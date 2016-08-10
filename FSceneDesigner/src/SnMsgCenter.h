#ifndef _SD_MSG_CENTER_H_
#define _SD_MSG_CENTER_H_


#include <vector>
#include <QObject>

#include "SnEnums.h"

class SnProject;
class SnLayer2D;
class SnIdentify;


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
		void signalIdentifyAdd(SnIdentify* id);
		void signalIdentifyDelete(std::vector<SnIdentify*> ids);



		void signalIdentifyAttributeChange(SnIdentify* id,const char* name);

		void signalCurrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st);
		void signalEditModeChange(SN_EditMode mode);
		void signalTranslateModeChange(SN_TranslateMode mode);



	public:
		/* project */
		void emitCurProjectChange();
		void emitCurSceneChange();

		void emitLayer2DAdd(SnLayer2D* ly);
		void emitIdentifyAdd(SnIdentify* id);
		void emitIdentifyDelete(std::vector<SnIdentify*> ids);


		void emitCurLayerChange(SnLayer2D* ly);
		void emitCurEntityChange();

		void emitIdentifyAttributeChange(SnIdentify* id,const char* name);
		void emitCurrrentAndSelectsChange(SnIdentify* id,const std::vector<SnIdentify*>& st);

		void emitEditModeChange(SN_EditMode mode);
		void emitTranslateModeChange(SN_TranslateMode mode);
};


#endif /*_SD_MSG_CENTER_H_*/












