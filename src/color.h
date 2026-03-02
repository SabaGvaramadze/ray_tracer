#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <string>
#include "tracer.h"

using namespace std;

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
	color(uint8_t r,uint8_t g,uint8_t b){
		this->r = r*255;
		this->g = g*255;
		this->b = b*255;
	}
	
	int r;
	int g;
	int b;
};

void write_color(FILE *file,color a){
	interval i(0.0,0.999);
	a.r = (int)(clamp(a.r/256.0,i)*256);
	a.g = (int)(clamp(a.g/256.0,i)*256);
	a.b = (int)(clamp(a.b/256.0,i)*256);
	

	fwrite(to_string(a.r).c_str(),1,to_string(a.r).length(),file);
	fwrite(" ",1,1,file);
	fwrite(to_string(a.g).c_str(),1,to_string(a.g).length(),file);
	fwrite(" ",1,1,file);
	fwrite(to_string(a.b).c_str(),1,to_string(a.b).length(),file);
	fwrite("\n",1,1,file);
}

#endif
