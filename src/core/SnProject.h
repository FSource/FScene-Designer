#ifndef _SN_PROJECT_H_
#define _SN_PROJECT_H_ 


#include <string>
#include <vector>
#include "core/SnIdentify.h"

class SnProject:public SnIdentify
{
	public:
		int getClassType();
		const char* className();

	public:
		std::string getName();

};


#endif
