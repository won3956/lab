#include <stdio.h>
#include "arithmaticlib.h"

int main()
{
	double num1, num2;
	printf("calculator program \n");
	printf("first num: ");
	scanf("%lf", &num1);
	printf("second num: ");
	scanf("%lf", &num2);

	printf("%lf + %lf = %lf\n", num1, num2, add(num1, num2));
	printf("%lf - %lf = %lf\n", num1, num2, subtract(num1, num2)); 
	printf("%lf * %lf = %lf\n", num1, num2, multiple (num1, num2));
	printf("%lf / %lf = %lf\n\n", num1, num2, divide (num1, num2));

	printf("thank you ! \n");
	return 0;
}
