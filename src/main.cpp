#include <iostream>
#include <cstring>
#include <algorithm>

#include "tracer.h"
#include "camera.h"

using namespace std;

int main(){
	stage stg;

	lambertian material_ground = lambertian(color(0.8,0.8,0.0));
	lambertian material_center = lambertian(color(0.1,0.2,0.5));
	metal material_left = metal(color(0.8,0.8,0.8),0.001);
	metal material_right = metal(color(0.8,0.6,0.2),1.0);
	

	stg.sphere_count = 4;
	stg.obj_count = 0;

	stg.spheres = (sphere**)malloc(sizeof(sphere*)*stg.sphere_count);
	stg.spheres[0] = new sphere(vec3(0,0,-1.2),0.5,(void*)&material_center,lambertian_type);
	stg.spheres[1] = new sphere(vec3(0,-100.5,-1),100,(void*)&material_ground,lambertian_type);
	stg.spheres[2] = new sphere(vec3(-1,0,-1),0.5,(void*)&material_left,metal_type);
	stg.spheres[3] = new sphere(vec3(1,-0,-1),0.5,(void*)&material_right,metal_type);

	camera cam;
	camera_render(cam,stg);
}

