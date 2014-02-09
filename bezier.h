#ifndef _BEZIER_H_
#define _BEZIER_H_

class bezier{
public:
	int precision;
	virtual void draw(){ 
	}
	void setPrecisions(int precision){
		if(precision < 2){
		precision = 2;
		}
		this->precision = precision;
	}
};

#endif
