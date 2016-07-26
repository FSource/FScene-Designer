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

void SnDataOperator::moveEntityToEntity(Faeris::Entity2D* en,Faeris::Entity2D* p)
{
	en->addRef();

	SnIdentify* e_id=dynamic_cast<SnIdentify*>(en);
	e_id->getIdentifyParent()->removeIdentifyChild(e_id);

	SnIdentify* e_p=dynamic_cast<SnIdentify*>(p);
	e_p->addIdentifyChild(e_id);

	en->decRef();
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
	id->setAttribute(name,value);
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



