#include <assert.h>
#include "operator/SnDataOperator.h"
#include "core/SnProject.h"

#include "SnGlobal.h"
#include "SnMsgCenter.h"
#include "core/SnScene.h"
#include "core/SnLayer2D.h"


NS_FS_USE

SnDataOperator::SnDataOperator()
{
}

SnDataOperator::~SnDataOperator()
{
}


SnProject* SnDataOperator::getCurProject()
{
    return SnGlobal::getProject();
}


void SnDataOperator::setCurProject(SnProject* proj)
{
    SnGlobal::setProject(proj);
	SnGlobal::msgCenter()->emitCurProjectChange();
}

SnScene* SnDataOperator::getCurScene()
{
    SnProject* proj=getCurProject();
    if(proj)
    {
        return proj->getCurScene();
    }
    return NULL;
}

SnIdentify* SnDataOperator::getCurrentIdentify()
{
    SnProject* proj=getCurProject();
    if(proj)
    {
        return proj->getCurrentIdentify();
    }
	return NULL;

}

SnLayer2D* SnDataOperator::getCurrentLayer()
{

    SnProject* proj=getCurProject();
    if(proj)
    {
        return proj->getCurrentLayer();
    }
	return NULL;
}

void SnDataOperator::setSceneName(SnScene* sn,std::string name)
{
	sn->setIdentifyName(name.c_str());
}

void SnDataOperator::addLayer2D(SnLayer2D* ly)
{
	getCurScene()->push(ly);

	SnGlobal::msgCenter()->emitLayer2DAdd(ly);
}

void SnDataOperator::reindexLayer2D(SnLayer2D* l_from,int index)
{
	Scene* sn=l_from->getScene();

	l_from->addRef();
	sn->remove(l_from);
	sn->insert(index,l_from);
	l_from->decRef();

	SnGlobal::msgCenter()->emitLayer2DAdd(l_from);
}

void SnDataOperator::moveEntityToLayer(Faeris::Entity2D* en,SnLayer2D* layer)
{
	en->addRef();
	
	SnIdentify* e_id=dynamic_cast<SnIdentify*>(en);
	e_id->getIdentifyParent()->removeIdentifyChild(e_id);

	layer->addIdentifyChild(e_id);
	en->decRef();

	SnGlobal::msgCenter()->emitLayer2DAdd(layer);
}

void SnDataOperator::moveIdentifyToIdentify(SnIdentify* id,SnIdentify* p)
{
	assert(p->acceptChild(id));

	id->getIdentifyParent()->removeIdentifyChild(id);

	p->addIdentifyChild(id);
	SnGlobal::msgCenter()->emitLayer2DAdd(NULL);
}


void SnDataOperator::translateInWorld(std::vector<SnIdentify*> ids_root,float x,float y)
{
	int ids_root_size=ids_root.size();
	for(int i=0;i<ids_root_size;i++)
	{
		SnIdentify* id_root=ids_root[i];
		id_root->translateInWorld(x,y);
		SnGlobal::msgCenter()->emitIdentifyAttributeChange(id_root,"position");
	}
}

void SnDataOperator::rotate(std::vector<SnIdentify*> ids_root,float angle)
{

	int ids_root_size=ids_root.size();
	for(int i=0;i<ids_root_size;i++)
	{
		SnIdentify* id_root=ids_root[i];
		id_root->rotate(angle);
		SnGlobal::msgCenter()->emitIdentifyAttributeChange(id_root,"rotateZ");
	}

}

void SnDataOperator::scale(std::vector<SnIdentify*> ids_root,float sx,float sy)
{
	int ids_root_size=ids_root.size();

	for(int i=0;i<ids_root_size;i++)
	{
		SnIdentify* id_root=ids_root[i];
		Entity2D* en=dynamic_cast<Entity2D*>(id_root);

		Vector3f rs=en->getScale();

		rs.x*=sx;
		rs.y*=sy;

		en->setScale(rs);

		SnGlobal::msgCenter()->emitIdentifyAttributeChange(id_root,"scale");
	}
}



void SnDataOperator::setBoundSize2D(std::vector<SnIdentify*> ids_root,float r_minx,float r_maxx,float r_miny,float r_maxy)

{
	int ids_root_size=ids_root.size();
	for(int i=0;i<ids_root_size;i++)
	{
		SnIdentify* id_root=ids_root[i];
		Entity2D* en=dynamic_cast<Entity2D*>(id_root);

		if(!en) 
		{
			continue;
		}

		float minx,maxx,miny,maxy;
		en->getBoundSize2D(&minx,&maxx,&miny,&maxy);

		float t_minx=minx*r_minx;
		float t_maxx=maxx*r_maxx;
		float t_miny=miny*r_miny;
		float t_maxy=maxy*r_maxy;

		Vector2f anchor=en->getAnchor();

		float posx=t_minx*(1-anchor.x)+t_maxx*anchor.x;
		float posy=t_miny*(1-anchor.y)+t_maxy*anchor.y;

		Matrix4* mat=en->getLocalMatrix();

		Matrix4 t_mat=*mat;
		t_mat.setTranslate(0,0,0);

		Vector3f t_pos=t_mat.mulVector3(Vector3f(posx,posy,0));

		  
		float s_x=t_maxx-t_minx;
		float s_y=t_maxy-t_miny;


		en->move(t_pos.x,t_pos.y,0);

		en->setSize(s_x,s_y);

		SnGlobal::msgCenter()->emitIdentifyAttributeChange(id_root,"position");
		SnGlobal::msgCenter()->emitIdentifyAttributeChange(id_root,"size");
	}
}



void SnDataOperator::setIdentifyAttribute(SnIdentify* id,const char* name,const Faeris::FsVariant& value)
{
	id->setIdentifyAttribute(name,value);
	SnGlobal::msgCenter()->emitIdentifyAttributeChange(id,name);
}

void SnDataOperator::setIdentifyCurrentAndSelect(SnIdentify* ct_id,const std::vector<SnIdentify*>& st_ids)
{
	SnProject* proj=getCurProject();
	if(!proj)
	{
		return;
	}




	if(ct_id!=NULL)
	{
		if(dynamic_cast<SnLayer2D*>(ct_id))
		{
			std::vector<SnIdentify*> real_select;
			proj->setCurrentAndSelectIdentify(ct_id,real_select);
			SnGlobal::msgCenter()->emitCurrrentAndSelectsChange(ct_id,real_select);

			/*
			   Layer2D* ct_layer=dynamic_cast<Layer2D*>(ct_id);
			   int size=st_ids.size();
			   for(int i=0;i<size;i++)
			   {
			   SnIdentify* s_id=st_ids[i];

			   Entity2D* en=dynamic_cast<Entity2D*>(s_id);
			   if(en)
			   {
			   if(en->getLayer()==ct_layer)
			   {
			   real_select.push_back(s_id);
			   }
			   }
			   }
			   */
		}
		else if(dynamic_cast<Entity2D*>(ct_id))
		{
			std::vector<SnIdentify*> real_select;
			Entity2D* ct_en=dynamic_cast<Entity2D*>(ct_id);
			Layer2D* layer=(Layer2D*) ct_en->getLayer();

			int size=st_ids.size();
			for(int i=0;i<size;i++)
			{
				SnIdentify* s_id=st_ids[i];

				Entity2D* en=dynamic_cast<Entity2D*>(s_id);
				if(en)
				{
					if(en->getLayer()==layer)
					{
						real_select.push_back(s_id);
					}
				}
			}
			proj->setCurrentAndSelectIdentify(ct_id,real_select);
			SnGlobal::msgCenter()->emitCurrrentAndSelectsChange(ct_id,real_select);
		}
		else
		{
			std::vector<SnIdentify* > real_select;
			proj->setCurrentAndSelectIdentify(ct_id,real_select);
			SnGlobal::msgCenter()->emitCurrrentAndSelectsChange(ct_id,real_select);

		}

	}
	else 
	{
		std::vector<SnIdentify* > real_select;
		proj->setCurrentAndSelectIdentify(NULL,real_select);
		SnGlobal::msgCenter()->emitCurrrentAndSelectsChange(ct_id,real_select);
	}
}


std::vector<SnIdentify*> SnDataOperator::getSelectedIdentify()
{
	SnProject* proj=getCurProject();
	if(!proj)
	{
		return std::vector<SnIdentify*>();
	}


	return proj->getSelectedIdentify();
}

std::vector<SnIdentify*> SnDataOperator::getSelectedIdentifyRoot()
{
	SnProject* proj=getCurProject();
	if(!proj)
	{
		return std::vector<SnIdentify*>();
	}


	return proj->getSelectedIdentifyRoot();
}


void SnDataOperator::setEditMode(SN_EditMode mode)
{

	SnProject* proj=getCurProject();
	if(!proj)
	{

		return ;
	}


	proj->setEditMode(mode);
	SnGlobal::msgCenter()->emitEditModeChange(mode);
}

void SnDataOperator::setTranslateMode(SN_TranslateMode mode)
{
	SnProject* proj=getCurProject();
	if(!proj)
	{
		return;
	}

	proj->setTranslateMode(mode);
	SnGlobal::msgCenter()->emitTranslateModeChange(mode);
}


/* drop */
void SnDataOperator::addIdentifyFromUrl(Faeris::Vector2f pos,const std::string& filename)
{
	SnProject* proj=getCurProject();
	if(!proj)
	{
		return;
	}

	SnLayer2D* ly=getCurrentLayer();
	if(ly==NULL)
	{
		return;
	}



	std::string relative_path=SnUtil::toRelativePath(proj->getDirName().c_str(),filename.c_str());

	SnIdentify* identify=SnUtil::createIdentifyFromUrl(filename.c_str(),relative_path.c_str());

	if(identify==NULL)
	{
		return;
	}

	Entity2D* en=dynamic_cast<Entity2D*>(identify);
	assert(en);

	std::vector<SnIdentify*> select=getSelectedIdentify();
	if(select.size()>0)
	{
		if(select[0]->acceptChild(identify)&&SnUtil::identifyHitPoint(select[0],pos))
		{
			select[0]->addIdentifyChild(identify);
		}
		else 
		{
			ly->addIdentifyChild(identify);
		}
	}
	else 
	{
		ly->addIdentifyChild(identify);
	}

	en->setPositionInWorld(Vector3f(pos.x,pos.y,0));

	SnGlobal::msgCenter()->emitIdentifyAdd(identify);

	std::vector<SnIdentify*> new_select;
	new_select.push_back(identify);

	proj->setCurrentAndSelectIdentify(identify,new_select);

	SnGlobal::msgCenter()->emitCurrrentAndSelectsChange(identify,new_select);

}

void SnDataOperator::addIdentify(SnIdentify* identify)
{

	SnProject* proj=getCurProject();
	if(!proj)
	{
		delete identify ;
		return;
	}

	SnLayer2D* ly=getCurrentLayer();
	if(ly==NULL)
	{
		delete identify ;
		return;
	}

	Entity2D* en=dynamic_cast<Entity2D*>(identify);
	assert(en);

	std::vector<SnIdentify*> select=getSelectedIdentify();
	if(select.size()>0)
	{
		if(select[0]->acceptChild(identify))
		{
			select[0]->addIdentifyChild(identify);
		}
		else 
		{
			ly->addIdentifyChild(identify);
		}
	}
	else 
	{
		ly->addIdentifyChild(identify);
	}


	SnGlobal::msgCenter()->emitIdentifyAdd(identify);

	std::vector<SnIdentify*> new_select;
	new_select.push_back(identify);

	proj->setCurrentAndSelectIdentify(identify,new_select);

	SnGlobal::msgCenter()->emitCurrrentAndSelectsChange(identify,new_select);

}



void SnDataOperator::deleteSelect()
{
	std::vector<SnIdentify*> ids=getSelectedIdentifyRoot();
	int size=ids.size();

	setIdentifyCurrentAndSelect(NULL,std::vector<SnIdentify*>());
	SnGlobal::msgCenter()->emitCurrrentAndSelectsChange(NULL, std::vector<SnIdentify*>());


	for(int i=0;i<size;i++)
	{
		SnIdentify* id=ids[i];
		SnIdentify* p=id->getIdentifyParent();
		assert(p);
		p->removeIdentifyChild(id);
	}

	SnGlobal::msgCenter()->emitIdentifyDelete(ids);

}




/* redo/undo */
bool SnDataOperator::canRedo()
{
	return false;
	//  return SnGlobal::canRedo();
}

bool SnDataOperator::canUndo()
{
	return false;
	// return SnGlobal::canUndo();
}

void SnDataOperator::redo()
{

}

void SnDataOperator::undo()
{

}



