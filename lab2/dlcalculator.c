#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle;
    double (*add) (double, double);
    double (*subtract) (double, double);
    double (*multiple) (double, double);
    double (*divide) (double, double);
    double num1, num2;
    char *error;

    handle = dlopen("./lib/libarithmatic.so", RTLD_LAZY);
    if (!handle)
    {
        fputs(dlerror(), stderr);
        exit(1);
    }

    add = dlsym(handle, "add");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s", error);
        exit(1);
    }

    subtract = dlsym(handle, "subtract");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s", error);
        exit(1);
    }

    multiple = dlsym(handle, "multiple");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s", error);
        exit(1);
    }

    divide = dlsym(handle, "divide");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s", error);
        exit(1);
    }

    printf("calculator program ! \n");
    printf("first num: ");
    scanf("%lf", &num1);
    printf("second num: ");
    scanf("%lf", &num2);

    printf("%lf + %lf = %lf\n", num1, num2, (*add)(num1, num2));
    printf("%lf - %lf = %lf\n", num1, num2, (*subtract)(num1, num2));
    printf("%lf * %lf = %lf\n", num1, num2, (*multiple)(num1, num2));
    printf("%lf / %lf = %lf\n", num1, num2, (*divide)(num1, num2));

    printf("thank you ! \n");

    dlclose(handle);
    return 0;
}

