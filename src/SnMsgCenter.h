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



	public:


		/* project */
		void emitCurProjectChange();

};


#endif /*_SD_MSG_CENTER_H_*/












