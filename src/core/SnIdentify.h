#ifndef _SD_IDENTIFY_H_
#define _SD_IDENTIFY_H_


enum 
{
	SN_CLASS_IDENTIFY=0,
	SN_CLASS_PROJECT,
	SN_CLASS_SCENE,
	SN_CLASS_LAYER2D,

};

class SnIdentify
{
	public:
		virtual int getClassType()=0;
		virtual const char* className()=0;
		virtual ~SnIdentify();
};




#endif /*_SD_IDENTIFY_H_*/

