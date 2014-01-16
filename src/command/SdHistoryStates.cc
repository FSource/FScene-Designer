#include <assert.h>
#include "command/SdHistoryStates.h"

SdHistoryStates::SdHistoryStates()
{
	m_curStateIndex=-1;
}
SdHistoryStates::~SdHistoryStates()
{
	for(int i=0;i<m_historyStates.size();i++)
	{
		SdCommand* command=m_historyStates.getItem(i);
		command->backDiscard();
	}
	m_historyStates.clear();
}

void SdHistoryStates::pushCommand(SdCommand* cmd)
{
	if(m_curStateIndex<m_historyStates.size()-1)
	{
		for(int i=m_curStateIndex+1;i<m_historyStates.size();i++)
		{
			SdCommand* command=m_historyStates.getItem(i);
			command->forwardDiscard();
		}
		m_historyStates.dropTail(m_historyStates.size()-1-m_curStateIndex);
	}

	if(m_historyStates.full())
	{
		SdCommand* command=m_historyStates.getItem(0);
		command->backDiscard();

		m_historyStates.push(cmd);
	}
	else 
	{
		m_historyStates.push(cmd);
		m_curStateIndex++;
	}
}

SdCommand* SdHistoryStates::undo()
{
	assert(canUndo());
	SdCommand* command=m_historyStates.getItem(m_curStateIndex);
	m_curStateIndex--;
	command->undo();
	return command;

}

SdCommand* SdHistoryStates::redo()
{
	assert(canRedo());
	SdCommand* command=m_historyStates.getItem(m_curStateIndex+1);
	m_curStateIndex++;
	command->redo();
    return command;
}

bool SdHistoryStates::canRedo()
{
	if(m_curStateIndex<m_historyStates.size()-1)
	{
		return true;
	}
	return false;
}

bool SdHistoryStates::canUndo()
{
	if(m_curStateIndex>=0)
	{
		return true;
	}
    return false;

}

