#ifndef _SN_LABEL_BITMAP_H_
#define _SN_LABEL_BITMAP_H_ 

#include "stage/entity/FsLabelBitmap.h"
#include "SnTEntity2D.h"

class SnLabelBitmap:public TSnEntity2D<Faeris::LabelBitmap> 
{
	public:
		FS_CLASS_DECLARE(SnLabelBitmap);

	public:
		static SnLabelBitmap* newInstance(Faeris::FsDict* dict);

	public:
		SnLabelBitmap();


	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnAttrGroupList* getAttributeList();
		std::vector<std::string> getObjectFstAttrList();
};



#endif /*_SN_LABEL_BITMAP_H_*/

