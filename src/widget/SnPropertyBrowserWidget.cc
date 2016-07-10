#include <QVBoxLayout>
#include "widget/SnPropertyBrowserWidget.h"
#include "qtpropertymanager.h"
#include "qteditorfactory.h"
#include "qttreepropertybrowser.h"

SnPropertyBrowserWidget::SnPropertyBrowserWidget()
{

	QtDoublePropertyManager *doubleManager;
	QtStringPropertyManager *stringManager;
	QtColorPropertyManager *colorManager;
	QtFontPropertyManager *fontManager;
	QtPointPropertyManager *pointManager;
	QtSizePropertyManager *sizeManager;


	doubleManager = new QtDoublePropertyManager(this);
	stringManager = new QtStringPropertyManager(this);
	colorManager = new QtColorPropertyManager(this);
	fontManager = new QtFontPropertyManager(this);
	pointManager = new QtPointPropertyManager(this);
	sizeManager = new QtSizePropertyManager(this);


	QtDoubleSpinBoxFactory *doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this);
	QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(this);
	QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(this);
	QtLineEditFactory *lineEditFactory = new QtLineEditFactory(this);
	QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(this);



	propertyEditor = new QtTreePropertyBrowser(this);
	propertyEditor->setFactoryForManager(doubleManager, doubleSpinBoxFactory);
	propertyEditor->setFactoryForManager(stringManager, lineEditFactory);
	propertyEditor->setFactoryForManager(colorManager->subIntPropertyManager(), spinBoxFactory);
	propertyEditor->setFactoryForManager(fontManager->subIntPropertyManager(), spinBoxFactory);
	propertyEditor->setFactoryForManager(fontManager->subBoolPropertyManager(), checkBoxFactory);
	propertyEditor->setFactoryForManager(fontManager->subEnumPropertyManager(), comboBoxFactory);
	propertyEditor->setFactoryForManager(pointManager->subIntPropertyManager(), spinBoxFactory);
	propertyEditor->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);


	QtProperty *property;

	property = doubleManager->addProperty(tr("Position X"));
	doubleManager->setRange(property, 0, 50);
	doubleManager->setValue(property, 100);
	addProperty(property, QLatin1String("xpos"));

	property = doubleManager->addProperty(tr("Position Y"));
	doubleManager->setRange(property, 0, 33);
	doubleManager->setValue(property, 33);
	addProperty(property, QLatin1String("ypos"));

	property = doubleManager->addProperty(tr("Position Z"));
	doubleManager->setRange(property, 0, 256);
	doubleManager->setValue(property, 11);
	addProperty(property, QLatin1String("zpos"));

	QVBoxLayout* vlayout=new QVBoxLayout();
	vlayout->addWidget(propertyEditor);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);
}

SnPropertyBrowserWidget::~SnPropertyBrowserWidget()
{
}









void SnPropertyBrowserWidget::addProperty(QtProperty *property, const QString &id)
{
	propertyToId[property] = id;
	idToProperty[id] = property;
	QtBrowserItem *item = propertyEditor->addProperty(property);
	if (idToExpanded.contains(id))
		propertyEditor->setExpanded(item, idToExpanded[id]);
}
