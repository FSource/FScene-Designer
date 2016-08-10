#include "core/SnIdentify.h"
#include "support/util/FsDict.h"
#include "support/util/FsString.h"

NS_FS_USE
SnIdentify::SnIdentify()
{
}
SnIdentify::~SnIdentify()
{
}

int SnIdentify::identifyType()
{
	return SN_CLASS_IDENTIFY;
}
const char* SnIdentify::identifyTypeName()
{
	return "SnIdentify";
}

SnIdentify* SnIdentify::getIdentifyParent(){return NULL;}
int SnIdentify::getIdentifyChildNu( ){return 0;}
SnIdentify* SnIdentify:: getIdentifyChild(int ){return NULL;}

int SnIdentify::getIdentifyChildIndex(SnIdentify* id)
{
	int ident_nu=getIdentifyChildNu();
	for(int i=0;i<ident_nu;i++)
	{
		SnIdentify* c=getIdentifyChild(i);
		if(c==id)
		{
			return i;
		}
	}
	return -1;
}

void SnIdentify::addIdentifyChild(SnIdentify* ){}
void SnIdentify::removeIdentifyChild(SnIdentify* ){}
void SnIdentify::clearIdentifyChild(){}
bool SnIdentify::acceptChild(SnIdentify* id){return false;}




bool SnIdentify::isDragEnabled(){return false;}




SnAttrGroupList* SnIdentify::getAttributeList()
{
	SnAttrGroupDesc* group=new SnAttrGroupDesc("FsObject");

	group->addAttrTypeDesc(createAttributeDesc("className",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("objectName",SN_TYPE_NORMAL));

	SnAttrGroupList* g_list=new SnAttrGroupList;
	g_list->addAttrGroupDesc(group);

	return g_list;
}


void SnIdentify::setIdentifyAttribute(const char* name,const FsVariant&  value)
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	ob->setAttribute(name,value);
}

void SnIdentify::setIdentifyAttributes(Faeris::FsDict* dict)
{
	FsDict::Iterator* iter=dict->takeIterator();
	while(!iter->done())
	{
		FsString* name=(FsString*)iter->getKey();
		FsObject* value=iter->getValue();
		setIdentifyAttribute(name->cstr(),value);
		iter->next();
	}
	delete iter;

}


FsVariant SnIdentify::getIdentifyAttribute(const char* name)
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	FsVariant ret= ob->getAttribute(name);
	return ret;
}

void SnIdentify::setIdentifyName(const char* name)
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	ob->setObjectName(name);
}

const char* SnIdentify::getIdentifyName()
{
	FsObject* ob=dynamic_cast<FsObject*>(this);
	return ob->getObjectName();
}

void SnIdentify::setIdentifyClassName(const char* name)
{
	m_className=name;
}

const char* SnIdentify::getIdentifyClassName()
{
	return m_className.c_str();
}


std::vector<SnIdentify*> SnIdentify::getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse)
{
	return std::vector<SnIdentify*>();
}

SnIdentify* SnIdentify::getChildHitPoint(Faeris::Vector2f p,bool traverse)
{
	return NULL;
}

void SnIdentify::translateInWorld(float x,float y)
{ 
}

void SnIdentify::translateXInWorld(float x,float y)
{
}

void SnIdentify::translateYInWorld(float x,float y)
{
}

void SnIdentify::rotate(float angle)
{
}


Vector3f SnIdentify::getPositionInWorld()
{
	return Vector3f();
}



Vector2f SnIdentify::toXAxisProj(Vector2f v)
{
	return v;
}

Vector2f SnIdentify::toYAxisProj(Vector2f v)
{
	return v;
}


void SnIdentify::getBoundSize2D(float* minx,float* maxx,float* miny,float* maxy)
{

}


bool SnIdentify::isAncestors(SnIdentify* id)
{
	SnIdentify* p=getIdentifyParent();

	while(p)
	{
		if(p==id)
		{
			return true;
		}
		p=p->getIdentifyParent();
	}
	return false;
}


Faeris::FsDict* SnIdentify::takeObjectFst()
{
	FsDict* dict=FsDict::create();
	std::vector<std::string> p=getObjectFstAttrList();

	int size=p.size();
	for(int i=0;i<size;i++)
	{
		FsVariant v=getIdentifyAttribute(p[i].c_str());
		FsObject* ob=variantToFst(v);
		if(ob)
		{
			dict->insert(FsString::create(p[i].c_str()),ob);
		}
		else 
		{
			FS_TRACE_WARN("can't get %s attribute info",p);
		}
	}
	return dict;
}




SnAttrTypeDesc* SnIdentify::createAttributeDesc(const char* name,int type)
{
	return new SnAttrTypeDesc(name,type);
}

SnAttrTypeDesc* SnIdentify::createAttributeDesc(const char* name,int type,int editor_type)
{
	return new SnAttrTypeDesc(name,type,editor_type);
}

SnAttrTypeDesc* SnIdentify::createAttributeDesc(const char* name,const char* fn(int))
{
	QStringList e_list;
	int index=0;
	while(fn(index)!=NULL)
	{
		e_list<<fn(index);
		index++;
	}
	return new SnAttrTypeDesc(name,e_list);
}


Faeris::FsObject* SnIdentify::variantToFst(const FsVariant& t_value)
{
	E_FsType ftype=t_value.getType();
	switch(ftype)
	{
		case E_FsType::FT_IN_VALID:
			{
				FS_TRACE_WARN("Error FsVariant To Cast");
				return NULL;
			}

		case E_FsType::FT_B_1:
			{
				bool value=*(bool*)t_value.getValue();
				if(value)
				{
					return FsString::create("true");
				}
				else 
				{
					return FsString::create("false");
				}
			}
			break;
		case E_FsType::FT_I_1:
			{
				char buf[128];
				int value =*(int*)t_value.getValue();
				sprintf(buf,"%d",value);
				return FsString::create(buf);
			}
		case E_FsType::	FT_F_1:
			{
				char buf[128];
				float value= *(float*)t_value.getValue();
				sprintf(buf,"%.2f",value);
				return FsString::create(buf);
				break;
			}
		case E_FsType::FT_F_2:
			{
				FsArray* ret=FsArray::create();
				Vector2 value=*(Vector2*)t_value.getValue();

				char buf[128];
				sprintf(buf,"%.2f",value.v[0]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[1]);
				ret->push(FsString::create(buf));

				return ret;
			}
		case E_FsType::FT_F_3:
			{

				FsArray* ret=FsArray::create();
				Vector3 value=*(Vector3*)t_value.getValue();

				char buf[128];
				sprintf(buf,"%.2f",value.v[0]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[1]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[2]);
				ret->push(FsString::create(buf));

				return ret;
				break;
			}
		case E_FsType::FT_F_4:
			{

				FsArray* ret=FsArray::create();
				Vector3 value=*(Vector3*)t_value.getValue();

				char buf[128];
				sprintf(buf,"%.2f",value.v[0]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[1]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[2]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[3]);
				ret->push(FsString::create(buf));

				return ret;
				break;
			}

		case E_FsType::FT_COLOR_4:
			{
				FsArray* ret=FsArray::create();
				Color4f value=*(Color4f*)t_value.getValue();

				char buf[128];
				sprintf(buf,"%.2f",value.r);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.g);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.b);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.a);
				ret->push(FsString::create(buf));

				return ret;
				break;
			}

		case E_FsType::FT_CHARS:
			{
				const char* value=(char*)t_value.getValue();
				return FsString::create(value);
			}
		case E_FsType::FT_F_RECT2D:
			{
				FsArray* ret=FsArray::create();
				Rect2D value=*(Rect2D*)t_value.getValue();

				char buf[128];
				sprintf(buf,"%.2f",value.v[0]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[1]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[2]);
				ret->push(FsString::create(buf));
				sprintf(buf,"%.2f",value.v[3]);
				ret->push(FsString::create(buf));

				return ret;
				break;
			}
		case E_FsType::FT_DICT:
			{
				FsDict* value=(FsDict*) t_value.getValue();
				return value;
				break;
			}
		case E_FsType::FT_ARRAY:
			{
				FsArray* value=(FsArray*) t_value.getValue();
				return value;
				break;
			}
	}

	assert(0);
	return NULL;
}


std::vector<std::string> SnIdentify::getObjectFstAttrList()
{
	std::vector<std::string> ret;
	ret.push_back("editClass");
	ret.push_back("className");
	ret.push_back("objectName");
	return ret;
}



