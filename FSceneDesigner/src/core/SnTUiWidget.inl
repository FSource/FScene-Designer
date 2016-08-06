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



#endif /*_SN_T_UI_WIDGET_INL_*/

