#include <stdio.h>
#include <math.h>

int main() {
    printf("olá mundo");
    printf("\"olá mundo\"");
    int mult = 4*4;
    double div = 20/3;
    double result = pow(7, 2);
    int sum = 0;
    for (int i = 0; i <= 5; ++i) {
        sum += i;
    }
    double raiz = sqrt(50);

    printf("\n");

    int count =0;
    do{
        count++;
    }while (count==count++);
    
    int valuep=0, values=1;
    printf("%d\n", valuep);
    while (valuep!=-1)
    {
        valuep++;
        printf("%d\n", valuep);
        printf("%d\n", values);
        valuep = values+valuep;
    }
    
    
    return 0;
}