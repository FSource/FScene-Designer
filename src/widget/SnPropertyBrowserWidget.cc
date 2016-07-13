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
	QVBoxLayout* vlayout=new QVBoxLayout();
	vlayout->addWidget(m_propertyEditor);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);


}


void SnPropertyBrowserWidget::setPropertysList(SnAttrGroupList* list)
{	
	m_propertyEditor->clear();
	m_variantManager->clear();

	if(list==NULL)
	{
		return;
	}


	int size=list->getAttrGroupDescNu();
	for(int i=0;i<size;i++)
	{
		SnAttrGroupDesc* gdesc=list->getAttrGroupDesc(i);
		QtProperty* property=addProperty(gdesc);
		m_propertyEditor->addProperty(property);
	}
}

QtProperty* SnPropertyBrowserWidget::addProperty(SnAttrGroupDesc* desc)
{
	const char* name=desc->getName();

	QtProperty* group=m_variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),QString(name));

	int size=desc->getAttrTypeDescNu();

	for(int i=0;i<size;i++)
	{
		SnAttrTypeDesc* tattr=desc->getAttrTypeDesc(i);

		QtProperty* sub_property=addProperty(tattr);
		if(sub_property)
		{
			group->addSubProperty(sub_property);
		}
	}
	return group;
}



QtProperty* SnPropertyBrowserWidget::addProperty(SnAttrTypeDesc* tattr)
{
	const char* name=tattr->getName();
	int type=tattr->getType();
	FsVariant t_value=tattr->getValue();


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
					return property;
					break;
				}
			case E_FsType::	FT_F_1:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Double,QString(name));
					property->setValue(*(float*)t_value.getValue());
					return property;
					break;
				}
			case E_FsType::FT_F_2:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::PointF,QString(name));
					Vector2 value=*(Vector2*)t_value.getValue();
					property->setValue(QPointF(value.x,value.y));
					return property;
					break;
				}
			case E_FsType::FT_F_3:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Vector3D,QString(name));
					Vector3 value=*(Vector3*)t_value.getValue();
					property->setValue(QVector3D(value.x,value.y,value.z));
					return property;
					break;
				}
			case E_FsType::FT_F_4:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Vector4D,QString(name));
					Vector4 value=*(Vector4*)t_value.getValue();
					property->setValue(QVector4D(value.x,value.y,value.z,value.w));
					return property;
					break;
				}

			case E_FsType::FT_COLOR_4:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::Color,QString(name));
					Color4f value=*(Color4f*)t_value.getValue();
					property->setValue(QColor(value.r*255,value.g*255,value.b*255,value.a*255));
					return property;
					break;
				}

			case E_FsType::FT_CHARS:
				{
					QtVariantProperty* property=m_variantManager->addProperty(QVariant::String,QString(name));
					const char* value=(char*)t_value.getValue();
					property->setValue(value);
					return property;
					break;
				}

			default:
				QtVariantProperty* property=m_variantManager->addProperty(QVariant::String,QString(name));
				const char* value=(char*)t_value.getValue();
				std::string v=std::string(value)+std::string(FsEnum_FsTypeToStr(ftype));
				property->setValue(v.c_str());
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

void SnPropertyBrowserWidget::slotCurEntityChange()
{
	refreshProperty();
}

void SnPropertyBrowserWidget::slotCurLayerChange(SnLayer2D* ly)
{
	refreshProperty();
}



void SnPropertyBrowserWidget::refreshProperty()
{
	Entity2D* en=SnGlobal::dataOperator()->getCurEntity();
	if(en)
	{
		SnAttrGroupList* glist=dynamic_cast<SnIdentify*>(en)->getAttributeList();
		setPropertysList(glist);
		delete glist;
		return ;
	}

	SnLayer2D* ly=SnGlobal::dataOperator()->getCurLayer();
	if(ly)
	{
		SnAttrGroupList* glist=ly->getAttributeList();
		setPropertysList(glist);
		delete glist;
		return ;

		setPropertysList(NULL);
	}
}







SnPropertyBrowserWidget::~SnPropertyBrowserWidget()
{

}




