#include <osgViewer/Viewer> 
#include <osg/Group> 
#include <osg/Node>
#include <osg/Geode> 
#include <osg/Geometry>
#include <osgUtil/Optimizer> 

osg::ref_ptr<osg::Node> createQuad()
{
	//����Ҷ�ӽڵ����
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	//�������������
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	//������������
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f,0.0f,0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
	//���ö�������
	geom->setVertexArray(v.get() );

	//�����ı��ζ�����������
	osg::ref_ptr<osg::DrawElementsUInt> quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS,0);
	quad->push_back(0);
	quad->push_back(1);
	quad->push_back(2);
	quad->push_back(3);
	//������������
	geom->addPrimitiveSet(quad.get());

	//������������������
	osg::ref_ptr<osg::DrawElementsUInt> triangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	triangle->push_back(4);
	triangle->push_back(0);
	triangle->push_back(3);
	//������������
	geom->addPrimitiveSet(triangle.get());

	//������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array;
	vc->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	geom->setColorArray(vc.get() );
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	//������ɫ��������
	/*osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4> * colorIndex =
		new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4>;*/
	//������ݣ��붥��һһ��Ӧ
	/*colorIndex->push_back(0);
	colorIndex->push_back(1);
	colorIndex->push_back(2);
	colorIndex->push_back(3);
	colorIndex->push_back(2);*/

	//������������
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array;
	nc->push_back(osg::Vec3(0.0f,1.0f,0.0f));
	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	
	//��Ӽ������ݵ�Ҷ�ӽڵ�
	geode->addDrawable(geom.get());
	return geode.get();
}

int main(int argc, char *agrv[])
{ 
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(createQuad());

	osgUtil::Optimizer optm;
	optm.optimize(root.get() );

	viewer->setSceneData(root.get() );
	
	viewer->realize();
	viewer->run();
	return 0;
}

