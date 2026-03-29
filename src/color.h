#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <string>

struct color{
	color(){
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	color(double r,double g,double b){
		this->r = r*255;
		this->g = g*255;
		this->b = b*255;
	}
	color(int r,int g,int b){
		this->r = r;
		this->g = g;
		this->b = b;
	}
	
	int r;
	int g;
	int b;
};

inline color color_8(vec3 v){
	return color(v.x,v.y,v.z);
}
inline vec3 color_normal(color &c){
	return vec3(c.r/255.0,c.g/255.0,c.b/255.0);
}

inline vec3 color_mul(color &c, vec3 m){
	return vec3(c.r*m.x,c.g*m.y,c.b*m.z);
}
inline color color_mul(color &c, double m){
	return color(c.r*m,c.g*m,c.b*m);
}

inline double linear_to_gamma(double linear){
	if(linear > 0) return sqrt(linear);
	return 0;
}
void write_color(FILE *file,color a){
	interval i(0.0,0.999);


	a.r = (int)(clamp(linear_to_gamma(a.r/256.0),i)*255.99);
	a.g = (int)(clamp(linear_to_gamma(a.g/256.0),i)*255.99);
	a.b = (int)(clamp(linear_to_gamma(a.b/256.0),i)*255.99);
	

	fwrite(std::to_string(a.r).c_str(),1,std::to_string(a.r).length(),file);
	fwrite(" ",1,1,file);
	fwrite(std::to_string(a.g).c_str(),1,std::to_string(a.g).length(),file);
	fwrite(" ",1,1,file);
	fwrite(std::to_string(a.b).c_str(),1,std::to_string(a.b).length(),file);
	fwrite("\n",1,1,file);
}


#endif
