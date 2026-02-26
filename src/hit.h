#ifndef HIT_H
#define HIT_H

#include "objects.h"
#include "stage.h"
#include "vec3.h"
#include "interval.h"

struct hit_record{
	vec3 point;
	vec3 normal;
	double t;
	bool front_face;
};

void set_face_normal(hit_record &record,const ray &r,const vec3& out_normal){
	if(vec_dot(out_normal,r.direction)<0.0){
		record.front_face = false;
		record.normal = vec_mul(out_normal,-1);
	}
	record.normal = out_normal;
	record.front_face = true;
}
bool hit(sphere s,ray r,interval ray_t,hit_record &record){
	vec3 otc = vec_sub(s.position,r.origin);

	//double a = vec_dot(r.direction,r.direction);4
	double a = vec_length_squared(r.direction);

	//double b = -2.0 * vec_dot(r.direction,otc);
	double h = vec_dot(r.direction,otc);

	//double c = vec_dot(otc,otc)-s.radius*s.radius;
	double c = vec_length_squared(otc) - s.radius*s.radius;

	double discriminant = h*h-a*c;

	if(discriminant<0)return false;

	double sqrtd = sqrt(discriminant);

	double root = (h-sqrtd)/a;
	if(!surrounds(root,ray_t)){
		root = (h+sqrtd)/a;
		if(!surrounds(root,ray_t))return false;
	}
	
	record.t = root;
	record.point = ray_at(r,root);
	vec3 out_normal = vec_div(vec_sub(record.point,s.position),s.radius);
	set_face_normal(record,r,out_normal);

	return true;
}

bool hit(const stage &s,ray r,interval ray_t,hit_record &record){
	hit_record tmp_record;
	double closest_t=ray_t.max;
	bool hit_recorded = false;

	for(int i=0;i<s.sphere_count;i++){
		if(hit(*s.spheres[i],r,interval(ray_t.min,closest_t),tmp_record)){
			hit_recorded = true;
			closest_t = tmp_record.t;
			record = tmp_record;
		}
	}

	return hit_recorded;
}


#endif
