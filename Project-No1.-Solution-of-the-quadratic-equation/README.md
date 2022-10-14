Квадратное уравнение<a name="TOP"></a>
===================

## Задача ##

Задача по поиску корней квадратного уравнения. Необходимо реализовать все возможные решения разачи с учетом всех значений коэффициентов a, b, c. Необходимо реализовать функцию тестирования и написать документацию.

## Алгоритм ##

Основной идеей этой задачи -- это решение квадратного уравнения через дискриминант.

## Функции ##

При решении задачи может получиться, что решение квадратных уравнений перейдет в решение линейного уравнения. Для этого необходимо реализовать отдельно функцию для решения линейных уравнеий

```C++
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
```

Затем используя эту функцию можем написать функцию для решния любого квадратного уравнения:

 ```C++
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
```

Проверку деления на 0 не достаточно с силу устройства языка, поэтому сделаем проверку на число, которое очень близко к 0:

```C++
#define EXP 1e-6
```

Основной сложностью была проверка делимости на 0 и делимости на маленьное отричательносе число в результате чего ответ становится -0, что не должно происходить, для этого используем следующее условие

```C++
if((is_zero(Discr) == 0) && (Discr < 0))
			*x_1 = *x_2 = 0;
```

Где функция is_zero указана ниже:

```C++
int is_zero(double value){

        if (fabs (value) < EXP)
                return 1;
        else
                return 0;
}
```

Теперь рассмотрим функцию тестирования. Она написана с помощью макроса:

```C++
#define TEST( a, b, c, x1, x2, counter)                                     
                square_eq (a, b, c, x_1, x_2);                              
                if((x1 == *x_1) && (x2 == *x_2))                            
                        printf("TEST №%d OK!\n", counter);                 
                else{                                                       
                        printf("TEST №%d NOT OK!!!\n", counter);            
                        printf("True res X1 = %lf, X2 = %lf\n", x1, x2);    
                        printf("You res x1* = %lf, x2* = %lf/n", x_1, x_2); 
                }                                                           
```

## Документация ##

Документация описана в хндере.
