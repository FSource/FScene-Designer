#ifndef _SN_IO_OPERATOR_H_
#define _SN_IO_OPERATOR_H_ 

#include <string>
#include <vector>

class SnProject;
class SnIdentify;


class SnIoOperator
{

	public:
		SnIoOperator();
		~SnIoOperator();

	public:
		SnProject* loadProject(const char* filename);
		bool saveProject(SnProject* proj,const char* name);


		void exportProject(SnProject* proj,const char* filename);
		void exportSnIdentify(SnIdentify* id,const char* filename);
};




#endif /*_SN_IO_OPERATOR_H_*/
