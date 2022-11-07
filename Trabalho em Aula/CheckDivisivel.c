#include <stdio.h>
#include <stdbool.h>

bool NumeroImparEDiv3(int numero){
    if(numero%3==0 && numero%2==1)
    return true;
    else 
    return false;
}

int main(){
    printf("Numeros impares e divisiveis por 3:\n");
    for(int value =0; value<2000; value++){
        if(NumeroImparEDiv3(value))
            printf("%d\t", value);
    }
    printf("\n");
    return 0;
}