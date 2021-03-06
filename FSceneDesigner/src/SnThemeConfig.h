#ifndef _SN_THEME_CONFIG_H_
#define _SN_THEME_CONFIG_H_ 

#include "graphics/FsColor.h"
#include "math/FsVector2.h"


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

		static Faeris::Color TRANSLATE_CONTROLLER_X_AXIS_COLOR;
		static Faeris::Color TRANSLATE_CONTROLLER_Y_AXIS_COLOR;
		static Faeris::Color TRANSLATE_CONTROLLER_X_AXIS_FOCUS_COLOR;
		static Faeris::Color TRANSLATE_CONTROLLER_Y_AXIS_FOCUS_COLOR;

		static float TRANSLATE_CONTROLLER_AXIS_WIDTH;

		static float TRANSLATE_CONTROLLER_CENTER_POINT_OUT_LINE_WIDTH;
		static float TRANSLATE_CONTROLLER_AXIS_HIT_WIDTH;
		static float TRANSLATE_CONTROLLER_AXIS_HIT_LONG;

		static float TRANSLATE_CONTROLLER_TRIANGLE_HEIGHT;
		static float TRANSLATE_CONTROLLER_TRIANGLE_WIDTH;

		/* scale controller */
		static float SCALE_CONTROLLER_CENTER_POINT_HIT_GAP;
		static Faeris::Color SCALE_CONTROLLER_CENTER_POINT_COLOR;
		static Faeris::Color SCALE_CONTROLLER_CENTER_POINT_COLOR_ONFOCUS;
		static Faeris::Color SCALE_CONTROLLER_CENTER_POINT_OUT_LINE_COLOR;

		static Faeris::Color SCALE_CONTROLLER_X_AXIS_COLOR;
		static Faeris::Color SCALE_CONTROLLER_Y_AXIS_COLOR;
		static Faeris::Color SCALE_CONTROLLER_X_AXIS_FOCUS_COLOR;
		static Faeris::Color SCALE_CONTROLLER_Y_AXIS_FOCUS_COLOR;

		static float SCALE_CONTROLLER_AXIS_WIDTH;
		static float SCALE_CONTROLLER_CENTER_POINT_OUT_LINE_WIDTH;
		static float SCALE_CONTROLLER_AXIS_HIT_WIDTH;
		static float SCALE_CONTROLLER_AXIS_HIT_LONG;

		static float SCALE_CONTROLLER_AXIS_RECT_SIZE;



		/* rotate controller */
		static Faeris::Color ROTATE_CONTROLLER_OUT_LINE_COLOR;
		static Faeris::Color ROTATE_CONTROLLER_OUT_LINE_FOCUS_COLOR;
		static float ROTATE_CONTROLLER_RADIUS;
		static float ROTATE_CONTROLLER_OUT_LINE_WIDTH;

		static float ROTATE_CONTROLLER_TRIANGLE_WIDTH;
		static float ROTATE_CONTROLLER_TRIANGLE_HEIGHT;


		/* resize controller */
		static float RESIZE_CONTROLLER_HIT_LENGTH;
		static float RESIZE_CONTROLLER_RECTANCLE_LENGTH;
		static float RESIZE_CONTROLLER_OUT_LINE_WIDTH;

		static Faeris::Color RESIZE_CONTROLLER_OUT_LINE_COLOR;
		static Faeris::Color RESIZE_CONTROLLER_FILL_COLOR;
		static Faeris::Color RESIZE_CONTROLLER_FILL_FOCUS_COLOR;

		/* press button */
		static Faeris::Vector2f PRESS_BUTTON_DEFAULT_SIZE;



	public:
		static void initConfig();

};


#endif /*_SN_THEME_CONFIG_H_*/

