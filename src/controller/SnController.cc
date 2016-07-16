#include "SnController.h"
#include "widget/SnEditViewWidget.h"

SnController::SnController()
{

}

SnController::~SnController()
{

}

bool SnController::onLoad(SnEditViewWidget* )
{
	return false;
}

bool SnController::onUnload(SnEditViewWidget* )
{
	return false;
}

bool SnController::onTouchBegin(SnEditViewWidget* ,QMouseEvent* )
{
	return false;

}

bool SnController::onTouchMove(SnEditViewWidget* ,QMouseEvent* )
{
	return false;
}

bool SnController::onTouchEnd(SnEditViewWidget* ,QMouseEvent* )
{
	return false;

}
bool SnController::onKeyPressEvent(SnEditViewWidget* ,QKeyEvent* )
{
	return false;
}

bool SnController::onKeyReleaseEvent(SnEditViewWidget* ,QKeyEvent* )
{
	return false;
}


void  SnController::onDraw(SnEditViewWidget* )
{
}



