#ifndef _SN_ENTITY_2D_H_
#define _SN_ENTITY_2D_H_

#include "SnTEntity2D.h"
#include "stage/entity/FsEntity2D.h"


class SnEntity2D:public TSnEntity2D<Faeris::Entity2D>
{
	public:
		static SnEntity2D* newInstance(Faeris::FsDict* dict);

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();
};


#endif /*_SN_ENTITY_2D_H_*/

