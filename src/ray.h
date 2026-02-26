#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct ray{
	ray(vec3 origin,vec3 direction){
		this->origin = origin;
		this->direction = direction;
	}
	vec3 origin;
	vec3 direction;
};

vec3 ray_at(ray Ray,double t){
	return vec_add(Ray.origin,vec_mul(Ray.direction,t));
}

#endif
