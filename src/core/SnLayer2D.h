#ifndef _SN_LAYER2D_H_
#define _SN_LAYER2D_H_

#include "stage/layer/FsLayer2D.h"

NS_FS_USE

class SnLayer2D:public Layer2D 
{
	public:
		void setName(std::string name) {m_name=name;}
		std::string getName(){return m_name;}
	private:
		std::string m_name;
};


#endif /*_SN_LAYER2D_H_*/
