#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Group>
#include <osg/Matrixd>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

class GetWorldCoordinateOfNodeVisitor :public osg::NodeVisitor
{
public:
	GetWorldCoordinateOfNodeVisitor()
		:osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_PARENTS),
		done(false)
	{
		wMatrix = new osg::Matrixd;
	}

	virtual void apply(osg::Node & node)
	{
		if (!done)
		{
			if (0==node.getNumParents() )
			{
				wMatrix->set(osg::computeLocalToWorld(this->getNodePath()));
			}
			traverse(node);
		}
	}

	osg::Matrixd* getWorldMatrix()
	{
		return wMatrix;
	}

private:
	bool done;
	osg::Matrixd *wMatrix;
};

osg::Matrixd* getWorldCorrds(osg::Node *node)
{
	GetWorldCoordinateOfNodeVisitor *ncv = new GetWorldCoordinateOfNodeVisitor;
	if (node&&ncv)
	{
		node->accept(*ncv);
		return ncv->getWorldMatrix();
	}
	else
	{
		return nullptr;
	}
}

void Transform_Point(double out[4], const double m[16], const double in[4])
{
#define M(row,col) m[col*4+row]
	out[0] = M(0, 0)*in[0] + M(0, 1)*in[1] + M(0, 2)*in[2] + M(0, 3)*in[3];
	out[1] = M(1, 0)*in[0] + M(1, 1)*in[1] + M(1, 2)*in[2] + M(1, 3)*in[3];
	out[2] = M(2, 0)*in[0] + M(2, 1)*in[1] + M(2, 2)*in[2] + M(2, 3)*in[3];
	out[3] = M(3, 0)*in[0] + M(3, 1)*in[1] + M(3, 2)*in[2] + M(3, 3)*in[3];
#undef  M
}

osg::Vec3d WorldToScreen(osgViewer::Viewer *view, osg::Vec3d worldPoint)
{
	double in[4];
	double out[4];

	in[0] = worldPoint._v[0];
	in[1] = worldPoint._v[1];
	in[2] = worldPoint._v[2];
	in[3] = 1.0f;

	osg::Matrix projectMatrix = view->getCamera()->getProjectionMatrix();
	osg::Matrix viewMatrix = view->getCamera()->getViewMatrix();

	double myProjectMatrix[16];
	memcpy(myProjectMatrix,viewMatrix.ptr(), sizeof(GLdouble)*16);
	Transform_Point( in, myProjectMatrix, out);

	if (in[3]==0.0f)
	{
		return osg::Vec3d(0, 0, 0);
	}

	in[0] /= in[3];
	in[1] /= in[3];
	in[2] /= in[3];

	int viewPort[4];
	osg::Viewport *myViewPort = view->getCamera()->getViewport();
	viewPort[0] = myViewPort->x();
	viewPort[1] = myViewPort->y();
	viewPort[2] = myViewPort->width();
	viewPort[3] = myViewPort->height();

	osg::Vec3d screenPoint;
	screenPoint._v[0] = (int)(viewPort[0] + (1 + in[0])*viewPort[2] / 2 + 0.5);
	screenPoint._v[1] = (int)(viewPort[1] + (1 + in[1])*viewPort[3] / 2 + 0.5);
	screenPoint._v[2] = 0;

	return screenPoint;
}

int main(int argc, char *agrv[])
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new  osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("dumptruck.osg");
	osg::Matrixd * mat =getWorldCorrds(node.get() );
	root->addChild(node.release());
	viewer->setSceneData(root);
	viewer->realize();
	viewer->run();
}

