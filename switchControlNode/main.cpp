#include<osgViewer/Viewer>
#include<osg/Node>
#include<osg/Group>
#include<osg/Switch>
#include<osgDB/ReadFile>
#include<osgUtil/Optimizer>

int main(int argc, char *argv[])
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::ref_ptr<osg::Node> node1 = new osg::Node;
	node1 = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osg::Node> node2 = new osg::Node;
	node2 = osgDB::readNodeFile("glider.osg");

	osg::ref_ptr<osg::Switch> swit = new osg::Switch;
	swit->addChild(node1.get(), false);
	swit->addChild(node2.get(), true);

	root->addChild(swit.get());

	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());
	
	viewer->setSceneData(root.get());

	viewer->realize();
	viewer->run();
	return 0;
}