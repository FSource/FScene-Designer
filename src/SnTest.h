#ifndef _SN_TEST_H_
#define _SN_TEST_H_ 

#include "core/SnScene.h"
#include "core/SnLayer2D.h"
#include "core/SnProject.h"
#include "core/SnEntity2D.h"
#include "core/SnQuad2D.h"
#include "core/SnLabelTTF.h"
#include "core/SnPressButton.h"
#include "core/SnUiWidget.h"
#include "core/SnPageView.h"
#include "core/SnScrollView.h"
#include "core/SnListView.h"

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

	SnQuad2D* en1=new SnQuad2D();
	en1->setSize(40,40);
	en1->setPosition(100,-100);
	en1->setIdentifyName("Entity1");
	l4->addIdentifyChild(en1);

	SnQuad2D* en2=new SnQuad2D();
	en2->setSize(60,30);
	en2->setPosition(-100,100);
	en2->setIdentifyName("Entity2");
	l4->addIdentifyChild(en2);

	SnQuad2D* en3=new SnQuad2D();
	en3->setSize(100,100);
	en3->setPosition(200,-200);
	en3->setIdentifyName("Entity3");
	l4->addIdentifyChild(en3);

	SnQuad2D* ch1=new SnQuad2D();
	ch1->setSize(32,32);
	ch1->setPosition(-80,0);
	ch1->setIdentifyName("Ch1");
	en3->addIdentifyChild(ch1);

	SnQuad2D* ch2=new SnQuad2D();
	ch2->setSize(56,23);
	ch2->setPosition(90,0);
	ch2->setIdentifyName("Ch2");
	en3->addIdentifyChild(ch2);


	SnQuad2D* q1=new SnQuad2D();
	q1->setTexture("asset/Coin.png");
	q1->setPosition(200,200);
	q1->setIdentifyName("Quad_Coin");
	l4->addIdentifyChild(q1);

	SnQuad2D* q2=new SnQuad2D();
	q2->setSize(128,128);
	q2->setPosition(-300,450);
	q2->setIdentifyName("no Resurce");
	en3->addIdentifyChild(q2);

	SnLabelTTF* t1=new SnLabelTTF;
	t1->setIdentifyName("LabelTTF");

	l4->addIdentifyChild(t1);


	SnPressButton* pb1=new SnPressButton;
	pb1->setIdentifyName("PressButton1");
	l4->addIdentifyChild(pb1);
	
	SnUiWidget* ui1=new SnUiWidget;
	ui1->setIdentifyName("UiWidget1");
	//l4->addIdentifyChild(ui1);
	
	SnUiWidget* ui2=new SnUiWidget;
	ui2->setIdentifyName("UiWidget2");

	SnPageView* pg1=new SnPageView;
	pg1->setIdentifyName("PageView1");
	l4->addIdentifyChild(pg1);

	pg1->addPage(ui1);
	pg1->addPage(ui2);
	pg1->setCurrentPageIndex(0);


	/* scroll view */
	SnScrollView* sv1=new SnScrollView;
	sv1->setIdentifyName("ScrollView1");
	l4->addIdentifyChild(sv1);

	SnUiWidget* sv_c1=new SnUiWidget;
	sv_c1->setIdentifyName("SVContent1");
	sv1->setContentWidget(sv_c1);

	/* list view */
	SnListView* sl1=new SnListView;
	sl1->setIdentifyName("ListView1");
	l4->addIdentifyChild(sl1);

	SnUiWidget* ls_c1=new SnUiWidget;
	ls_c1->setIdentifyName("ListItem1");
	sl1->addListItem(ls_c1);

	SnUiWidget* ls_c2=new SnUiWidget;
	ls_c2->setIdentifyName("ListItem2");
	sl1->addListItem(ls_c2);


	return proj;
}




#endif /*_SN_TEST_H_*/
