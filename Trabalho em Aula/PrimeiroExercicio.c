#include <stdio.h>
#include <math.h>

int main() {
    //Parte 1
    //1.
    printf("olá mundo");//a
    printf("\"olá mundo\"");//b
    int valuec = 4*4;//c
    int valued = 3*1000;//d
    long v1 = 3000000;
	long v2 = 9999999;
	long dsss = v1*v2;//e
    double raizsete = sqrt(177);//f
    double div = 20/3;//g
    double result = pow(7, 2);//h
    int sum = 0;
    for (int i = 0; i <= 5; ++i) {
        sum += i;
    }//i


    printf("\n");
    //Parte 2
    double rectangulo = 5 * 10;//a - retangulo
    double Trapezoide = ((10+10)/2)*20;//b - trapezio
    double triangulo = sqrt(10((10-7)(10-2)(10-5)));//c - triangulo
    

    printf("\n");

    //Parte 3 Numeros Primos
    printf("%d", primo(10));
    //Parte 4
    int valuep=0, values=1;
    printf("%d\n", valuep);
    while (valuep < 143)
    {
       values = values + valuep;
	   printf("%d\n", values);
	   valuep = values + valuep;
	   printf("%d\n", valuep);
    }
    
    
    return 0;
}

int primos(int numero){
    return numero % 2;
}