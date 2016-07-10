#ifndef _SD_PROPERTY_WIDGET_H_
#define _SD_PROPERTY_WIDGET_H_

#include <QWidget>
#include <QtProperty>


class SnPropertyBrowserWidget:public QWidget
{
	public:
		SnPropertyBrowserWidget();
		~SnPropertyBrowserWidget();


	public:

		void  addProperty(QtProperty *property, const QString &id);
	private:
		QMap<QtProperty *, QString> propertyToId;
		QMap<QString, QtProperty *> idToProperty;
		QMap<QString, bool> idToExpanded;

		class QtTreePropertyBrowser *propertyEditor;

};



#endif /*_SD_PROPERTY_WIDGET_H_*/


