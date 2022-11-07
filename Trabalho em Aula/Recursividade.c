#include <stdio.h>

int factorial(int n){
    if(n==0)
        return 1;
        
    return n * factorial(n-1);
}

int main(){
    int n = 10;
    printf("O factorial de %d é %d\n", n, factorial(n));
    return 0;
}