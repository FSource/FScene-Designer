#ifndef _SN_THEME_CONFIG_H_
#define _SN_THEME_CONFIG_H_ 

#include "graphics/FsColor.h"

class SnThemeConfig 
{
	public:
		static Faeris::Color VIEW_AXIS_X_COLOR;
		static Faeris::Color VIEW_AXIS_Y_COLOR;
		static float VIEW_AXIS_WIDTH;

		/* select used */
		static Faeris::Color SELECT_CONTROLLER_SELECTED_COLOR;

		static Faeris::Color IDENTIFY_SELECT_OUT_LINE_COLOR;
		static float IDENTIFY_SELECT_OUT_LINE_WIDTH;

		/* translate editor used */
		static float TRANSLATE_CONTROLLER_CENTER_POINT_HIT_GAP;
		static Faeris::Color TRANSLATE_CONTROLLER_CENTER_POINT_COLOR;
		static Faeris::Color TRANSLATE_CONTROLLER_CENTER_POINT_COLOR_ONFOCUS;
		static Faeris::Color TRANSLATE_CONTROLLER_CENTER_POINT_OUT_LINE_COLOR;
		static float TRANSLATE_CONTROLLER_CENTER_POINT_OUT_LINE_WIDTH;
		static float TRANSLATE_CONTROLLER_AXIS_HIT_WIDTH;
		static float TRANSLATE_CONTROLLER_AXIS_HIT_LONG;




	public:
		static void initConfig();

};


#endif /*_SN_THEME_CONFIG_H_*/

