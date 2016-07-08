#ifndef _SN_LAYER2D_H_
#define _SN_LAYER2D_H_
#include "stage/layer/FsLayer2D.h"
class SnEntity2D;




class SnLayer2D:public Faeris::Layer2D 
{
	public:
		SnLayer2D();
		~SnLayer2D();
	public:
		void setName(std::string name) {m_name=name;}
		std::string getName(){return m_name;}

	public:
		void add(Faeris::Entity* entity) FS_OVERRIDE;
		void remove(Faeris::Entity* entity) FS_OVERRIDE;
		void clearEntity() FS_OVERRIDE;

public:
		int getEntityNu();
		Faeris::Entity2D * getEntity(int index);

	private:
		std::string m_name;
		Faeris::FsArray* m_array;
};


#endif /*_SN_LAYER2D_H_*/
