#include <QTextStream>
#include <QDir>

#include "SnIdentifyFactory.h"
#include "support/util/FsString.h"

#include "core/SnEntity2D.h"
#include "core/SnLabelTTF.h"
#include "core/SnLayer2D.h"
#include "core/SnListView.h"
#include "core/SnPageView.h"
#include "core/SnPressButton.h"
#include "core/SnQuad2D.h"
#include "core/SnScene.h"
#include "core/SnScrollView.h"
#include "core/SnUiWidget.h"

#include "support/util/FsScriptUtil.h"



NS_FS_USE

SnIdentify* SnIdentifyFactory::newInstanceFromUrl(const char* filename)
{

	QFile f(filename);

	if(!f.open(QIODevice::ReadOnly | QIODevice::Text))  
	{
		return NULL;
	}

	QTextStream txtInput(&f);  

	QString content=txtInput.readAll();
	FsDict* dict=ScriptUtil::parseScriptFromStr(content.toUtf8().constData());

	if(dict==NULL)
	{
		return NULL;
	}

	SnIdentify* id=newInstance(dict);
	dict->destroy();
	return id;
}



SnIdentify* SnIdentifyFactory::newInstance(Faeris::FsDict* dict)
{
	FsString* name=dict->lookupString("editClass");
	if(name)
	{
		std::map<std::string,SnIdentifyCreateFunc>::iterator  iter=m_creatorFuncs.find(name->cstr());

		if(iter!=m_creatorFuncs.end())
		{
			return iter->second(dict);
		}
		else 
		{
			FS_TRACE_WARN("Can't Find EditClass(%s) In SnIdentifyFactory",name->cstr()); 
		}
	}
	else 
	{
		FS_TRACE_WARN("Can't Find Key Edit Class Type Info");
		return NULL;
	}
	return NULL;
}

void SnIdentifyFactory::preLoadCreatorFuncs()
{
	m_creatorFuncs["SnEntity2D"] =(SnIdentifyCreateFunc)SnEntity2D::newInstance;
	m_creatorFuncs["SnLabelTTF"] =(SnIdentifyCreateFunc)SnLabelTTF::newInstance;
	m_creatorFuncs["SnLayer2D"] =(SnIdentifyCreateFunc)SnLayer2D::newInstance;
	m_creatorFuncs["SnListView"] =(SnIdentifyCreateFunc)SnListView::newInstance;
	m_creatorFuncs["SnPageView"] =(SnIdentifyCreateFunc)SnPageView::newInstance;
	m_creatorFuncs["SnPressButton"] =(SnIdentifyCreateFunc)SnPressButton::newInstance;
	m_creatorFuncs["SnQuad2D"] =(SnIdentifyCreateFunc)SnQuad2D::newInstance;
	m_creatorFuncs["SnScene"] =(SnIdentifyCreateFunc)SnScene::newInstance;
	m_creatorFuncs["SnScrollView"] =(SnIdentifyCreateFunc)SnScrollView::newInstance;
	m_creatorFuncs["SnUiWidget"] =(SnIdentifyCreateFunc)SnUiWidget::newInstance;

}




