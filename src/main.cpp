#include <iostream>
#include <cstring>
#include <algorithm>
#include <time.h>

#include "tracer.h"
#include "camera.h"

using namespace std;

int main(){
	stage stg;

	lambertian material_ground = lambertian(color(0.9,0.9,0.9));
	lambertian material_center = lambertian(color(0.1,0.2,0.5));
	lambertian close_center = lambertian(color(0.6,0.3,0.3));
	dielectric material_left = dielectric(1.50);
	dielectric material_bubble = dielectric(1.00/1.50);
	metal material_right = metal(color(0.8,0.6,0.2),1.0);
	metal mirror = metal(color(0.55,0.6,0.3),0.05);
	

	int start = 6;

	stg.sphere_count = 350;
	stg.obj_count = 0;

	stg.spheres = (sphere**)malloc(sizeof(sphere*)*stg.sphere_count);
	stg.spheres[0] = new sphere(vec3(0,-0.40,-1.2),0.15,(void*)&close_center,lambertian_type);
	stg.spheres[1] = new sphere(vec3(0,-1000.5,-1),1000,(void*)&material_ground,lambertian_type);
	stg.spheres[2] = new sphere(vec3(-1,0,-1),0.5,(void*)&material_left,dielectric_type);
	stg.spheres[3] = new sphere(vec3(-1,-0,-1),0.4,(void*)&material_bubble,dielectric_type);
	stg.spheres[4] = new sphere(vec3(3.5,-0.3,-2.9),0.7,(void*)&mirror,metal_type);
	stg.spheres[5] = new sphere(vec3(0,0,-2.2),0.5,(void*)&material_center,lambertian_type);

	std::srand(time(NULL));

	for(int i = start;i<stg.sphere_count;i++){
		vec3 pos;
		while(1){
			pos = vec_mul(vec3(rand_double(-1,1)*1.3,0,rand_double(-1,1)+0.1),4.5);
			pos.y = -0.4;
			pos.z -= 3;
			double rad = 0.1;
			double intersect = false;
			for(int j=0;j<i;j++){
				if(vec_length(vec_sub(pos,stg.spheres[j]->position)) <= rad+stg.spheres[j]->radius){
					intersect = true;
					break;
				}
			}
			if(!intersect)break;
		}
		
		double type = rand_double();
		sphere *tmp;
		if(type<0.7)
			tmp = new sphere(pos,0.1,(void*)(new lambertian(color(rand_double(),rand_double(),rand_double()))),lambertian_type);
		else if(type < 0.9)
			tmp = new sphere(pos,0.1,(void*)(new metal(color(rand_double(0,0.5)+0.5,rand_double(0,0.5)+0.5,rand_double(0,0.5)+0.5),rand_double(0,0.3))),metal_type);
		else if(type <1)
			tmp = new sphere(pos,0.1,(void*)(new dielectric(rand_double(0,1.5))),dielectric_type);
		stg.spheres[i] = tmp;
	}


	camera cam;
	camera_render(cam,stg);
}

