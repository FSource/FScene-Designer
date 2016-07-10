#ifndef _SN_TEST_H_
#define _SN_TEST_H_ 

#include "core/SnScene.h"
#include "core/SnLayer2D.h"
#include "core/SnProject.h"
#include "core/SnEntity2D.h"
#include "core/SnQuad2D.h"

static SnProject* SnTest_CreateProject()
{

	SnProject* proj=new SnProject();

	proj->setDirName("E:/");
	proj->setFileName("temp.fscene");
	proj->setName("MainScene");

	SnScene* sn=proj->getCurScene();
	sn->setIdentifyName("MainScene");

	SnLayer2D* l1=new SnLayer2D;
	l1->setIdentifyName("BackGround");

	SnLayer2D* l2=new SnLayer2D;
	l2->setIdentifyName("BackGround2");

	SnLayer2D* l3=new SnLayer2D;
	l3->setIdentifyName("Fight");

	SnLayer2D* l4=new SnLayer2D;
	l4->setIdentifyName("UiLayer");

	sn->push(l1);
	sn->push(l2);
	sn->push(l3);
	sn->push(l4);

	SnEntity2D* en1=new SnEntity2D();
	en1->setIdentifyName("Entity1");
	l4->add(en1);

	SnEntity2D* en2=new SnEntity2D();
	en2->setIdentifyName("Entity2");
	l4->add(en2);

	SnEntity2D* en3=new SnEntity2D();
	en3->setIdentifyName("Entity3");
	l4->add(en3);

	SnEntity2D* ch1=new SnEntity2D();
	ch1->setIdentifyName("Ch1");
	en3->addChild(ch1);

	SnEntity2D* ch2=new SnEntity2D();
	ch2->setIdentifyName("Ch2");
	en3->addChild(ch2);


	SnQuad2D* q1=new SnQuad2D();
	q1->setTexture("asset/Coin.png");

	q1->setIdentifyName("Quad_Coin");
	ch2->addChild(q1);

	return proj;
}




#endif /*_SN_TEST_H_*/
