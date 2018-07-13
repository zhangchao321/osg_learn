#include <osgViewer/Viewer> 
#include <osg/Group> 
#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>  
#include <osgUtil/Optimizer> 

int main(int argc, char *agrv[])
{ 
	osg::ref_ptr<osg::Group> root = new  osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform;
	pat1->setPosition(osg::Vec3(-5,0,0));
	pat1->setScale(osg::Vec3(3,3,3));
	pat1->addChild(node.get());

	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 = new osg::PositionAttitudeTransform;
	pat2->setPosition(osg::Vec3(5,5,5));
	pat2->setScale(osg::Vec3(2,2,2));
	pat2->addChild(node.get());

	root->addChild(pat1);
	root->addChild(pat2);

	osgUtil::Optimizer optimizer; 
	optimizer.optimize(root.get());

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

	return 0;
}

