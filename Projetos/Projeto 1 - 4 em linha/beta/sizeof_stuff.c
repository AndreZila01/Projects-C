
void f(int *a) {
    printf("%ld\n", sizeof(a));
    printf("%ld\n", sizeof(int));
    printf("%ld\n", sizeof(a) / sizeof(int));
}

int main() {
    int a[99];

    // printf("%ld\n", sizeof(a) / sizeof(int));

    // f(&(*a));

    int b = 3;
    int *p = &b;

    printf("%d\n", &(*p) == p);
    printf("%p\n", p);
    printf("%p\n", &(*(&(*p))));

    return 0;
}