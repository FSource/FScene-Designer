#ifndef _SN_LABEL_TTF_H_
#define _SN_LABEL_TTF_H_ 


#include "stage/entity/FsLabelTTF.h"
#include "SnTEntity2D.h"


class SnLabelTTF:public TSnEntity2D<Faeris::LabelTTF> 
{
	public:
		FS_CLASS_DECLARE(SnLabelTTF);

	public:
		static SnLabelTTF* newInstance(Faeris::FsDict* dict);

	public:
		SnLabelTTF();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnAttrGroupList* getAttributeList();
		std::vector<std::string> getObjectFstAttrList();

};

#endif /*_SN_LABEL_TTF_H_*/

