#include <stdio.h>
#include <math.h>

#define RECURS_LEVEL_MAX  10
#define N_MAX             10

// pointer to function of one variable
typedef double(*Func1vFp)(double);

// example functions of one variable
double f_poly(double x) { // polynomial a[0] + a[1]x + ... + a[n]x^n

	return 2*pow(x,5)-4*pow(x,4)+3.5*pow(x,2)+1.35*x-6.25;

}

double f_rat(double x) {
	
	return 1/(pow(x-0.5,2)+0.01);

}

double f_exp(double x) {


	return 2*x*exp(-1.5*x)-1;
}

double f_trig(double x) {

	return x*tan(x);

}

// Quadratures

double lerp(double a, double b, double r)
{
	return b * r + a * (1 - r);
}

double calculate(Func1vFp f1,double a,double b,double c)
{
	return (b-a)*f1(c);
}

// rectangle rule, leftpoint
double quad_rect_left(Func1vFp f1, double a, double b, int n) {

	double result=0;
	double start=a;
	double end=a;


	for (int i = 1; i <= n; i++)
	{
		start=end;
		end=a+(i*(b-a)/n);
		result+=calculate(f1,start,end,start);
	}
	
	return result;
	
}

// rectangle rule, rightpoint
double quad_rect_right(Func1vFp f1, double a, double b, int n) {
	double result=0;
	double start=a;
	double end=a;


	for (int i = 1; i <= n; i++)
	{
		start=end;
		end=a+(i*(b-a)/n);
		result+=calculate(f1,start,end,end);
	}
	
	return result;


}

// rectangle rule, midpoint
double quad_rect_mid(Func1vFp f1, double a, double b, int n) {

	double result=0;
	double start=a;
	double end=a;


	for (int i = 1; i <= n; i++)
	{
		start=end;
		end=a+(i*(b-a)/n);
		result+=calculate(f1,start,end,(start+end)/2);
	}
	
	return result;



}


double calculate_trap(Func1vFp f1,double a,double b)
{
	return ((b-a)/2)*(f1(a)+f1(b));
}

// trapezoidal rule
double quad_trap(Func1vFp func, double a, double b, int n) {

	double result = 0;
	double sp = a; 
	double ep = a; 
	
	for (int i = 1; i <= n; i++)
	{
		sp = ep;
		ep = lerp(a, b, (double)i / n);
		result += (ep - sp) / 2 * (func(sp) + func(ep));	
	}
	return result;

}

// Simpson's rule
double quad_simpson(Func1vFp f, double a, double b, int n) {
	double result = 0;
	double sp = a; 
	double ep = a; 
	
	for (int i = 1; i <= n; i++)
	{
		sp = ep;
		ep = lerp(a, b, (double)i / n);
		result += (ep - sp) / 6 * (f(sp) + 4 * f((sp + ep) / 2) + f(ep));	
	}
	return result;
}

// pointer to quadrature function
typedef double (*QuadratureFp)(Func1vFp, double, double, int);

// array of pointers to integrand functions
Func1vFp func_tab[] = { f_poly, f_rat, f_trig, f_exp };

// array of pointers to quadrature functions
QuadratureFp quad_tab[] = {
	quad_rect_left, quad_rect_right, quad_rect_mid, quad_trap, quad_simpson };

// calls 'quad_no' quadrature function for 'fun_no' integrand function
// on interval [a, b] and n subintervals
double quad_select(int fun_no, int quad_no, double a, double b, int n) {

	return quad_tab[quad_no](func_tab[fun_no], a, b, n); 

}

// adaptive algorithm
double recurs(Func1vFp f, double a, double b, double S, double delta, QuadratureFp quad, int level) {
	double c=(a+b)/2;
	double s1=quad(f,a,c,1);
	double s2=quad(f,c,b,1);
	double sum=s1+s2;

	if (sum-S<=delta && sum-S>=-delta)
	{
		return sum;
	}
	
	if (level>RECURS_LEVEL_MAX)
	{
		return NAN;
	}
	

	return recurs(f, a, c, s1, delta / 2, quad, level + 1) + 
		recurs(f, c, b, s2, delta / 2, quad, level + 1);

}

// initialization for adaptive algorithm
double init_recurs(Func1vFp f, double a, double b, double delta, QuadratureFp quad) {
	return recurs(f,a,b,quad(f,a,b,1),delta,quad,0);

}

// double integrals

// pointer to function of two variables
typedef double (*Func2vFp)(double,double);

double func2v_2(double x, double y) {
	return 2 - x*x - y*y*y;
}

// sample functions to define the normal domain

double lower_bound2(double x) {
	return 0.7*exp(-2*x*x);
}
double upper_bound2(double x) {
	return sin(10*x);
}


// rectangle rule (leftpoint) - double integral over rectangular domain
double dbl_integr(Func2vFp f, double x1, double x2, int nx, double y1, double y2, int ny) {
	double sum = 0;
	double start_x, start_y;
	double end_x, end_y = y1;
	for (int iy = 1; iy <= ny; iy++)
	{
		double xs = 0;
		start_y = end_y;
		end_y = lerp(y1, y2, (double)iy / ny);
		end_x = x1;

		for (int ix = 1; ix <= nx; ix++)
		{
			start_x = end_x;
			end_x = lerp(x1, x2, (double)ix / nx);

			xs += (end_x - start_x) * f(start_x, start_y);
		}
		sum += (end_y - start_y) * xs;
	}
	return sum;
}

// rectangle rule (midpoint) - double integral over normal domain with respect to the x-axis
double dbl_integr_normal_1(Func2vFp f, double x1, double x2, int nx, double hy,
						   Func1vFp fg, Func1vFp fh) {

	double s = 0;
	double sx, sy;
	double ex = x1, ey;
	for (int ix = 1; ix <= nx; ix++)
	{
		sx = ex;
		ex = lerp(x1, x2, (double)ix / nx);

		double mx = (sx + ex) / 2;
		double y1 = fg(mx);
		double y2 = fh(mx);
		int ny = ceil((y2 - y1) / hy);

		ey = y1;

		for (int iy = 1; iy <= ny; iy++)
		{
			sy = ey;	
			ey = lerp(y1, y2, (double)iy / ny);
			s += (ex - sx) * (ey - sy) * f(mx, (sy + ey) / 2);
		}
	}
	return s;

}

// rectangle rule (leftpoint) - double integral over multiple normal
// domains with respect to the x-axis
double dbl_integr_normal_n(Func2vFp f, double x1, double x2, int nx, double y1, double y2,
		int ny, Func1vFp fg, Func1vFp fh)  {

	double s = 0;

	double hy = (y2 - y1) / ny;
	double sx, sy;
	double ex = x1, ey;
	for (int ix = 1; ix <= nx; ix++)
	{
		double ys = 0;
		sx = ex;
		ex = lerp(x1, x2, (double)ix / nx);

		double my1 = fg(sx);
		if (my1 < y1) my1 = y1;
		double my2 = fh(sx);
		if (my2 > y2) my2 = y2;

		int mny = ceil((my2 - my1) / hy);

		ey = my1;

		for (int iy = 1; iy <= mny; iy++)
		{
			sy = ey;
			ey = lerp(my1, my2, (double)iy / mny);
			ys += (ey - sy) * f(sx, sy);
		}
		s += (ex - sx) * ys;
	}
	return s;


}

// multiple quadratures

typedef double (*FuncNvFp)(const double*, int);
typedef int (*BoundNvFp)(const double*, int);

// sample function of three variables
double func3v(const double v[], int n) {
	return v[0] - v[1] + 2*v[2];
}

// sample predicate in 3D
int bound3v(const double v[], int n) { // a cylinder
	return v[0] > 0 && v[0] < 0.5 && v[1]*v[1] + (v[2]-1)*(v[2]-1) < 1;
}

// sample function of n variables
double funcNv(const double v[], int n) {
	double fv = 1.;
	for (int i = 1; i < n; ++i) {
		fv += sin(i*v[i]);
	}
	return fv;
}
// sample n-dimensional predicate (n-dim hypersphere)
int boundNv(const double v[], int n) {
	double r = 0.0;
	for (int i = 0; i < n; ++i) r += (v[i]-1)*(v[i]-1);
	return r <= 1.;
}

// multiple integrals over a cuboid with predicate (if boundary != NULL)
// rectangular rule (rightpoint)

struct vec3
{
	double x, y, z;
};

union vec3p
{
	double packed[3];
	struct vec3 vec;
};


double trpl_quad_rect(FuncNvFp f, double variable_lim[][2], const int tn[], BoundNvFp boundary) {
	double s = 0;
	union vec3p vp;
	struct vec3 *v = &vp.vec;

	int nx = tn[0], ny = tn[1], nz = tn[2];
	double x1 = variable_lim[0][0], x2 = variable_lim[0][1];
	double y1 = variable_lim[1][0], y2 = variable_lim[1][1];
	double z1 = variable_lim[2][0], z2 = variable_lim[2][1];
	double lx, ly, lz;

	v->x = x1;
	for (int ix = 1; ix <= nx; ix++)
	{
		double ps = 0;
		lx = v->x;	
		v->x = lerp(x1, x2, (double)ix / nx);
		v->y = y1;
		for (int iy = 1; iy <= ny; iy++)
		{
			double zs = 0;
			ly = v->y;
			v->y = lerp(y1, y2, (double)iy / ny);
			v->z = z1;
			for (int iz = 1; iz <= nz; iz++)
			{
				lz = v->z;
				v->z = lerp(z1, z2, (double)iz / nz);
				if (boundary == NULL || boundary(vp.packed, 3)) zs += (v->z - lz) * f(vp.packed, 3);
			}
			ps += (v->y - ly) * zs;
		}
		s += (v->x - lx) * ps;
	}
	return s;


}

// multiple integrals over a n-dim hypercuboid with predicate (if boundary != NULL)
// rectangular rule (midpoint)
void recur_quad_rect_mid(double *p_sum, FuncNvFp f, int variable_no, double t_variable[],
         double variable_lim[][2], const int tn[], int level, BoundNvFp boundary) {
	
	
	if (level == variable_no) 
	{
		double du = 1;
		for (int vi = 0; vi < variable_no; vi++)
			du *= (variable_lim[vi][1] - variable_lim[vi][0]) / tn[vi];
		if (boundary == NULL || boundary(t_variable, variable_no)) *p_sum += du * f(t_variable, variable_no);
		return;
	}

	double n = tn[level];
	double u1 = variable_lim[level][0], u2 = variable_lim[level][1];
	for (int i = 1; i <= n; i++)
	{
		t_variable[level] = lerp(u1, u2, ((double)i - 0.5) / n);
		recur_quad_rect_mid(p_sum, f, variable_no, t_variable, variable_lim, tn, level + 1, boundary);
	}
}

int main(void) {
	int to_do, n, nx, ny, integrand_fun_no, method_no, flag;
	int no_funcs = sizeof(func_tab) / sizeof(Func1vFp);
	int no_quads = sizeof(quad_tab) / sizeof(QuadratureFp);
	double a, b, x1, x2, y1, y2, hy, sum, delta;
	double t_variable[N_MAX], variable_lim[N_MAX][2];
	int tn[N_MAX];

	scanf("%d", &to_do);
	switch (to_do) {
		case 1: // loop over quadratures and integrands
			scanf("%lf %lf %d", &a, &b, &n);
			for(int q = 0; q < no_quads; ++q) {
				for(int f = 0; f < no_funcs; ++f) {
					printf("%.5f ",quad_select(f, q, a, b, n));
				}
				printf("\n");
			}
			break;
		case 2: // adaptive algorithm
			scanf("%d %d",&integrand_fun_no,&method_no);
			scanf("%lf %lf %lf", &a, &b, &delta);
			printf("%.5f\n", init_recurs(func_tab[integrand_fun_no],a,b,delta,quad_tab[method_no]));
			break;
		case 3: // double integral over a rectangle
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf %lf %d", &y1, &y2, &ny);
			printf("%.5f\n", dbl_integr(func2v_2, x1, x2, nx, y1, y2, ny));
			break;
		case 4: // double integral over normal domain
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf", &hy);
			printf("%.5f\n", dbl_integr_normal_1(func2v_2, x1, x2, nx, hy, lower_bound2, upper_bound2));
			break;
		case 5: // double integral over multiple normal domains
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf %lf %d", &y1, &y2, &ny);
			printf("%.5f\n",dbl_integr_normal_n(func2v_2, x1, x2, nx, y1, y2, ny, lower_bound2, upper_bound2));
			break;
		case 6: // triple integral over a cuboid
			scanf("%lf %lf %d", &variable_lim[0][0], &variable_lim[0][1], tn);
			scanf("%lf %lf %d", &variable_lim[1][0], &variable_lim[1][1], tn+1);
			scanf("%lf %lf %d", &variable_lim[2][0], &variable_lim[2][1], tn+2);
			scanf("%d", &flag);
			printf("%.5f\n", trpl_quad_rect(func3v, variable_lim, tn, flag ? bound3v : NULL));
			break;
		case 7: // multiple integral over hyper-cuboid
			scanf("%d", &n);
			if(n > N_MAX) break;
			for(int i = 0; i < n; ++i) {
				scanf("%lf %lf %d", &variable_lim[i][0], &variable_lim[i][1], tn+i);
			}
			scanf("%d", &flag);
			sum = 0.;
			recur_quad_rect_mid(&sum, funcNv, n, t_variable, variable_lim, tn, 0, flag ? boundNv : NULL);
			printf("%.5f\n", sum);
			break;
		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}
	return 0;
}

