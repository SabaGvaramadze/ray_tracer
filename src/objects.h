#ifndef OBJECT_H
#define OBJECT_H

struct sphere{
	vec3 position;
	double radius;
	void *mat;
	int type;
	sphere(){
		position = vec3(0,0,0);
		radius = 0;
	}
	sphere(vec3 position,double radius,void *mat,int type){
		this->position = position;
		this->radius = radius;
		this->mat = mat;
		this->type = type;
	}
};

struct object{
};

#endif
