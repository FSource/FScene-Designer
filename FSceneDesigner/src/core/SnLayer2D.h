#ifndef _SN_LAYER2D_H_
#define _SN_LAYER2D_H_

#include "math/FsRect2D.h"
#include "stage/layer/FsLayer2D.h"
#include "SnIdentify.h"




class SnLayer2D:public SnIdentify, public Faeris::Layer2D 
{
	public:
		FS_CLASS_DECLARE(SnLayer2D);

	public:
		static SnLayer2D* newInstance(Faeris::FsDict* dict);

	public:
		SnLayer2D();
		~SnLayer2D();

	public:
		virtual int identifyType();
		virtual const char* identifyTypeName();

		virtual SnAttrGroupList* getAttributeList();

		virtual SnIdentify* getIdentifyParent();
		virtual int getIdentifyChildNu();
		virtual SnIdentify* getIdentifyChild(int index);
		virtual int getIdentifyChildIndex(SnIdentify* id);


		virtual void addIdentifyChild(SnIdentify* idenfy);
		virtual void removeIdentifyChild(SnIdentify* idenfy);
		virtual void clearIdentifyChild();


		virtual bool isDragEnabled();
		virtual bool isDropEnabled();

		virtual std::vector<SnIdentify*> getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse);
		virtual SnIdentify* getChildHitPoint(Faeris::Vector2f p,bool traverse);



	public:
		void setEditViewArea(Faeris::Rect2D rect){m_editViewArea=rect;}
		Faeris::Rect2D getEditViewArea(){return m_editViewArea;}


	public:
		virtual std::vector<std::string> getObjectFstAttrList();

	private:
		Faeris::FsArray* m_array;
		Faeris::Rect2D m_editViewArea;

};


#endif /*_SN_LAYER2D_H_*/
