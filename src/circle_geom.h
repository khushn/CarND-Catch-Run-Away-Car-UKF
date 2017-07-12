#ifndef CIRCLE_GEOM_H
#define CIRCLE_GEOM_H

#include <iostream>

#include "Eigen/Dense"

using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;

class CircleGeom {

public: 

	double radius_;
	
	// center
	double cx_;
	double cy_;

	// dynamic data
	double x_;
	double y_;
	double dir_;
	double turn_rate_;
	double speed_;


	CircleGeom(VectorXd& xm);
	virtual ~CircleGeom();

	/**
	   Dear Cicle, 
	    kindly tell me, which point in future should I target, 
	   - Given my max speed is same as yours
	   - Thy now know youreself
	   - I'll tell you where I am right now
	   - also please tell me in what time I can expect to meet the rogue car I'm hunting 

	   NOTE; The returned value is time and turn and distance are filled in, in passed arguments
	*/
	double tell_me_circle(double hunter_x, double hunter_y, double *turn_ret, double *dist_ret);

private: 
	double check_position(double hunter_x, double hunter_y, double tx, double ty, double *turn_ret, double *dist_ret);
};

#endif /* CIRCLE_GEOM_H */