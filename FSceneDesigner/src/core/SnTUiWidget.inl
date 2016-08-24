#ifndef _SN_T_UI_WIDGET_INL_
#define _SN_T_UI_WIDGET_INL_ 

template<typename T> 
SnAttrGroupList* TSnUiWidget<T>::getAttributeList()
{
	SnAttrGroupList* glist=TSnEntity2D<T>::getAttributeList();

	SnAttrGroupDesc* group =new SnAttrGroupDesc("UiWidget");

	group->addAttrTypeDesc(createAttributeDesc("scissorEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgEnabled",SN_TYPE_NORMAL));
	group->addAttrTypeDesc(createAttributeDesc("bgTextureUrl",SN_TYPE_EXTENDS,SN_EXTENDS_EDIT_FILEPATH));
	group->addAttrTypeDesc(createAttributeDesc("bgColor",SN_TYPE_NORMAL));

	glist->addAttrGroupDesc(group);
	return glist;
}

template<typename T> 
SnIdentify* TSnUiWidget<T>::getIdentifyParent()
{
	UiWidget* widget=getParentWidget();
	if(widget!=NULL)
	{
		return dynamic_cast<SnIdentify*>(widget);
	}

	return TSnEntity2D<T>::getIdentifyParent();

}
template<typename T> 
std::vector<std::string> TSnUiWidget<T>::getObjectFstAttrList()
{
	std::vector<std::string> ret=TSnEntity2D<T>::getObjectFstAttrList();

	ret.push_back("scissorEnabled");
	ret.push_back("bgEnabled");
	ret.push_back("bgTextureUrl");
	ret.push_back("bgColor");
	return ret;

}

template<typename T>
 SnIdentify* TSnUiWidget<T>::getChildHitPoint(Faeris::Vector2f point,bool traverse)
{
	if(getScissorEnabled())
	{
		if(!SnUtil::identifyHitPoint(this,point))
		{
			return NULL;
		}
	}

	return TSnEntity2D<T>::getChildHitPoint(point,traverse);


}

template<typename T>
std::vector<SnIdentify*> TSnUiWidget<T>::getChildInArea(Faeris::Vector2f& start,Faeris::Vector2f& end,bool traverse)
{
	std::vector<SnIdentify* > ret;
	int child_nu=getIdentifyChildNu();

	float minx,maxx,miny,maxy;
	getTRSBoundSize2D(&minx,&maxx,&miny,&maxy);

	Faeris::Vector2f ts(minx,miny);
	Faeris::Vector2f te(maxx,maxy);


	for(int i=0;i<child_nu;i++)
	{
		SnIdentify* id=getIdentifyChild(i);

		if(SnUtil::identifyInRect(id,start,end))
		{
			if(getScissorEnabled())
			{
				if(SnUtil::identifyInRect(id,ts,te))
				{
					ret.push_back(id);
				}
			}
			else 
			{
				ret.push_back(id);
			}
		}

		if(traverse)
		{
			std::vector<SnIdentify*> r=id->getChildInArea(start,end,traverse);
			ret.insert(ret.end(),r.begin(),r.end());
		}
	}

	return ret;
}

template<typename T>
bool TSnUiWidget<T>::filterExportValue(const char* name,const Faeris::FsVariant& vs)
{
	if(strcmp(name,"touchEnabled")==0)
	{
		return false;
	}
	else if(strcmp(name,"touchesEnabled")==0)
	{
		return false;
	}
	else if(strcmp(name,"touchDispatchEnabled")==0)
	{
		return false;
	}
	else if(strcmp(name,"touchesDispatchEnabled")==0)
	{
		return false;
	}
	else if(strcmp(name,"scissorEnabled")==0)
	{
		if(vs.getType()==Faeris::E_FsType::FT_B_1)
		{
			bool value=*(bool *)vs.getValue();
			if(value)
			{
				return true;
			}
		}
	}
	else if(strcmp(name,"bgEnabled")==0)
	{

		if(vs.getType()==Faeris::E_FsType::FT_B_1)
		{
			bool value=*(bool *)vs.getValue();
			if(!value)
			{
				return true;
			}
		}

	}
	else if(strcmp(name,"bgTextureUrl")==0)
	{
		if(vs.getType()==Faeris::E_FsType::FT_CHARS)
		{
			const char* value=(char*)vs.getValue();
			if(strcmp(value,"")==0)
			{
				return true;
			}
		}
	}
	else if(strcmp(name,"bgColor")==0)
	{
		if(vs.getType()==Faeris::E_FsType::FT_COLOR_4)
		{
			Faeris::Color4f value=*(Faeris::Color4f*)vs.getValue();
			if(value.equal(Faeris::Color4f(1,1,1,1)))
			{
				return true;
			}
		}

	}


	return  TSnEntity2D<T>::filterExportValue(name,vs);
}


#endif /*_SN_T_UI_WIDGET_INL_*/











