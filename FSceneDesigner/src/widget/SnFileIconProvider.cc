#include "SnFileIconProvider.h"

SnFileIconProvider::SnFileIconProvider()
{

}

QIcon SnFileIconProvider::icon(const QFileInfo& info) const 
{
	QString path=info.absoluteFilePath();
	QString suffix=info.suffix();

	if(suffix=="png"||suffix=="jpg"||suffix=="tga")
	{
		return QIcon(path);
	}

	return QFileIconProvider::icon(info);
}

