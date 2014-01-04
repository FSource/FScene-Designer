#ifndef _SD_BONE_H_
#define _SD_BONE_H_

#include <string>
#include <vector>

#include "math/FsMatrix4.h"
class SdBoneAttribute
{
	public:
		SdBoneAttribute()
			:name(""),tx(0.0f),ty(0.0f),
			angle(0.0f),sx(1.0f),sy(1.0f),
			flipX(false),flipY(false)
	{
	}

	public:
		std::string name;
		float tx,ty;
		float angle;
		float sx,sy;
		bool flipX,flipY;

};

class SdBone 
{
	public:
		SdBone(SdBone* parent=NULL);
		~SdBone();

	public:
		void setName(const char* name);
		std::string getName();

		void setParent(SdBone* bone);
		SdBone* getParent();

		void addChild(SdBone* bone);
		void removeChild(SdBone* bone);

		int getChildNu();
		SdBone* getChild(int index);

	public:
		void updateLocalMatrix();
		void updateWorldMatrix(bool child=true);

	public:
		SdKeyFrame* getKeyFrame(int pos);
		void getKeyFrameNu();

	public:
		void insertFrame(int pos);
		void removeFrame(int pos);

	private:
		SdAnimation* m_animation;
		SdBone* m_parent;
		std::vector<SdBone*> m_children;


		Matrix4 m_localMatrix;
		Matrix4 m_worldMatrix;

		std::vector<SdKeyFrame*> m_keyFrames;

};


#endif /*_SD_BONE_H_*/

















