#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Billboard>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgUtil//Optimizer>
#include <osgViewer/Viewer>

osg::ref_ptr<osg::Node> createBillboardTree(osg::ref_ptr<osg::Image> image)
{
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	v->push_back(osg::Vec3(-0.5,0,-0.5));
	v->push_back(osg::Vec3(0.5, 0, -0.5));
	v->push_back(osg::Vec3(0.5, 0, 0.5));
	v->push_back(osg::Vec3(-0.5, 0, 0.5));
	geometry->setVertexArray(v.get());

	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array;
	normal->push_back(osg::Vec3(1, 0, 0) ^ osg::Vec3(0, 0, 1));
	geometry->setNormalArray(normal.get());
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array;
	vt->push_back(osg::Vec2(0, 0));
	vt->push_back(osg::Vec2(1, 0));
	vt->push_back(osg::Vec2(1, 1));
	vt->push_back(osg::Vec2(0, 1));

	geometry->setTexCoordArray(0,vt.get());
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	if (image.get())
	{
		osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet;
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
		texture->setImage(image.get());
		stateSet->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
		stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		geometry->setStateSet(stateSet.get());
	}

	osg::ref_ptr<osg::Billboard> billBoard1 = new osg::Billboard;
	billBoard1->setMode(osg::Billboard::POINT_ROT_EYE);
	billBoard1->addDrawable(geometry.get(),osg::Vec3(5,0,0));

	osg::ref_ptr<osg::Billboard> billBoard2 = new osg::Billboard;
	billBoard2->setMode(osg::Billboard::AXIAL_ROT);
	billBoard2->setAxis(osg::Vec3(0, 0, 1));
	billBoard1->addDrawable(geometry.get(), osg::Vec3(10, 0, 0));

	osg::ref_ptr<osg::Group> billBoard = new osg::Group;
	billBoard->addChild(billBoard1.get());
	billBoard->addChild(billBoard2.get());

	return billBoard.get();
}

int main(int argc, char *agrv[])
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	 
	osg::ref_ptr<osg::Group> root = new  osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg"); 

	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("tree0.rgba");
	osg::ref_ptr<osg::Node> billNode =createBillboardTree(image.get());

	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;
	pat->setScale(osg::Vec3(5, 5, 5));
	pat->addChild(billNode.get());

	root->addChild(node.release());
	root->addChild(pat.release());
	
	viewer->setSceneData(root);
	viewer->realize();
	viewer->run();
}

