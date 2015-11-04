#include "Group.h"
using  namespace std;


bool Group::intersect( const Ray& r , Hit& h , float tmin ) 
{
	Hit result;

	for(unsigned i=0;i<scene_.size();++i)
	{
		
		if(scene_[i]->intersect(r,h,tmin))
		{
			if(h.getT()<result.getT())
			{
				result.set(h.getT(),h.getMaterial(),h.getNormal());
			}
			//return true;
		}
	}

	if(result.getT()>FLT_MAX||result.getT()==FLT_MAX)
	{
		return false;
	}else
	{
		h.set(result.getT(),result.getMaterial(),result.getNormal());
		return true;
	}
	return false;

}