#ifndef _SD_ANIMATION_H_
#define _SD_ANIMATION_H_ 

#include <string>
#include <vector>

class SdTimeLine;

class SdAnimation 
{
	public:
		SdAnimation();
		~SdAnimation();

	public:
		void setName(std::string name);
		std::string getName();

		int getTimeLineNu();
		SdTimeLine* getTimeLine(int index);

		SdTimeLine* createTimeLine();
		SdTimeLine* createTimeLine(const char* name);

	private:
		std::string m_name;
		std::vector<SdTimeLine*> m_timelines;
};

#endif /*_SD_ANIMATION_H_*/

