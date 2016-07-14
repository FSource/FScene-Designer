#ifndef _SN_CONTORLLER_H_
#define _SN_CONTORLLER_H_ 

class SnController 
{
	public:
		SnController();
		virtual ~SnController();

	public:
		virtual onLoad();
		virtual onUnload();

		virtual onTouchBegin(float x,float y);
		virtual onTouchMove(float x,float y);
		virtual onTouchEnd(float x,float y);

};



#endif /*_SN_CONTORLLER_H_*/
