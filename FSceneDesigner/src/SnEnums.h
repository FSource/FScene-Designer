#ifndef _SN_ENUMS_H_
#define _SN_ENUMS_H_ 



enum class SN_EditMode
{
	TRANSALTE=0,
	ROTATE=1,
	SCALE=2,
	RESIZE=3,
};

enum class SN_TranslateMode 
{
	LOCAL=1,
	WORLD=2
};


enum  SN_ExportSaveFlags
{
	FILTER_VALUE=0x01,
	IGNORE_EXPORT=0x02,
};

#endif /*_SN_ENUMS_H_*/

