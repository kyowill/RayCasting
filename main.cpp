#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
  // Fill in your implementation here.

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").
  for( int argNum = 1; argNum < argc; ++argNum )
    {
      std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }
	
    
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  SceneParser SP(argv[1]);//
  Group* scene=SP.getGroup();
  Camera* camera=SP.getCamera();
  Image image( 500, 500 );
  for(int i=0;i<500;++i)
  {
    for(int j=0;j<500;++j)
    {
       Vector2f point(-1+j/250.0,-1+i/250.0);
       Ray r(camera->generateRay(point));
       
       Hit h;
       Vector3f ori=r.getOrigin();
       Vector3f dir=r.getDirection();
       // printf("origin:%f,%f,%f,direction:%f,%f,%f\n",
       //        ori.x(),ori.y(),ori.z(),dir.x(),dir.y(),dir.z());
       if(scene->intersect(r,h,0))
       {
          //printf("1\n");

          //printf("t:%f\n",h.getT());
          //Vector3f pixelColor (1-h.getT()/10,1-h.getT()/10,1-h.getT()/10);
          Vector3f p=r.pointAtParameter(h.getT());

          Vector3f pixelColor(0,0,0);

          int num_lights=SP.getNumLights();

          for(int k=0;k<num_lights;++k)
          {

            Light* L=SP.getLight(k);
            
            Vector3f dir(0,0,0);
            
            Vector3f col(0,0,0);
            
            float distanceToLight;
            
            L->getIllumination(p,dir,col,distanceToLight);

            //Material* m=h.getMaterial();

            Ray r2(p,dir);//new ray for shadow
            
            Material* m_h2;
            Vector3f n_h2(0,0,0);
            
            Hit h2(distanceToLight,m_h2,n_h2);
            if(!(scene->intersect(r2,h2,0)))
            {
                Material* m=h.getMaterial();
                pixelColor+=m->Shade(r,h,dir,col);
            }

            //pixelColor+=m->Shade(r,h,dir,col);

          }

          image.SetPixel( j,i, pixelColor );//j<=>x,i<=>y


       }else  
       {
          Vector3f pixelColor=SP.getBackgroundColor();
          image.SetPixel( j,i, pixelColor );
       }
    }
  }

  //vector<Object3D*> scene=SP.getScene();
  //printf("%d\n",(Scene.getGroup())->getGroupSize());


 
  ///TODO: below demonstrates how to use the provided Image class
  ///Should be removed when you start
  //Vector3f pixelColor (1.0f,1.0f,1.0f);
  //width and height
  //Image image( 200 , 200 );
  //image.SetPixel( 9,14, pixelColor );//(0,0)在左下角(width-1,height-1)在右上角 
  image.SaveImage("yk.bmp");
  return 0;
}

