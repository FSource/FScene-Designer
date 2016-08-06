#ifndef _SD_HISTORY_STATES_H_
#define _SD_HISTORY_STATES_H_

#include "command/SdCommand.h"
#include "util/SdCircleQueue.h"

class SdHistoryStates 
{
	public:
		SdHistoryStates();
		~SdHistoryStates();
	public:
		bool canRedo();
		bool canUndo();
		SdCommand* redo();
		SdCommand* undo();
		void pushCommand(SdCommand* cmd);

	private:
        SdCircleQueue<SdCommand> m_historyStates;
        int m_curStateIndex;

};

#endif /*_SD_HISTORY_STATES_H_*/



