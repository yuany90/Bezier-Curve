#ifndef _BEZIER_H_
#define _BEZIER_H_


class bezier{
public:
	int precision;
	bool showControlPoints;
	bezier(){
		precision = 5;
		showControlPoints = true;
	}
	virtual void draw(){ 
	}
	void setPrecisions(int precision){
		if(precision < 2){
		precision = 2;
		}
		this->precision = precision;
	}
	void controlPoints(bool flag){
		showControlPoints = flag;
	}
};

#endif
