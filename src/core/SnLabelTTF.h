#ifndef _SN_LABEL_TTF_H_
#define _SN_LABEL_TTF_H_ 


#include "stage/entity/FsLabelTTF.h"
#include "SnTEntity2D.h"


class SnLabelTTF:public TSnEntity2D<Faeris::LabelTTF> 
{
	public:
		static SnLabelTTF* newInstance(Faeris::FsDict* dict);

	public:
		SnLabelTTF();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnAttrGroupList* getAttributeList();

};

#endif /*_SN_LABEL_TTF_H_*/

