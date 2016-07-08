#ifndef _SN_ENTITY2D_H_
#define _SN_ENTITY2D_H_ 

#include "stage/entity/FsEntity2D.h"


class SnEntity2D:public Faeris::Entity2D 
{
	public:
		void setName(std::string name){m_name=name;}
		std::string getName(){return m_name;}



	private:
		std::string m_name;
	
};


#endif /*_SN_ENTITY2D_H_*/
