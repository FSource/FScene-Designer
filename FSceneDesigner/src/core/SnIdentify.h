#ifndef _SD_IDENTIFY_H_
#define _SD_IDENTIFY_H_

#include <vector>
#include <string>
#include "FsVariant.h"
#include "support/util/FsArray.h"
#include "FsEnums.h"
#include <QStringList>
#include "FsObject.h"


enum 
{
	SN_CLASS_UNKOWN=-1,
	SN_CLASS_IDENTIFY=0,
	SN_CLASS_PROJECT=1,
	SN_CLASS_SCENE=2,
	SN_CLASS_LAYER2D=3,
	SN_CLASS_T_ENTITY2D=4,
	SN_CLASS_ENTITY2D=5,
	SN_CLASS_QUAD2D=6,
	SN_CLASS_LABEL_TTF=7,
	SN_CLASS_LABEL_BMP=8,
	SN_CLASS_PRESS_BUTTON,
	SN_CLASS_UI_WIDGET,
	SN_CLASS_PAGE_VIEW,
	SN_CLASS_LIST_VIEW,
	SN_CLASS_SCROLL_VIEW,
};

enum 
{
	SN_TYPE_NORMAL=0,
	SN_TYPE_ENUMS=1,
	SN_TYPE_EXTENDS=2,
};


enum 
{
	SN_EXTENDS_EDIT_UNKOWN=0,
	SN_EXTENDS_EDIT_FILEPATH=1,
};


class SnAttrTypeDesc
{
	public:
		SnAttrTypeDesc(const char* name,int type)
		{
			m_name=name;
			m_type=type;
			m_editType=SN_EXTENDS_EDIT_UNKOWN;
		}
		SnAttrTypeDesc(const char* name,int type,int editType)
		{
			m_name=name;
			m_type=type;
			m_editType=editType;
		}

		SnAttrTypeDesc(const char* name, QStringList enums)
		{
			m_type=SN_TYPE_ENUMS;
			m_name=name;
			m_enums=enums;
			m_editType=-1;
		}

	public:
		const char* getName() { return m_name.c_str(); }
		int getType() { return m_type; }
		int getEditorType(){return m_editType;}


		void addEnum(QString v) {m_enums<<v;}
		const QStringList& getEnums(){return m_enums;}

	private:
		std::string m_name;

		/* normal type */
		int m_type;
		QStringList m_enums;
		int m_editType;
};




class SnAttrGroupDesc
{
	public: 
		SnAttrGroupDesc(const char* name)
		{
			m_name=name;
		}
		~SnAttrGroupDesc()
		{
			int size=m_subAttr.size();
			for(int i=0;i<size;i++)
			{
				delete m_subAttr[i];
			}
			m_subAttr.clear();
		}

	public:
		void addAttrTypeDesc(SnAttrTypeDesc* sc)
		{
			m_subAttr.push_back(sc);
		}
		int getAttrTypeDescNu()
		{
			return m_subAttr.size();
		}
		SnAttrTypeDesc* getAttrTypeDesc(int index)
		{
			return m_subAttr[index];
		}
		const char* getName()
		{
			return m_name.c_str();
		}
	private:
		std::string m_name;
		std::vector<SnAttrTypeDesc*> m_subAttr;
};

class SnAttrGroupList 
{
	public:
		SnAttrGroupList() {}
	   	~SnAttrGroupList()
		{
			int size=m_groupList.size();
			for(int i=0;i<size;i++)
			{
				delete m_groupList[i];
			}
			m_groupList.clear();
		}

	public:
		void addAttrGroupDesc(SnAttrGroupDesc* desc)
		{
			m_groupList.push_back(desc);
		}

		int  getAttrGroupDescNu()
		{
			return m_groupList.size();
		}

		SnAttrGroupDesc* getAttrGroupDesc(int index)
		{
			return m_groupList[index];
		}


	private:
		std::vector<SnAttrGroupDesc*> m_groupList;
};








class SnIdentify
{
	public:
		SnIdentify();
		virtual ~SnIdentify();
	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);

		virtual void addIdentifyChild(SnIdentify* idenfy);
		virtual void removeIdentifyChild(SnIdentify* idenfy);
		virtual void clearIdentifyChild();


		virtual bool isDragEnabled();
		virtual bool isDropEnabled();

		virtual SnAttrGroupList* getAttributeList();


		virtual std::vector<SnIdentify*> getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse);
		virtual SnIdentify* getChildHitPoint(Faeris::Vector2f p,bool traverse);


		virtual Faeris::Vector3f getPositionInWorld();
		virtual void translateInWorld(float x,float y);
		virtual void translateXInWorld(float x,float y);
		virtual void translateYInWorld(float x,float y);
		virtual void rotate(float angle);

		virtual Faeris::Vector2f toXAxisProj(Faeris::Vector2f v);
		virtual Faeris::Vector2f toYAxisProj(Faeris::Vector2f v);

		virtual bool isAncestors(SnIdentify* id);

		virtual void getBoundSize2D(float* minx,float* maxx,float* miny,float* maxy);


		/* Attribute  Info */
		virtual void setIdentifyAttribute(const char* name,const Faeris::FsVariant& value);
		virtual Faeris::FsVariant getIdentifyAttribute(const char* name);

		virtual void setIdentifyAttributes(Faeris::FsDict* dict);


		virtual Faeris::FsDict* takeObjectFst();



	public:
		void setIdentifyName(const char* name);
		const char* getIdentifyName();

		void setIdentifyClassName(const char* name);
		const char* getIdentifyClassName();

	protected:
		SnAttrTypeDesc* createAttributeDesc(const char* name,int type);
		SnAttrTypeDesc* createAttributeDesc(const char* name,int type,int editor_type);
		SnAttrTypeDesc* createAttributeDesc(const char* name,const char* fn(int));
		Faeris::FsObject* variantToFst(const Faeris::FsVariant& v);

		virtual std::vector<std::string> getObjectFstAttrList();
		std::string m_className;

};


#endif /*_SD_IDENTIFY_H_*/

