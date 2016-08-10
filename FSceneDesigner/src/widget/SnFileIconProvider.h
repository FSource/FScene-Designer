#ifndef _SN_FILE_ICON_PROVIDER_H_
#define _SN_FILE_ICON_PROVIDER_H_ 
#include <QFileIconProvider>

class SnFileIconProvider:public QFileIconProvider 
{
	public:
		SnFileIconProvider();

	public:
		virtual QIcon icon(const QFileInfo & info) const;

	public:
		//void clearIcon();

	public:
		std::map<std::string,QIcon> m_map;
};


#endif /*_SN_FILE_ICON_PROVIDER_H_*/
