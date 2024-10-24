double o_x(double t_x, double u_x);
double o_y(double t_y, double u_y);
double alpha(double t_x, double t_y, double u_x, double u_y);
double theta(double t_x, double t_y, double u_x, double u_y);
double beta(double alpha, double delta, double gamma); 
double delta(double k_x, double k_y, double o_x, double o_y);
double gammaCal(double theta, double k_x, double k_y, double o_x, double o_y);
double* w(double o_x, double o_y, double alpha, double beta, double theta);
double* v(double o_x, double o_y, double alpha, double beta, double theta);
