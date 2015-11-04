#include "Plane.h"


bool Plane::intersect( const Ray& r , Hit& h , float tmin)
{

	//float a=ray.direction_.normalize().dotMul(normal_);
	float a=Vector3f::dot(r.getDirection(),normal_);

	//printf("a:%f\n",a);

	if(a<0)
	{
		
		// result.IsHit=true;
		// //printf("a<0\n");
		// double b=normal_.dotMul(ray.origin_+normal_*d_);
		// //printf("b %f\n",b);
		
		// double distance=-b/a;

		// //printf("distance %f\n",distance);
		// Vector tmp=ray.getPoint(-b/a);

		// // printf("ray.getPoint(-b/a) %f,%f,%f\n",tmp.x_,
		// // 		tmp.y_,
		// // 		tmp.z_);
		// result.position_=tmp;
		// result.normal_=normal_.normalize();
		// result.distance_=distance;
		// result.shininess_=shininess_;
		// result.Ka_=PlaneKa_;
		// result.Kd_=PlaneKd_;
		// result.Ks_=PlaneKs_;
		float b=Vector3f::dot(normal_,r.getOrigin()-normal_*offset_);

		float t=-b/a;
		// if(!(t>tmin)&&!(t<FLT_MAX))
		// {
		// 	return false;
		// }

		//Vector3f tmp=r.pointAtParameter(t);

		

		h.set(t,material_,normal_);

		return true;

	}else
	{
		return false;

	}


}