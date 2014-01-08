#ifndef _SD_SPRITE_H_
#define _SD_SPRITE_H_

#include <vector>
#include <string>

class SdProject;


class SdAnimation;
class SdProject;

class SdSpriteAttribute 
{
	public:
		std::string name;
};

class SdSprite 
{
	public:
		SdSprite(const std::string& name);
		~SdSprite();

	public:
		void setAttribute(const SdSpriteAttribute& attr);
		SdSpriteAttribute getAttribute();

	public:
		void setName(const std::string& name);
		std::string getName();

		SdProject* getProject();
		void setProject(SdProject* proj);

		SdAnimation* createAnimation(const std::string& name);
		void removeAnimation(SdAnimation* anim);
		void addAnimation(int pos,SdAnimation* anim);
		void addAnimation(SdAnimation* anim);


		int getAnimationNu();
		SdAnimation* getAnimation(int index);

		bool hasAnimationWithName(const std::string& name);
		bool hasAnimation(SdAnimation* anim);

		int getAnimationPos(SdAnimation* anim);

		SdAnimation* getCurAnimation();
		void setCurAnimation(SdAnimation* anim);

	private:
		SdSpriteAttribute m_attr;

        std::vector<SdAnimation*> m_animations;

		SdAnimation* m_curAnimation;
		SdProject* m_project;
};


#endif /*_SD_SPRITE_H_*/

























