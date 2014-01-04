#ifndef _SD_ANIMATION_TITILE_BAR_
#define _SD_ANIMATION_TITILE_BAR_

#include <QWidget>
#include <QPushButton>
#include <QLabel>

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
		void initLayout();

	private:
		bool m_toggle;
		QPushButton* m_expand;
		QLabel* m_lable;
};



#endif /*_SD_ANIMATION_TITILE_BAR_*/

