#include <osgViewer/Viewer> 
#include <osg/Group> 
#include <osg/Node>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>  
#include <osgUtil/Optimizer> 

int main(int argc, char *agrv[])
{ 
	osg::ref_ptr<osg::Group> root = new  osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("avatar.osg");

	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform;
	osg::Matrix m;
	m.makeRotate(90, osg::Vec3(0, 1, 0));
	m.makeTranslate(osg::Vec3(100,0,0));
	mt1->setMatrix(m);
	mt1->addChild(node.get());
	 

	root->addChild(node.get());
	root->addChild(mt1.get());

	osgUtil::Optimizer optimizer; 
	optimizer.optimize(root.get());

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

	return 0;
}

