#ifndef _SD_PATH_UTIL_H_
#define _SD_PATH_UTIL_H_

#include <string>
class SdPathUtil
{

	public:
        static std::string getFileName(const std::string& file);
        static std::string getDirName(const std::string& file);
		static std::string removePrePath(const std::string& name,
										 const std::string& pre_path);
		static std::string toStdName(const std::string& name);
};


#endif /*_SD_PATH_UTIL_H_*/

