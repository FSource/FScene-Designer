#ifndef _SN_IDENTIFY_FACTORY_H_
#define _SN_IDENTIFY_FACTORY_H_ 

#include <map>
#include <string>

#include "support/util//FsDict.h"

class SnIdentify;

typedef SnIdentify* (*SnIdentifyCreateFunc)(Faeris::FsDict*);

class SnIdentifyFactory 
{
	public:
		SnIdentify* newInstanceFromUrl(const char* filename);
		SnIdentify* newInstance(Faeris::FsDict* dict);

	public:
		void preLoadCreatorFuncs();

	private:
		std::map<std::string,SnIdentifyCreateFunc> m_creatorFuncs;
};





#endif /*_SN_IDENTIFY_FACTORY_H_*/


