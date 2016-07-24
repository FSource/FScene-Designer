#ifndef _SD_IDENTIFY_H_
#define _SD_IDENTIFY_H_

#include <vector>
#include <string>
#include "FsVariant.h"
#include "support/util/FsArray.h"
#include "FsEnums.h"
#include <QStringList>


enum 
{
	SN_CLASS_IDENTIFY=0,
	SN_CLASS_PROJECT,
	SN_CLASS_SCENE,
	SN_CLASS_LAYER2D,
	SN_CLASS_T_ENTITY2D,
	SN_CLASS_ENTITY2D,
	SN_CLASS_QUAD2D,
};

enum 
{
	SN_TYPE_NORMAL=0,
	SN_TYPE_ENUMS=1,
};



class SnAttrTypeDesc
{
	public:
		SnAttrTypeDesc(const char* name,int type)
		{
			m_name=name;
			m_type=type;
		}

		SnAttrTypeDesc(const char* name, QStringList enums)
		{
			m_type=SN_TYPE_ENUMS;
			m_name=name;
			m_enums=enums;
		}

	public:
		const char* getName() { return m_name.c_str(); }
		int getType() { return m_type; }

		void addEnum(QString v) {m_enums<<v;}
		const QStringList& getEnums(){return m_enums;}

	private:
		std::string m_name;

		/* normal type */
		int m_type;
		QStringList m_enums;

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

		virtual void setAttribute(const char* name,const Faeris::FsVariant& value);
		virtual Faeris::FsVariant getAttribute(const char* name);

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

	public:
		void setIdentifyName(const char* name);
		const char* getIdentifyName();

	protected:
		SnAttrTypeDesc* createAttributeDesc(const char* name,int type);
		SnAttrTypeDesc* createAttributeDesc(const char* name,const char* fn(int));
};


#endif /*_SD_IDENTIFY_H_*/

