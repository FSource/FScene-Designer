#ifndef _SD_TIME_LINE_H_
#define _SD_TIME_LINE_H_

#include "SdSubTimeLine.h"

class SdTimeLineUiData;
class SdSubTimeLineSet;

class SdTimeLine 
{
	public:
		SdTimeLine();
		~SdTimeLine();

	public:
		bool getVisible(){return m_visible;}
		void setVisible(bool v){m_visible=v;}

		bool getSelect(){return m_select;}
		void setSelect(bool v){m_select=v;}

		bool getExpand(){return m_expand;}
		void setExpand(bool expand){m_expand=expand;}


		void setName(const char* name){m_name=name;}
		std::string getName(){return m_name;}

		SdTimeLineUiData* getUiData(){return m_uiData;}

	private:
		bool m_visible;
		bool m_select;
		bool m_expand;

		std::string m_name;

		/* Sub Time Line */
		SdSubTimeLineSet* m_subTimeSet;

		/* Ui Data */
		SdTimeLineUiData* m_uiData;


};



#endif /*_SD_TIME_LINE_H_*/

