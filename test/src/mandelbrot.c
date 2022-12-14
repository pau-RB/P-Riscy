#include"../API/api.h"
#include"../MMIO/mmio.h"

#define MAX_THD 8
#define FRAME_SIZE 128
#define STACK_SIZE 128

#define BASE 8192
#define STEP 512
#define MAXITER 100
#define INFTY 4*BASE

char child_stack[MAX_THD][STACK_SIZE]={1};
char child_frame[MAX_THD][FRAME_SIZE]={1};

typedef struct {
	int r;
	int i;
} Complex;

inline int fromint(int a) {
	return BASE*a;
}

inline Complex com(int r, int i) {
	Complex res = {r,i};
	return res;
}

inline Complex add(Complex a, Complex b)
	{return com(a.r+b.r,a.i+b.i);}

inline Complex sub(Complex a, Complex b)
	{return com(a.r-b.r,a.i-b.i);}

inline Complex mul(Complex a, Complex b)
	{return com((a.r*b.r-a.i*b.i)/BASE,(a.r*b.i+a.i*b.r)/BASE);}

inline int modsq(Complex a)
	{return (a.r*a.r+a.i*a.i)/BASE;}

int inside(Complex c) {
	Complex z = {0,0};
	for(int i = 0; i < MAXITER; ++i) {
		if(modsq(z) > INFTY)
			return 0;
		z = add(mul(z,z),c);
	}
	return 1;
}

int mandelbrot(int l, int r, int b, int t) {
	int a;
	for (int i = b; i < t; i+=STEP)
    	for (int j = l; j < r; j+=STEP)
    		a = inside(com(j,i));
    return a;
}

int mandelbrot4(int l, int r, int b, int t) {

	int h = (l+r)/2;
	int v = (b+t)/2;

	fork4(l,h,b,v,(void*)mandelbrot,child_frame[0],child_stack[0]+STACK_SIZE);
    fork4(l,h,v,t,(void*)mandelbrot,child_frame[1],child_stack[1]+STACK_SIZE);
    fork4(h,r,b,v,(void*)mandelbrot,child_frame[2],child_stack[2]+STACK_SIZE);
    fork4(h,r,v,t,(void*)mandelbrot,child_frame[3],child_stack[3]+STACK_SIZE);

    wait(child_frame[0]);
    wait(child_frame[1]);
    wait(child_frame[2]);
    wait(child_frame[3]);

}

int main() {

	

	printLSR('S');

	int a = mandelbrot4(fromint(-2),fromint(1),fromint(-1),fromint(1));

    printLSR('E');

    return a;

}
