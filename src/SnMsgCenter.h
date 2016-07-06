#ifndef _SD_MSG_CENTER_H_
#define _SD_MSG_CENTER_H_


#include <QObject>

class SnProject;


class SnMsgCenter:public QObject 
{
	Q_OBJECT

	public:

		SnMsgCenter();
		~SnMsgCenter();


    signals:
		/* project */
		void signalCurProjectChange();
		void signalCurSceneChange();



	public:


		/* project */
		void emitCurProjectChange();
		void emitCurSceneChange();

};


#endif /*_SD_MSG_CENTER_H_*/












