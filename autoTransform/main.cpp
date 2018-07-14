#include <osgViewer/Viewer> 
#include <osg/Group> 
#include <osg/Node>
#include <osg/AutoTransform>
#include <osgDB/ReadFile>  
#include <osgUtil/Optimizer> 
#include <osgText/Text>

osg::ref_ptr<osg::Node> createAutoTransform(const osg::Vec3 &position, float size, const std::string &label,
	osg::AutoTransform::AutoRotateMode autoMode, osgText::Text::AxisAlignment axisAlignment)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	std::string font("./fonts/cour.ttf");

	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	geode->addDrawable(text.get());

	text->setFont(font);
	text->setFontResolution(128.0f, 128.0f);
	text->setCharacterSize(size);
	text->setAlignment(osgText::Text::CENTER_CENTER);
	text->setAxisAlignment(axisAlignment);
	text->setText(label);

	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform;
	at->addChild(geode.get());

	at->setAutoRotateMode(autoMode);
	at->setAutoScaleToScreen(false);
	at->setMinimumScale(0.0f);
	at->setMaximumScale(5.0f);
	at->setPosition(position);

	return at.get();
}

int main(int argc, char *agrv[])
{ 
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	const std::string label = "Fly to high";
	osg::ref_ptr<osg::Node> node = createAutoTransform(osg::Vec3(0,0,0),60,label, 
		osg::AutoTransform::ROTATE_TO_SCREEN, osgText::Text::XY_PLANE);
	root->addChild(node.get());

	node = createAutoTransform(osg::Vec3(0, 0, 0), 60, label,
		osg::AutoTransform::ROTATE_TO_SCREEN, osgText::Text::XY_PLANE);
	root->addChild(node.get());

	node = createAutoTransform(osg::Vec3(0, 0, 0), 60, label,
		osg::AutoTransform::NO_ROTATION, osgText::Text::YZ_PLANE);
	root->addChild(node.get());

	node = createAutoTransform(osg::Vec3(0, 0, 0), 60, label,
		osg::AutoTransform::ROTATE_TO_CAMERA, osgText::Text::XY_PLANE);
	root->addChild(node.get());

	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get() );
	viewer->realize();
	viewer->run();
	return 0;
}

