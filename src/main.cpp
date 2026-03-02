#include <iostream>
#include <cstring>
#include <algorithm>
#include "color.h"
#include "ray.h"
#include "objects.h"
#include "hit.h"
#include "stage.h"
#include "tracer.h"
#include "interval.h"
#include "camera.h"

using namespace std;

color ray_color(const ray &r,const stage &stg);

int main(){
	stage stg;

	stg.sphere_count = 2;

	stg.spheres = (sphere**)malloc(sizeof(sphere*)*stg.sphere_count);
	stg.spheres[0] = new sphere(vec3(0,0,-1),0.5);
	stg.spheres[1] = new sphere(vec3(0,-100.5,-1),100);

	camera cam;
	camera_render(cam,stg);
}

