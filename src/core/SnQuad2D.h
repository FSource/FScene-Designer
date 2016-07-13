#ifndef _SN_QUAD_2D_H_
#define _SN_QUAD_2D_H_ 

#include "stage/entity/FsQuad2D.h"
#include "SnTEntity2D.h"

class SnQuad2D:public TSnEntity2D<Faeris::Quad2D> 
{
	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();
		virtual SnAttrGroupList* getAttributeList();

};




#endif /*_SN_QUAD_2D_H_*/

