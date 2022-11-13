#include <stdio.h>
#include <string.h>

struct person {
    char name[80];
    int age;
};

void register_person(char* name, int age, struct person arr[], int idx) {
    strcpy(arr[idx].name, name);
    arr[idx].age = age;
}

int main() {
    struct person users[3];
    register_person("André", 39, users, 0);
    register_person("Miguel", 49, users, 1);
    register_person("Daniel", 6, users, 2);


    for(int i=0; i<3; i++) {
        printf("%s (%d)\n",users[i].name, users[i].age);
    }
    return 0;
}