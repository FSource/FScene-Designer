#ifndef _SN_CLASS_H_
#define _SN_CLASS_H_ 


#define SN_CLASS_ATTR_SET_GET_FUNCTION(cls,set,get,t)  \
	static  void cls##_##set(Faeris::FsObject* o,const t* v) \
	{ \
		cls* ob=dynamic_cast<cls*>(o); \
		ob->set(*v); \
	} \
	static const t* cls##_##get(Faeris::FsObject* o)  \
	{ \
		cls* ob=dynamic_cast<cls*>(o); \
		static t temp; \
		temp=ob->get(); \
		return &temp; \
	} \



#define SN_CLASS_ATTR_SET_GET_CHARS_FUNCTION(cls,set,get)  \
	static  void cls##_##set(Faeris::FsObject* o,const char* v) \
	{ \
		cls* xx=dynamic_cast<cls*>(o); \
		xx->set(v); \
	} \
	static const char* cls##_##get(Faeris::FsObject* o)  \
	{ \
		cls* xy=dynamic_cast<cls*>(o); \
		const char* ret= xy->get(); \
		return ret; \
	} \


#define SN_CLASS_ATTR_GET_CHARS_FUNCTION(cls,get)  \
	static const char* cls##_##get(Faeris::FsObject* o)  \
	{ \
		cls* ob=dynamic_cast<cls*>(o); \
		return ob->get(); \
	} \



#endif /*_SN_CLASS_H_*/
