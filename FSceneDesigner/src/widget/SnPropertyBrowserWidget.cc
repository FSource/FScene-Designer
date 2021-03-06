#include <QVector3D>
#include <QRect>
#include <QVector4D>
#include <QVBoxLayout>

#include "widget/SnPropertyBrowserWidget.h"
#include "snvariantmanager.h"
#include "snvariantfactory.h"
#include "qttreepropertybrowser.h"
#include "qtvariantproperty.h"
#include "support/util/FsScriptUtil.h"
#include "FsEnums.h"
#include "SnGlobal.h"
#include "operator/SnDataOperator.h"
#include "core/SnProject.h"


NS_FS_USE

SnPropertyBrowserWidget::SnPropertyBrowserWidget()
{

	m_variantManager=new SnVariantManager(this);
	m_variantFactor=new SnVariantFactory(this);
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

	saveExpandState();


	m_identify=id;

	m_propertyEditor->clear();
	m_variantManager->clear();
	m_nameToProperty.clear();
	m_nameToDesc.clear();
	m_propertyToDesc.clear();

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
	updateExpandState();
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
	m_nameToProperty[name]=group;


	return group;
}



QtProperty* SnPropertyBrowserWidget::addProperty(SnIdentify* id,SnAttrTypeDesc* tattr)
{

	const char* disp_name=tattr->getDisplayName();
	int type=tattr->getType();

	const char* name_value=tattr->getName();
	FsVariant t_value=id->getIdentifyAttribute(name_value);

	if(type==SN_TYPE_ENUMS)
	{
		E_FsType ftype=t_value.getType();
		if(ftype==E_FsType::FT_CHARS)
		{

			QtVariantProperty* property=m_variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),QString(disp_name));
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

			m_nameToProperty[name_value]=property;
			m_nameToDesc[name_value]=tattr;
			m_propertyToDesc[property]=tattr;

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
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Bool,QString(disp_name));
					property->setValue(*(bool*)t_value.getValue());
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_I_1:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Int,QString(disp_name));
					property->setValue(*(int*)t_value.getValue());
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}
			case E_FsType::	FT_F_1:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Double,QString(disp_name));
					property->setValue(*(float*)t_value.getValue());
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_F_2:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::PointF,QString(disp_name));
					Vector2 value=*(Vector2*)t_value.getValue();
					property->setValue(QPointF(value.x,value.y));
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_F_3:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Vector3D,QString(disp_name));
					Vector3 value=*(Vector3*)t_value.getValue();
					property->setValue(QVector3D(value.x,value.y,value.z));
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}
			case E_FsType::FT_F_4:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Vector4D,QString(disp_name));
					Vector4 value=*(Vector4*)t_value.getValue();
					property->setValue(QVector4D(value.x,value.y,value.z,value.w));
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}

			case E_FsType::FT_COLOR_4:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Color,QString(disp_name));
					Color4f value=*(Color4f*)t_value.getValue();
					property->setValue(QColor(value.r*255,value.g*255,value.b*255,value.a*255));
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}

			case E_FsType::FT_F_RECT2D:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::RectF,QString(disp_name));
					Rect2D value=*(Rect2D*)t_value.getValue();

					property->setValue(QRectF(value.x,value.y,value.width,value.height));
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}


			case E_FsType::FT_CHARS:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::String,QString(disp_name));
					const char* value=(char*)t_value.getValue();
					property->setValue(value);
					m_nameToProperty[name_value]=property;
					m_nameToDesc[name_value]=tattr;
					m_propertyToDesc[property]=tattr;
					return property;
					break;
				}

			default:
				QtVariantProperty* property=m_variantManager->addProperty(QVariant::String,QString(disp_name));
				const char* value=(char*)t_value.getValue();
				std::string v=std::string(value)+std::string(FsEnum_FsTypeToStr(ftype));
				property->setValue(v.c_str());

				m_nameToProperty[name_value]=property;
				m_nameToDesc[name_value]=tattr;
				m_propertyToDesc[property]=tattr;

				return property;
				break;
		}
	}
	else if(type==SN_TYPE_EXTENDS)
	{
		E_FsType ftype=t_value.getType();
		switch(ftype)
		{
			case E_FsType::FT_CHARS:
				{
					if(tattr->getEditorType()==SN_EXTENDS_EDIT_FILEPATH)
					{
						QtVariantProperty* property=m_variantManager->addProperty(SnVariantManager::filePathTypeId(),QString(disp_name));
						const char* value=(char*)t_value.getValue();
						property->setValue(value);
						m_nameToProperty[name_value]=property;
						m_nameToDesc[name_value]=tattr;
						m_propertyToDesc[property]=tattr;
						return property;
					}
				}
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

	if(this->signalsBlocked())
	{
		return;
	}


	if(m_identify==NULL)
	{
		FS_TRACE_ERROR("NO Select Value,But has Attribute");
		return ;
	}

	QString qname=p->propertyName();
	std::string name=qname.toUtf8().constData();

	SnAttrTypeDesc* desc=NULL; 
	std::map<QtProperty*,SnAttrTypeDesc*>::iterator iter=m_propertyToDesc.find(p);
	if(iter==m_propertyToDesc.end())
	{
		FS_TRACE_ERROR("No Property(%s) Register",name.c_str());
		return;
	}
	desc=iter->second;
	name=desc->getName();

	if(desc->getType()==SN_TYPE_ENUMS)
	{
		const QStringList& enum_list=desc->getEnums();
		int value=qvariant_cast<int>(v);

		QString enum_name=enum_list[value];

		SnGlobal::dataOperator()->setIdentifyAttribute( m_identify,name.c_str(),FsVariant(enum_name.toUtf8().constData()));
	}

	else if(desc->getType()==SN_TYPE_NORMAL||desc->getType()==SN_TYPE_EXTENDS)
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
					if(desc->getEditorType()==SN_EXTENDS_EDIT_FILEPATH)
					{
						std::string dir_path=SnGlobal::dataOperator()->getCurProject()->getDirName();
						if(t_v.startsWith(dir_path.c_str()))
						{
							std::string r_path=SnUtil::toRelativePath(dir_path.c_str(),t_v.toUtf8().constData());
							ret=FsVariant(r_path.c_str());
						}
						else 
						{
							ret=FsVariant(t_v.toUtf8().constData());
						}
					}
					else 
					{
						ret=FsVariant(t_v.toUtf8().constData());
					}
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
			case QVariant::RectF:
				{
					QRectF t_v=qvariant_cast<QRectF>(v);
					ret=FsVariant(Rect2D(t_v.x(),t_v.y(),t_v.width(),t_v.height()));
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



	FsVariant t_value=id->getIdentifyAttribute(name);
	this->blockSignals(true);
	updateProperty((QtVariantProperty*)iter->second,t_iter->second,t_value);
	this->blockSignals(false);
}



void SnPropertyBrowserWidget::updateProperty(QtVariantProperty* property,SnAttrTypeDesc* tattr,FsVariant t_value)
{


	//const char* name=tattr->getName();
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
	else if(type==SN_TYPE_NORMAL||type==SN_TYPE_EXTENDS)
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
			case E_FsType::FT_F_RECT2D:
				{
					Rect2D value=*(Rect2D*)t_value.getValue();
					property->setValue(QRectF(value.x,value.y,value.width,value.height));
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

void SnPropertyBrowserWidget::saveExpandState()
{
	QList<QtBrowserItem *> list = m_propertyEditor->topLevelItems();
	QListIterator<QtBrowserItem *> it(list);
	while (it.hasNext()) 
	{
		QtBrowserItem *item = it.next();
		QtProperty *prop = item->property();


		std::string name=prop->propertyName().toUtf8().constData();

		std::map<QtProperty*,SnAttrTypeDesc*>::iterator iter=m_propertyToDesc.find(prop);
		if(iter!=m_propertyToDesc.end())
		{
			name=iter->second->getName();
		}


		m_nameToExpands[name] = m_propertyEditor->isExpanded(item);
	
		QList<QtBrowserItem *> ch_list = item->children();
		QListIterator<QtBrowserItem *> ch_it(ch_list);

		while(ch_it.hasNext())
		{
			QtBrowserItem* ch_item = ch_it.next();
			QtProperty* ch_prop = ch_item->property();
			std::string ch_name=ch_prop->propertyName().toUtf8().constData();

			std::map<QtProperty*,SnAttrTypeDesc*>::iterator ch_iter=m_propertyToDesc.find(prop);
			if(ch_iter!=m_propertyToDesc.end())
			{
				ch_name=iter->second->getName();
			}

			m_nameToExpands[ch_name] = m_propertyEditor->isExpanded(ch_item);
		}
	}
}

void SnPropertyBrowserWidget::updateExpandState()
{
	QList<QtBrowserItem *> list = m_propertyEditor->topLevelItems();
	QListIterator<QtBrowserItem *> it(list);
	while (it.hasNext()) 
	{
		QtBrowserItem *item = it.next();
		QtProperty* prop = item->property();
		std::map<QtProperty*,SnAttrTypeDesc*>::iterator iter;

		iter=m_propertyToDesc.find(prop);

		std::string name=prop->propertyName().toUtf8().constData();
		if(iter!=m_propertyToDesc.end())
		{
			SnAttrTypeDesc* desc=iter->second;
			name=desc->getName();
		}



		if(m_nameToExpands.find(name)!=m_nameToExpands.end())
		{
			bool value=m_nameToExpands[name];
			m_propertyEditor->setExpanded(item,value);
		}

		QList<QtBrowserItem *> ch_list = item->children();

		QListIterator<QtBrowserItem *> ch_it(ch_list);

		while(ch_it.hasNext())
		{
			QtBrowserItem* ch_item = ch_it.next();
			QtProperty *ch_prop = ch_item->property();

			std::string ch_name=ch_prop->propertyName().toUtf8().constData();

			std::map<QtProperty*,SnAttrTypeDesc*>::iterator ch_iter;
			ch_iter=m_propertyToDesc.find(ch_prop);

			if(ch_iter!=m_propertyToDesc.end())
			{
				ch_name=ch_iter->second->getName();
			}

			if(m_nameToExpands.find(ch_name)!=m_nameToExpands.end())
			{
				bool value=m_nameToExpands[ch_name];
				m_propertyEditor->setExpanded(ch_item,value);
			}
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




