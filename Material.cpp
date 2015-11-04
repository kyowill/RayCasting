#include "Material.h"

Vector3f Material::Shade( const Ray& ray, const Hit& hit,
              const Vector3f& dirToLight, const Vector3f& lightColor )
{

	float L_N=Vector3f::dot(dirToLight,hit.getNormal());
	
	float V_N=Vector3f::dot(ray.getDirection(),hit.getNormal());
	
	Vector3f R=ray.getDirection() - 2 * V_N * hit.getNormal();

	float L_R=Vector3f::dot(dirToLight,R);

	if(L_N<=0)
	{
		L_N=0;
	}
	Vector3f Dcolor;
	if(t.valid())
	{

		Dcolor= L_N*lightColor*t(hit.texCoord.x(),hit.texCoord.y());
	}else
	{
		Dcolor= L_N * lightColor * diffuseColor;
	}

	Vector3f Scolor= pow(L_R,shininess) * lightColor * specularColor;

	return Dcolor + Scolor; 
	
}