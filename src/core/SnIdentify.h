#ifndef _SD_IDENTIFY_H_
#define _SD_IDENTIFY_H_

#include <string>

enum 
{
	SN_CLASS_IDENTIFY=0,
	SN_CLASS_PROJECT,
	SN_CLASS_SCENE,
	SN_CLASS_LAYER2D,
	SN_CLASS_T_ENTITY2D,
	SN_CLASS_ENTITY2D,
	SN_CLASS_QUAD2D,
};

class SnIdentify
{
	public:
		SnIdentify();
		virtual ~SnIdentify();
	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);


		virtual bool isDragEnabled();
		virtual bool isDropEnabled();

	public:
		void setIdentifyName(const char* name){m_identifyName=name;}
		const char* getIdentifyName(){return m_identifyName.c_str();}

	private:
		std::string m_identifyName;

};




#endif /*_SD_IDENTIFY_H_*/

