#include <QVector3D>
#include <QVector4D>
#include <QVBoxLayout>

#include "widget/SnPropertyBrowserWidget.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include "support/util/FsScriptUtil.h"
#include "FsEnums.h"
#include "SnGlobal.h"
#include "operator/SnDataOperator.h"


NS_FS_USE

SnPropertyBrowserWidget::SnPropertyBrowserWidget()
{

	m_variantManager=new QtVariantPropertyManager(this);
	m_variantFactor=new QtVariantEditorFactory(this);
	m_propertyEditor = new QtTreePropertyBrowser(this);


	m_propertyEditor->setFactoryForManager(m_variantManager,m_variantFactor);
	m_propertyEditor->setHeaderVisible(false);
	m_identify=NULL;
	m_groupAttrDescList=NULL;


	QVBoxLayout* vlayout=new QVBoxLayout();
	vlayout->addWidget(m_propertyEditor);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);


	connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
			this, SLOT(slotEditorValueChange(QtProperty *, const QVariant &)));
}


void SnPropertyBrowserWidget::setIdentify(SnIdentify* id)
{	
	if(m_identify==id)
	{
		return;
	}

	m_identify=id;

	m_propertyEditor->clear();
	m_variantManager->clear();
	m_nameToProperty.clear();
	m_nameToDesc.clear();

	if(m_groupAttrDescList)
	{
		delete m_groupAttrDescList;
		m_groupAttrDescList=NULL;
	}

	if(!m_identify)
	{
		return;
	}



	m_groupAttrDescList=id->getAttributeList();


	m_variantManager->blockSignals(true);

	int size=m_groupAttrDescList->getAttrGroupDescNu();
	for(int i=0;i<size;i++)
	{
		SnAttrGroupDesc* gdesc=m_groupAttrDescList->getAttrGroupDesc(i);
		QtProperty* property=addProperty(id,gdesc);
		m_propertyEditor->addProperty(property);
	}

	m_variantManager->blockSignals(false);
}

QtProperty* SnPropertyBrowserWidget::addProperty(SnIdentify* id,SnAttrGroupDesc* desc)
{
	const char* name=desc->getName();

	QtProperty* group=m_variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),QString(name));

	int size=desc->getAttrTypeDescNu();

	for(int i=0;i<size;i++)
	{
		SnAttrTypeDesc* tattr=desc->getAttrTypeDesc(i);

		QtProperty* sub_property=addProperty(id,tattr);
		if(sub_property)
		{
			group->addSubProperty(sub_property);
		}
	}
	return group;
}



QtProperty* SnPropertyBrowserWidget::addProperty(SnIdentify* id,SnAttrTypeDesc* tattr)
{

	const char* name=tattr->getName();
	int type=tattr->getType();
	FsVariant t_value=id->getAttribute(name);

	if(type==SN_TYPE_ENUMS)
	{
		E_FsType ftype=t_value.getType();
		if(ftype==E_FsType::FT_CHARS)
		{

			QtVariantProperty* property=m_variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),QString(name));
			QStringList enums_name=tattr->getEnums();

			property->setAttribute(QLatin1String("enumNames"), enums_name);
			const char* value=(char*)t_value.getValue();

			int size=enums_name.size();
			for(int i=0;i<size;i++)
			{
				if(enums_name.value(i)==value)
				{
					property->setValue(i);
					break;
				}
			}

			m_nameToProperty[name]=property;
			m_nameToDesc[name]=tattr;

			return property;
		}



	}
	else if(type==SN_TYPE_NORMAL)
	{
		E_FsType ftype=t_value.getType();
		switch(ftype)
		{
			case E_FsType::FT_IN_VALID:
				{
					return NULL;
				}

			case E_FsType::FT_B_1:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Bool,QString(name));
					property->setValue(*(bool*)t_value.getValue());
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_I_1:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Int,QString(name));
					property->setValue(*(int*)t_value.getValue());
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}
			case E_FsType::	FT_F_1:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Double,QString(name));
					property->setValue(*(float*)t_value.getValue());
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_F_2:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::PointF,QString(name));
					Vector2 value=*(Vector2*)t_value.getValue();
					property->setValue(QPointF(value.x,value.y));
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_F_3:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Vector3D,QString(name));
					Vector3 value=*(Vector3*)t_value.getValue();
					property->setValue(QVector3D(value.x,value.y,value.z));
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_F_4:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Vector4D,QString(name));
					Vector4 value=*(Vector4*)t_value.getValue();
					property->setValue(QVector4D(value.x,value.y,value.z,value.w));
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}

			case E_FsType::FT_COLOR_4:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Color,QString(name));
					Color4f value=*(Color4f*)t_value.getValue();
					property->setValue(QColor(value.r*255,value.g*255,value.b*255,value.a*255));
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}

			case E_FsType::FT_CHARS:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::String,QString(name));
					const char* value=(char*)t_value.getValue();
					property->setValue(value);
					m_nameToProperty[name]=property;
					m_nameToDesc[name]=tattr;
					return property;
					break;
				}

			default:
				QtVariantProperty* property=m_variantManager->addProperty(QVariant::String,QString(name));
				const char* value=(char*)t_value.getValue();
				std::string v=std::string(value)+std::string(FsEnum_FsTypeToStr(ftype));
				property->setValue(v.c_str());

				m_nameToProperty[name]=property;
				m_nameToDesc[name]=tattr;

				return property;
				break;
		}
	}
	return NULL;
}	



void SnPropertyBrowserWidget::slotCurProjectChange()
{
	refreshProperty();
}

void SnPropertyBrowserWidget::slotEditorValueChange(QtProperty* p,QVariant v)
{

	if(m_identify==NULL)
	{
		FS_TRACE_ERROR("NO Select Value,But has Attribute");
		return ;
	}

	QString qname=p->propertyName();
	std::string name=qname.toUtf8().constData();


	SnAttrTypeDesc* desc=NULL; 
	std::map<std::string,SnAttrTypeDesc*>::iterator iter=m_nameToDesc.find(name);
	if(iter==m_nameToDesc.end())
	{
		FS_TRACE_ERROR("No Property(%s) Register",name.c_str());
		return;
	}
	desc=iter->second;

	if(desc->getType()==SN_TYPE_ENUMS)
	{
		const QStringList& enum_list=desc->getEnums();
		int value=qvariant_cast<int>(v);

		QString enum_name=enum_list[value];

		SnGlobal::dataOperator()->setIdentifyAttribute( m_identify,name.c_str(),FsVariant(enum_name.toUtf8().constData()));
	}

	else if(desc->getType()==SN_TYPE_NORMAL)
	{
		FsVariant ret;
		switch(v.type())
		{
			case QVariant::Bool:
				{
					bool b_v=qvariant_cast<bool>(v);
					ret=FsVariant(b_v);
					break;
				}
			case QVariant::Int:
				{
					int i_v=qvariant_cast<int>(v);
					ret=FsVariant(i_v);
					break;
				}
			case QVariant::String:
				{
					QString t_v=qvariant_cast<QString>(v);
					ret=FsVariant(t_v.toUtf8().constData());
					break;
				}
			case QVariant::Double:
				{
					double t_v=qvariant_cast<double>(v);
					ret=FsVariant(float(t_v));
					break;
				}
			case QVariant::PointF:
				{
					QPointF t_v=qvariant_cast<QPointF>(v);
					ret=FsVariant(Vector2(t_v.x(),t_v.y()));
					break;
				}

			case QVariant::Vector3D:
				{
					QVector3D t_v=qvariant_cast<QVector3D>(v);
					ret=FsVariant(Vector3(t_v.x(),t_v.y(),t_v.z()));
					break;
				}

			case QVariant::Vector4D:
				{
					QVector4D t_v=qvariant_cast<QVector4D>(v);
					ret=FsVariant(Vector4(t_v.x(),t_v.y(),t_v.z(),t_v.w()));
					break;
				}

			case QVariant::Color:
				{
					QColor t_v=qvariant_cast<QColor>(v);
					qreal r,g,b,a;
					t_v.getRgbF(&r,&g,&b,&a);
					ret=FsVariant(Color4f(r,g,b,a));
					break;
				}

			default:
				FS_TRACE_ERROR("Unkown Type For Change");
				break;
		}


		SnGlobal::dataOperator()->setIdentifyAttribute( m_identify,name.c_str(),ret);
	}

}

void SnPropertyBrowserWidget::slotCurrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st)
{
	refreshProperty();
}


void SnPropertyBrowserWidget::slotIdentifyAttributeChange(SnIdentify* id,const char* name)
{
	if(id!=m_identify)
	{
		return ;
	}

	std::map<std::string,QtProperty*>::iterator iter=m_nameToProperty.find(name);
	if(iter==m_nameToProperty.end())
	{
		FS_TRACE_WARN("Unkown Property %s To Update",name);
		return ;
	}


	std::map<std::string,SnAttrTypeDesc*>::iterator t_iter=m_nameToDesc.find(name);
	if(t_iter==m_nameToDesc.end())
	{
		FS_TRACE_WARN("Unkown Desc %s To Update",name);
		return ;
	}



	FsVariant t_value=id->getAttribute(name);
	this->blockSignals(true);
	updateProperty((QtVariantProperty*)iter->second,t_iter->second,t_value);
	this->blockSignals(false);
}



void SnPropertyBrowserWidget::updateProperty(QtVariantProperty* property,SnAttrTypeDesc* tattr,FsVariant t_value)
{


	const char* name=tattr->getName();
	int type=tattr->getType();


	if(type==SN_TYPE_ENUMS)
	{
		E_FsType ftype=t_value.getType();
		if(ftype==E_FsType::FT_CHARS)
		{
			QStringList enums_name=tattr->getEnums();
			const char* value=(char*)t_value.getValue();

			int size=enums_name.size();
			for(int i=0;i<size;i++)
			{
				if(enums_name.value(i)==value)
				{
					property->setValue(i);
					break;
				}
			}
		}
	}
	else if(type==SN_TYPE_NORMAL)
	{
		E_FsType ftype=t_value.getType();
		switch(ftype)
		{
			case E_FsType::FT_IN_VALID:
				{
					return ;
				}

			case E_FsType::FT_B_1:
				{
					property->setValue(*(bool*)t_value.getValue());
					break;
				}
			case E_FsType::FT_I_1:
				{
					property->setValue(*(int*)t_value.getValue());
					break;
				}
			case E_FsType::	FT_F_1:
				{

					property->setValue(*(float*)t_value.getValue());
					break;
				}
			case E_FsType::FT_F_2:
				{

					Vector2 value=*(Vector2*)t_value.getValue();
					property->setValue(QPointF(value.x,value.y));
					break;
				}
			case E_FsType::FT_F_3:
				{

					Vector3 value=*(Vector3*)t_value.getValue();
					property->setValue(QVector3D(value.x,value.y,value.z));
					break;
				}
			case E_FsType::FT_F_4:
				{

					Vector4 value=*(Vector4*)t_value.getValue();
					property->setValue(QVector4D(value.x,value.y,value.z,value.w));
					break;
				}

			case E_FsType::FT_COLOR_4:
				{

					Color4f value=*(Color4f*)t_value.getValue();
					property->setValue(QColor(value.r*255,value.g*255,value.b*255,value.a*255));
					break;
				}

			case E_FsType::FT_CHARS:
				{
					const char* value=(char*)t_value.getValue();
					property->setValue(value);
					break;
				}

			default:
				const char* value=(char*)t_value.getValue();
				std::string v=std::string(value)+std::string(FsEnum_FsTypeToStr(ftype));
				property->setValue(v.c_str());

				break;
		}
	}

}

void SnPropertyBrowserWidget::refreshProperty()
{
	SnIdentify* id=SnGlobal::dataOperator()->getCurrentIdentify();
	if(id)

	{
		setIdentify(id);
		return ;
	}

	setIdentify(NULL);
	m_identify=NULL;
}






SnPropertyBrowserWidget::~SnPropertyBrowserWidget()
{

}




