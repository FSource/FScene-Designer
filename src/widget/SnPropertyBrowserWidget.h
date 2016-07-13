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
		void setPropertysList(SnAttrGroupList* glist);

		void setProperty(std::string name,Faeris::FsVariant value);

	public slots:
		void slotCurProjectChange();
		void slotCurEntityChange();
		void slotCurLayerChange(SnLayer2D* ly);



	protected:
		QtProperty* addProperty(SnAttrGroupDesc* desc);
		QtProperty* addProperty(SnAttrTypeDesc* tattr);
		void refreshProperty();

	private:
		class QtTreePropertyBrowser* m_propertyEditor;
		class QtVariantEditorFactory* m_variantFactor;
		class QtVariantPropertyManager* m_variantManager;
		std::map<std::string,class QtVariantProperty*> m_propertys;
};



#endif /*_SD_PROPERTY_WIDGET_H_*/


