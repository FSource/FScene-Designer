#ifndef _SD_PROPERTY_WIDGET_H_
#define _SD_PROPERTY_WIDGET_H_

#include <QWidget>
#include <QtProperty>
#include <QtVariantProperty>
#include "snvariantmanager.h"
#include "snvariantfactory.h"

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
		void slotCurrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st);

	public slots:
		void slotEditorValueChange(QtProperty*,const QVariant v);
		void slotIdentifyAttributeChange(SnIdentify* id,const char* name);



	protected:
		void setIdentify(SnIdentify* id);
		QtProperty* addProperty(SnIdentify* id,SnAttrGroupDesc* desc);
		QtProperty* addProperty(SnIdentify* id,SnAttrTypeDesc* tattr);
		void refreshProperty();
		void updateProperty(QtVariantProperty* p,SnAttrTypeDesc* tattr,Faeris::FsVariant v);


		void saveExpandState();
		
		void updateExpandState();

	private:
		class QtTreePropertyBrowser* m_propertyEditor;
		class QtVariantEditorFactory* m_variantFactor;
		class QtVariantPropertyManager* m_variantManager;

		std::map<std::string,QtProperty*> m_nameToProperty;
		std::map<std::string,SnAttrTypeDesc*> m_nameToDesc;

		std::map<std::string,bool> m_nameToExpands;

		SnAttrGroupList* m_groupAttrDescList;
		SnIdentify* m_identify;

};



#endif /*_SD_PROPERTY_WIDGET_H_*/


