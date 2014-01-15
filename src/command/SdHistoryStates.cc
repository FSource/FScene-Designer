#include "command/SdHistoryStates.h"

void SdHistoryStates::pushCommand(SdCommand* cmd)
{
	if(m_curStateIndex<m_historyStates.size()-1)
	{
		m_historyStates.dropTail(m_historyStates.size()-1-m_curStateIndex);
	}

	if(m_historyStates.full())
	{
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

