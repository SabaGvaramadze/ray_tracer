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

inline double vec_length(vec3 a){
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}

inline double vec_length_squared(vec3 a){
	return a.x*a.x+a.y*a.y+a.z*a.z;
}

inline vec3 vec_unit(vec3 a){
	double len = vec_length(a);
	return vec3(a.x/len,a.y/len,a.z/len);
}

inline vec3 vec_add(vec3 a, vec3 b){
	return vec3(a.x+b.x,a.y+b.y,a.z+b.z);
}

inline vec3 vec_sub(vec3 a, vec3 b){
	return vec3(a.x-b.x,a.y-b.y,a.z-b.z);
}

inline vec3 vec_mul(vec3 a,double b){
	return vec3(a.x*b,a.y*b,a.z*b);
}

inline vec3 vec_mul(vec3 a,vec3 b){
	return vec3(a.x*b.x,a.y*b.y,a.z*b.z);
}
inline vec3 vec_div(vec3 a,double b){
	return vec3(a.x/b,a.y/b,a.z/b);
}

inline double vec_dot(vec3 a,vec3 b){
	return (a.x*b.x+a.y*b.y+a.z*b.z);
}

inline vec3 vec_random(double min,double max){
	return vec3(rand_double(min,max),rand_double(min,max),rand_double(min,max));
}
inline vec3 vec_random(){
	return vec3(rand_double(),rand_double(),rand_double());
}

inline vec3 vec_random_normal(){
	vec3 tmp;
	double lensq;
	while(true){
		tmp = vec_random(-1,1);
		lensq = vec_length_squared(tmp);
		if(1e-160 < lensq && lensq <= 1){
			return vec_div(tmp,sqrt(lensq));
		}
		
	}
}

inline vec3 vec_random_on_hemisphere(const vec3& norm){
	vec3 on_unit_sphere = vec_random_normal();
	if(vec_dot(norm,on_unit_sphere) > 0.0){
		return on_unit_sphere;
	}
	return vec_mul(on_unit_sphere,-1);
}

inline vec3 vec_reflect(const vec3 &v, const vec3 &n){
	return vec_sub(v,vec_mul(vec_mul(n,(vec_dot(v,n))),2));
}

inline bool vec_near_zero(const vec3 &v){
	double s = 1e-8;
	return (v.x < s && v.x > -s && v.y < s && v.y > -s && v.z < s && v.z > -s);
}

#endif
