#include "Sphere.h"

bool Sphere::intersect( const Ray& r , Hit& h , float tmin)
{
	Vector3f v=r.getOrigin()-center_;//Ray:Vector3f origin,Vector3f direction;

	float a0=v.absSquared()-radius_*radius_;
	//printf("a0:%f\n",a0);
	//float Ddotv=Vector3f::dot(r.getDirection(),v);//normalized direction

	float Ddotv=Vector3f::dot(r.getDirection().normalized(),v);

	float discr=Ddotv*Ddotv - a0;
	

	if(discr>=0)
	{
		float t=-Ddotv-sqrt(discr);

		if(!(t>tmin&&t<FLT_MAX))
		{
			return false;
		}

		t=t/(r.getDirection().abs());
		
		Vector3f tmp=r.pointAtParameter(t);
		//result.IsHit=true;

		//result.distance_=-Ddotv-sqrt(discr);
		//result.position_=tmp;
		//result.normal_=(tmp-center_).normalize();


		h.set(t,material,(tmp-center_).normalized());
		//h.set(t,material,(tmp-center_));
		// result.shininess_=shininess_;
		// result.Ka_=SphereKa_;
		// result.Kd_=SphereKd_;
		// result.Ks_=SphereKs_;

		//printf("***\n");
		return true;
	}

	return false;
}
