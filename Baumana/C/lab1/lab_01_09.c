// Лабораторная работа номер 1 Задача 8 вариант 3 . Выполнил ст гр ИУ7-21БВ Родинков Алексей +
#include <stdio.h>
#include <math.h>
int main(void)
{
	int top, d;
	float m, g, res;
	top = 0;
	int A[100] = {0};
	
	do {	
		printf("Write some numbers(maximum 100): ");
	 	d = scanf("%f",&m);
		if (m > 0 )
		{
			A[top] = m;
			top += 1;
		}	
	}while(((d == 1 && m > 0.0) && top < 100));
	
	for (int i = 0; i < top; i++)
		printf("A[%d] = %3d\n", i, A[i]);
	
	res = 1;
	for (int i = 0; i < top; i++)
		res *= (1. / (A[i] + i + 1));
	printf("This is result = %f\n", res);
	g = expf (res);
	printf("%f\n", g);
	// for (int i = 0; i < top; i++)
	// 	printf("%3d\n", A[i]);
	
	return 0;
}
