#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <string>

using namespace std;

struct color{
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
	
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

void write_color(FILE *file,color a){
	fwrite(to_string(a.r).c_str(),1,to_string(a.r).length(),file);
	fwrite(" ",1,1,file);
	fwrite(to_string(a.g).c_str(),1,to_string(a.g).length(),file);
	fwrite(" ",1,1,file);
	fwrite(to_string(a.b).c_str(),1,to_string(a.b).length(),file);
	fwrite("\n",1,1,file);
}

#endif
