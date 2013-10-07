#ifndef _SD_ANIMATION_H_
#define _SD_ANIMATION_H_ 

#include <string>
#include <vector>

#include "core/SdIdentify.h"

class SdBone;
class SdSprite;
class SdAnimation :public SdIdentify
{
	public:
		SdAnimation();
        virtual ~SdAnimation();

	public:
        virtual int getClassType();
        virtual const char* className();

	public:
		void setName(const char* name);
		std::string getName();

		SdSprite* getSprite();
		void setSprite(SdSprite* sprite);

	public:
		void addBone(SdBone* bone);
		void removeBone(SdBone* bone);

		int getBoneNu();
		SdBone* getBone(int index);

	public:
		void addKeyFrame(int pos);
		void removeKeyFrame(int pos);

	private:
		std::vector<SdBone*> m_bones;
		SdBone* m_root;
		std::string m_name;

		SdSprite* m_sprite;
};


#endif /*_SD_ANIMATION_H_*/

