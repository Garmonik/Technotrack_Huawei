#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

#include"QuadraticEquation.h"

//=============================================================================================

int main(){

	double x_1 = NAN, 
	       x_2 = NAN;

	unit_test(&x_1, &x_2);

	int task_code = enter (&x_1, &x_2);

	out_res(task_code, &x_1, &x_2);
	return 0;
}

//=============================================================================================

void unit_test(double *x_1, double *x_2){
	assert(x_1 != NULL);
	assert(x_2 != NULL);

	TEST(1, 2, 2, 0, 0, 1);
	TEST(1, 2, 0, 0, -2, 2);
	TEST(1, 2, 1, -1, -1, 3);
	TEST(0, -2, 0, 0, 0, 4);
	TEST(3, 1, -9, ((-1+sqrt(109))/6), ((-1-sqrt(109))/6), 5);
	TEST(2, 1, 7, 0, 0, 6);
	TEST(1, 1, -2, 1, -2, 7);
	TEST(4, 2, 1, 0, 0, 8);
	TEST(0, 0, 0, 0, 0, 9);
	TEST(2, -3, -2, 2, -0.5, 10);
}

//---------------------------------------------------------------------------------------------

int enter(double *x_1, double *x_2){
	assert(x_1 != NULL);
	assert(x_2 != NULL);

	printf("Hello!!!\n"
               "The Program started working...\n"
               "Enter 3 number for Quadratic equation.(a*x^2 + b*x + c = 0):\n");

	double a = NAN, 
	       b = NAN, 
	       c = NAN;

	while(scanf("%lf %lf %lf", &a, &b, &c) != 3){
		printf("Enter 3 number\n");
		fflush(stdin); // while (getchar (...) != '\n')
	}

	int task_code = square_eq (a, b, c, x_1, x_2);
	return task_code;
}

//---------------------------------------------------------------------------------------------

int is_zero(double value){

        if (fabs (value) < EXP)
                return 1;
        else
                return 0;
}

//---------------------------------------------------------------------------------------------

//ax+b = 0
double line_eq(double a, double b, double *x_1, double *x_2){
        assert(x_1 != NULL);
        assert(x_2 != NULL);
	assert(x_1 != x_2);

        if(is_zero(a)){
                if(is_zero(b)){
                        *x_1 = *x_2 = 0;
                        return -1;
                }
                else{
                        *x_1 = *x_2 = 0;
                        return 0;
                }
        }
        else{
                if(is_zero(-b/a))
                        *x_1 = *x_2 = 0.0;
                else
                        *x_1 = *x_2 = -b/a;

                return 1;
        }
}

//---------------------------------------------------------------------------------------------

//ax^2+bx+c = 0
double square_eq(double a, double b, double c, double *x_1, double *x_2){
	assert(x_1 != NULL);
	assert(x_2 != NULL);
       	assert(x_1 != x_2);

	if(is_zero (a))
		return line_eq(b, c, x_1, x_2);
	else{
		double Discr = b*b - 4*a*c;

		if((is_zero(Discr) == 0) && (Discr < 0)){
			*x_1 = *x_2 = 0;
			return 0;
		}
		else if(is_zero(Discr)){
			if(is_zero(-b/2/a))
				*x_1 = *x_2 = abs(-b/(2*a));
			else 
				*x_1 = *x_2 = -b/(2*a);
			return 1;
		}
		else if((is_zero(Discr) == 0) && (Discr > 0)){
			double Discr1 = sqrt(Discr);
			*x_1 = (-b + Discr1)/(2*a);
			*x_2 = (-b - Discr1)/(2*a);
			return 2;
        		}
	}
	return -3;
}

//---------------------------------------------------------------------------------------------

void out_res(int task_code, double *x_1, double *x_2){
	assert(x_1 != NULL);
	assert(x_2 != NULL);

	if(task_code == 0)
		printf("No roots\nx_1 = x_2 = 0\n");
	else if(task_code == 1)
		printf ("The problem has one roots x_1 = x_2 = %.6lf\n", *x_1);
	else if(task_code == 2)
		printf ("The problem has two roots x_1 = %.6lf and x_2 = %.6lf\n", *x_1, *x_2);
	else if(task_code == -1) 
		printf ("All roots\nx_1 = x_2 = 0\n");
	else 
		printf("Error!!!");
}
