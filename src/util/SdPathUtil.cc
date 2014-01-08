#include <QDir>
#include <QFileInfo>
#include "util/SdPathUtil.h"


std::string SdPathUtil::getFileName(const std::string& file)
{
	QFileInfo info(file.c_str());
	return info.fileName().toStdString();
}


std::string SdPathUtil::getDirName(const std::string& file)
{
	QFileInfo info(file.c_str());
	return info.absoluteDir().absolutePath().toStdString();
}

std::string SdPathUtil::removePrePath(const std::string& x_name,
                                      const std::string& x_pre_path)
{

    std::string name=SdPathUtil::toStdName(x_name);
    std::string pre_path=SdPathUtil::toStdName(x_pre_path);


	int path_length=pre_path.size();
	int name_length=name.size();


	if(path_length==0)
	{
		return name;
	}

	if(pre_path[path_length-1]!='/')
	{
		pre_path=pre_path+"/";
		path_length++;
	}

	if(path_length>name_length)
	{
		return name;
	}

	bool is_prefix=true;

	for(int i=0;i<path_length;i++)
	{
		if(pre_path[i]!=name[i])
		{
			is_prefix=false;
		}
	}
	if(!is_prefix)
	{
		return name;
	}

	else 
	{
		return name.c_str()+path_length;
	}
}


std::string SdPathUtil::toStdName(const std::string& x_name)
{
    std::string name=x_name;
	int size=name.size();
	for(int i=0;i<size;i++)
	{
		if(name[i]=='\\')
		{
            name[i]='/';
		}
	}
	return name;
}


