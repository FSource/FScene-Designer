#ifndef _SD_PROPERTY_WIDGET_H_
#define _SD_PROPERTY_WIDGET_H_

#include <QWidget>
#include <QtProperty>

#include "core/SnIdentify.h"
#include "core/SnLayer2D.h"
#include "FsVariant.h"
#include "support/util/FsArray.h"

class SnPropertyBrowserWidget:public QWidget
{
	Q_OBJECT
	public:
		SnPropertyBrowserWidget();
		~SnPropertyBrowserWidget();

	public:

		void setProperty(std::string name,Faeris::FsVariant value);

	public slots:
		void slotCurProjectChange();
		void slotCurEntityChange();
		void slotCurLayerChange(SnLayer2D* ly);

	public slots:
		void slotEditorValueChange(QtProperty*,const QVariant v);
		void slotIdentifyAttributeChange(SnIdentify* id,const char* name);


	protected:
		void setIdentify(SnIdentify* id);
		QtProperty* addProperty(SnIdentify* id,SnAttrGroupDesc* desc);
		QtProperty* addProperty(SnIdentify* id,SnAttrTypeDesc* tattr);
		void refreshProperty();

	private:
		class QtTreePropertyBrowser* m_propertyEditor;
		class QtVariantEditorFactory* m_variantFactor;
		class QtVariantPropertyManager* m_variantManager;

		std::map<std::string,QtProperty*> m_nameToProperty;
		std::map<std::string,SnAttrTypeDesc*> m_nameToDesc;

		SnAttrGroupList* m_groupAttrDescList;
		SnIdentify* m_identify;

};



#endif /*_SD_PROPERTY_WIDGET_H_*/

