#ifndef OBJECT_H
#define OBJECT_H

#include "vec3.h"

struct sphere{
	vec3 position;
	double radius;
	sphere(){
		position = vec3(0,0,0);
		radius = 0;
	}
	sphere(vec3 position,double radius){
		this->position = position;
		this->radius = radius;
	}
};

struct object{
};

#endif
