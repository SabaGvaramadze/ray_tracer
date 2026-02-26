#ifndef INTERVAL_H
#define INTERVAL_H

struct interval{
	double min;
	double max;
	interval(double min,double max){
		this->min = min;
		this->max = max;
	}
};

bool contains(double a,interval i){
	return (a>=i.min && a<=i.max);
}

bool surrounds(double a,interval i){
	return (a>i.min && a<i.max);
}

double size(interval i){
	return i.max-i.min;
}


#endif
