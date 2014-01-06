#ifndef _SD_ANIMATION_TITILE_BAR_
#define _SD_ANIMATION_TITILE_BAR_

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "ui_AnimationTitleBar.h"

class SdAnimationTitleBar:public QWidget 
{
	Q_OBJECT
	public:
		SdAnimationTitleBar();
		~SdAnimationTitleBar();

	public slots:
        void onToggle();


	protected:
		void initWidget();
        void connectSignal();

	private:

		int m_preHeight;
        bool m_toggle;
        Ui_AnimationTitleBar* m_ui;


};



#endif /*_SD_ANIMATION_TITILE_BAR_*/

