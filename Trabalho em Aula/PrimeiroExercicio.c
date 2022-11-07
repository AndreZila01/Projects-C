#include <stdio.h>
#include <math.h>


long factoriar(int numero){
    long value =1;
for(int numero=10; numero>=1;numero--){
value*=numero;
    }
    return value;
}

int primos(int numero)
{
    return numero % 2;
}

int Recursividade(int n){
    if(n == 0)
        return 0;
    else if(n==1)
        return 1;
    else 
        return Recursividade(n-1) + Recursividade(n-2);
}

int main()
{
    // Parte 1
    // 1.
    printf("olá mundo");     // a
    printf("\"olá mundo\""); // b
    int valuec = 4 * 4;      // c
    int valued = 3 * 1000;   // d
    // long v1 = 3000000;
    // long v2 = 9999999;
    // long dsss = v1 * v2;
    long valuee = 9999999L * 3000000L;// e
    double raizsete = sqrt(177); // f
    double div = 20 / 3;         // g
    double result = pow(7, 2);   // h
    int sum = 0;
    for (int i = 0; i <= 5; ++i)
    {
        sum += i;
    } // i

    printf("\n");
    // Parte 2
    double rectangulo = 5 * 10;                            // a - retangulo
    double Trapezoide = ((10 + 10) / 2) * 20;              // b - trapezio
    double triangulo = sqrt(((10+7+5)/2)*((10 - 7)*(10 - 2)*(10 - 5))); // c - triangulo

    printf("\n");
    // Parte 3 Numeros Primos
    printf("%d", primos(10));

    printf("\n");
    // Parte 4
    int valuep = 0, values = 1;
    printf("%d\n", valuep);
    while (valuep < 143)
    {
        values = values + valuep;
        printf("%d\n", values);
        valuep = values + valuep;
        printf("%d\n", valuep);
    }

    //printf("%d", Recursividade(10));

    printf("\n");
    // Parte 5
    long fatorial = factoriar(10);
    printf("Factorial do 10 é: %ld", fatorial);//a
    int valorcinco = 1;
    double valuebfive = (1/(valorcinco*(valorcinco+1)));//b
    double valuecfive = (valorcinco/(pow(valorcinco, 2)));//c

    

    return 0;
}
