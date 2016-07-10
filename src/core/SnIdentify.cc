#include "core/SnIdentify.h"

SnIdentify::SnIdentify()
{
	m_identifyName="";
}
SnIdentify::~SnIdentify()
{
}

int SnIdentify::identifyType()
{
	return SN_CLASS_IDENTIFY;
}
const char* SnIdentify::identifyTypeName()
{
	return "SnIdentify";
}

SnIdentify* SnIdentify::getIdentifyParent(){return NULL;}
int SnIdentify::getIdentifyChildNu( ){return 0;}
SnIdentify* SnIdentify:: getIdentifyChild(int ){return NULL;}
int SnIdentify::getIdentifyChildIndex(SnIdentify* ){return -1;}


bool SnIdentify::isDragEnabled(){return false;}
bool SnIdentify::isDropEnabled(){return false;}

