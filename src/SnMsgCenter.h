#ifndef _SD_MSG_CENTER_H_
#define _SD_MSG_CENTER_H_


#include <QObject>

class SnProject;
class SnLayer2D;


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
		void signalLayer2DAdd(SnLayer2D* ly);
		void signalCurLayerChange(SnLayer2D* ly);
		void signalCurEntityChange();


	public:
		/* project */
		void emitCurProjectChange();
		void emitCurSceneChange();

		void emitLayer2DAdd(SnLayer2D* ly);
		void emitCurLayerChange(SnLayer2D* ly);
		void emitCurEntityChange();

};


#endif /*_SD_MSG_CENTER_H_*/












