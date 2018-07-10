#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Group> 

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

int main(int argc, char *agrv[])
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new  osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osgt");
	root->addChild(node.release());
	viewer->setSceneData(root);
	viewer->realize();
	viewer->run();
}

