#ifndef _SD_UTIL_H_
#define _SD_UTIL_H_


#include <QString>
#include "math/FsVector2.h"
class SnIdentify;

namespace  SnUtil 
{
        QString toProjectPath(const QString& path);
		QString toRelativePath(const QString& root,const QString& path);


		bool identifyInRect(SnIdentify* en,Faeris::Vector2f start,Faeris::Vector2f end);
		bool identifyHitPoint(SnIdentify* en,Faeris::Vector2f p);

		bool hitIdentityCenterPoint(SnIdentify* en,Faeris::Vector2f pos,float gap);
		bool hitIdentityAxisX(SnIdentify* en,Faeris::Vector2f pos,float width,float height);
		bool hitIdentityAxisY(SnIdentify* en,Faeris::Vector2f pos,float width,float height);


	template <typename T>
        inline void swap(T* left, T* right)
		{
			T tmp = *left;
			*left = *right;
			*right = tmp;
		}

	template <typename T>
        inline T clamp(T value,T min,T max)
		{
			int ret;
			if(min>max)
			{
				swap(&min,&max);
			}
			if(value<min)
			{
				ret=min;
			}
			else if(value>max)
			{
				ret=max;
			}
			else 
			{
				ret=value;
			}
			return ret;
		}
	template <typename T>
        inline T zmod(T value,T m)
		{
			if(value<0)
			{
				T t=value/m;
				value=value+(-t+1)*m;
			}
			return value%m;
		}

        inline float fmin(float left,float right)
		{
			return left<right?left:right;
        }

        inline float fmax(float left,float right)
		{
			return left<right?right:left;
		}

        inline int zmin(int left,int right)
        {
            return left<right?left:right;
        }

        inline int zmax(int left,int right)
        {
            return left<right?right:left;
        }
}

#endif /*_SD_UTIL_H_*/
