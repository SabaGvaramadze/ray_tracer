
#ifndef VEC3_H
#define VEC3_H

#include <math.h>

struct vec3{
	vec3(double x,double y,double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vec3(){
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	double x;
	double y;
	double z;
};

double vec_length(vec3 a){
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

double vec_length_squared(vec3 a){
	return a.x*a.x+a.y*a.y+a.z*a.z;
}

vec3 vec_unit(vec3 a){
	double len = vec_length(a);
	return vec3(a.x/len,a.y/len,a.z/len);
}

vec3 vec_add(vec3 a, vec3 b){
	return vec3(a.x+b.x,a.y+b.y,a.z+b.z);
}

vec3 vec_sub(vec3 a, vec3 b){
	return vec3(a.x-b.x,a.y-b.y,a.z-b.z);
}

vec3 vec_mul(vec3 a,double b){
	return vec3(a.x*b,a.y*b,a.z*b);
}
vec3 vec_div(vec3 a,double b){
	return vec3(a.x/b,a.y/b,a.z/b);
}

double vec_dot(vec3 a,vec3 b){
	return (a.x*b.x+a.y*b.y+a.z*b.z);
}

#endif
