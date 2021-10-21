#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

//===============================================================================
///     \brief tests
///     \author Kolyadich Mark
///     \version 1.0
///     \date 10.09.2021
///     \details function that tests the program
///     \param *x_1 [out] first answer
///     \param *x_2 [out] second answer
//===============================================================================
void unit_test(double *x_1, double *x_2);

//===============================================================================
///     \brief enter condition
///     \author Kolyadich Mark
///     \version 1.0
///     \date 10.09.2021
///     \details function that takes basic values
///     \param *x_1 [out] first answer
///     \param *x_2 [out] second answer
//===============================================================================
int enter(double *x_1, double *x_2);

//===============================================================================
///     \brief zero check
///     \author Kolyadich Mark
///     \version 1.0
///     \date 10.09.2021
///     \details function checks the number and compares it to zero
///     \param value [in, out] number to be checked
///    	\return true(1) if the number is zero, false(0) if the number is not zero
//===============================================================================
int is_zero(double value);

//===============================================================================
///     \brief decision
///     \author Kolyadich Mark
///     \version 1.0
///     \date 10.09.2021
///     \details solves any quadratic equation
///     \param a [in] first parameter of the quadratic equation
///     \param b [in] second parameter of the quadratic equation
///     \param c [in] third parameter of the quadratic equation
///     \param *x_1 [out] first answer
///     \param *x_2 [out] second answer
///     \return indicator for the answer table
//===============================================================================
double square_eq(double a, double b, double c, double *x_1, double *x_2);

//===============================================================================
///     \brief decision
///     \author Kolyadich Mark
///     \version 1.0
///     \date 10.09.2021
///     \details solves any linear equation
///    	\param a [in] first parameter of the linear equation
///     \param b [in] second parameter of the linear equation
///     \param *x_1 [out] first answer
///     \param *x_2 [out] second answer
///     \return indicator for the answer table
//===============================================================================
double line_eq(double a, double b, double *x_1, double *x_2);

//===============================================================================
///     \brief result
///     \author Kolyadich Mark
///     \version 1.0
///     \date 10.09.2021
///     \details displays the result
///     \param task_code [in] indicator for the answer table
///     \param *x_1 [out] first answer
///     \param *x_2 [out] second answer
//===============================================================================
void out_res(int task_code, double *x_1, double *x_2);

#define EXP 1e-6


//===============================================================================
///     \brief test
///     \author Kolyadich Mark
///     \version 1.0
///     \date 10.09.2021
///     \details gives the test result
///     \param a [in] first parameter of the quadratic equation
///     \param b [in] second parameter of the quadratic equation
///     \param c [in] third parameter of the quadratic equation
///     \param *x_1 [out] first answer
///     \param *x_2 [out] second answerr
///     \param counter [out] test number
//===============================================================================
#define TEST( a, b, c, x1, x2, counter)                                     \
                square_eq (a, b, c, x_1, x_2);                              \
                if((x1 == *x_1) && (x2 == *x_2))                            \
                        printf("TEST №%d OK!\n", counter);                  \
                else{                                                       \
                        printf("TEST №%d NOT OK!!!\n", counter);            \
                        printf("True res X1 = %lf, X2 = %lf\n", x1, x2);    \
                        printf("You res x1* = %lf, x2* = %lf/n", x_1, x_2); \
                }                                                           \
                
#endif /* QUADRATIC_EQUATIONint enter_H */
