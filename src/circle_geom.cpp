#include "circle_geom.h"

double normalize_angle(double theta);

CircleGeom::CircleGeom(VectorXd& xm) {
	x_ = xm[0];
	y_ = xm[1];
	speed_ = xm[2];
	dir_  = xm[3];
	turn_rate_ = xm[4];


	radius_ = fabs(speed_ / turn_rate_);

	
	if (turn_rate_ > 0) {
		cx_ = x_ + radius_*cos(M_PI/2 + dir_);
		cy_ = y_ + radius_*sin(M_PI/2 + dir_);
	} else {
		cx_ = x_ + radius_*cos(dir_ - M_PI/2);
		cy_ = y_ + radius_*sin(dir_ - M_PI/2);
	}

}

CircleGeom::~CircleGeom() {}

/**
We use the logic of dividing the circle into pi/2 i.e 4 positions where we could go. 
We find out which positions are feasible and go to the closest.
**/
double CircleGeom::tell_me_circle(double hunter_x, double hunter_y, double *turn_ret, double *dist_ret){

	double ret = -1;

	for (double i =0; i<=2*M_PI; i+=M_PI/2.) {
		double xx = cx_ + radius_ * cos(i);
		double yy = cy_ + radius_ * sin(i);
		double turn_ret1;
		double dist_ret1;
		double tret = check_position(hunter_x, hunter_y, xx, yy, &turn_ret1, &dist_ret1);
		if (tret>0) {
			if (ret == -1) {
				*turn_ret = turn_ret1;
				*dist_ret = dist_ret1;
				ret = tret;
			} else {
				if (tret < ret) {
					*turn_ret = turn_ret1;
					*dist_ret = dist_ret1;
					ret = tret;
				}
			}
		}
	}


	return ret;
}

double CircleGeom::check_position(double hunter_x, double hunter_y, double tx, double ty, double *turn_ret, double *dist_ret) {
	double x_diff = tx - hunter_x;
	double y_diff = ty - hunter_y;
	double dist = sqrt(x_diff*x_diff+ y_diff* y_diff);

	// time taken by hunter car to reach the distance
	double hunter_t = dist / speed_;

	// time taken by rogue car to reach that 
	double theta1 = atan2(y_ - cy_, x_ - cx_);
	double theta2 = atan2(ty - cy_, tx - cx_);
	double dtheta = normalize_angle(theta2 - theta1);

	double dist_along_circle = dtheta*radius_;
	double rogue_t = dist_along_circle / speed_;

	if (hunter_t <rogue_t) {
		*dist_ret = dist;
		*turn_ret = atan2(ty - hunter_y, tx - hunter_x);
		return hunter_t;
	} else {
		return -1;
	}
}

double normalize_angle(double theta) {
	//angle normalization
    while (theta> M_PI) theta-=2.*M_PI;
    while (theta<-M_PI) theta+=2.*M_PI;
    return theta;
}

