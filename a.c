#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOO "hello world"
#define SQUARE(x) x*x
#define MAX(x, y) (x>y ? x : y)
#define IS_EVEN(x) (x%2 == 0)

int sum(int *start, int *end) {
    int total = 0;
    while (start < end) {
        total += *start;
        // printf("%p\n", start);
        start++;
    }
    return total;
}

int sum_array(int arr[], int length) {
    int total = 0;
    for (int i = 0; i < length; ++i)
    {
        total += arr[i];
    }
    return total;
}

typedef struct {
    char *name;
    char title[100];
    float price;
} car;

void happy(car c) {
    // the argument `c` just a copy of struct, so it can not modify the outer struct
    c.price += 1;
}

void happy2(car *c) {
    c->price += 1; // (*c).price
}

int main() {
    int a1[] = {1, 1, 2, 1, 2};
    int *p = a1;
    // printf("%d\n", p[4]);
    // if (*(p+1) == a1[1])
    // {
    //     printf("true\n");
    // }
    printf("%d\n", sum(a1, a1+5));
    printf("%d\n", *(a1+2)); // 数组名就是指针
    printf("%d\n", sum_array(p, 5));
    char *arr = (char *)malloc(sizeof(char) * 2);
    *arr = '1';
    *(arr+1) = '2';
    *arr = '3';
    // strcpy(arr, "ab");
    printf("%c\n", arr[0]);
    free(arr);

    char* s1 = "Hello, world!";
    // s1[0] = 'z'; // 错误
    char s2[] = "Hello, world!";
    s2[0] = 'z'; // 正确
    s1 = "world"; // 正确
    // s2 = "world"; // 错误
    char s3[10];
    // s3 = "abc"; // 错误
    strcpy(s3, "abc"); // 正确
    char *s4 = "abc"; // `abc` is solid, read-only, s4 point to it
    s4 = "ddd"; // `ddd` is also solid, read-only, s4 point to it
    char s5[] = "fff";
    s4 = s5; // now, `fff` is in heap memory
    *s4 = 'x'; // so, it can be modified
    s4[1] = 'y'; // and can be modified in array form
    printf("%s\n", s4);

    car b1 = {.name = "baba", .price=100, .title="Game Of T"};
    car b2 = b1;
    b2.name = "ahaha";
    printf("%s %s\n", b1.name, b2.name);
    happy(b1);
    printf("%f\n", b1.price);
    happy2(&b1);
    printf("%f\n", b1.price);
    // b1.title = "hulu"; // wrong, char array cannot assign by '=' after allocation, use `strcpy()` instead

    struct species {
        char *name;
        int kinds;
    };
    struct fish {
        char *name;
        int age;
        struct species breed;
    };
    struct fish moo = {
        .age = 2,
        .name = "BoMooo",
        .breed = {"fish", 55}
    };
    typedef struct node {
        int data;
        struct node *next;
    } node;
    node *node1 = malloc(sizeof(node));
    node1->data = 1;
    node1->next = malloc(sizeof(node));
    node1->next->data = 2;
    node1->next->next = malloc(sizeof(node));
    node1->next->next->data = 3;
    for (node *cur = node1; cur != NULL; cur = cur->next) {
        printf("%d\n", cur->data);
    }

    union foo {
        int a;
        float b;
        char c;
    } ux;
    int *ux1 = (int *)&ux;
    float *ux2 = (float *)&ux;
    char *ux3 = (char *)&ux;
    ux.a = 222;
    puts("-----1-----");
    printf("%d\n", ux.a);
    printf("%f\n", ux.b);
    printf("%c\n", ux.c);
    printf("%d\n", *ux1);
    ux.b = 2.3;
    puts("-----2-----");
    printf("%d\n", ux.a);
    printf("%f\n", ux.b);
    printf("%c\n", ux.c);
    printf("%f\n", *ux2);
    ux.c = 'x';
    puts("-----3-----");
    printf("%d\n", ux.a);
    printf("%f\n", ux.b);
    printf("%c\n", ux.c);
    printf("%c\n", *ux3);
    puts("----end----");
    enum colors {RED,GREEN,BLUE};
    printf("%d %d %d\n", RED, GREEN, BLUE);
    enum colors color1 = GREEN;
    printf("%d\n", color1);
    puts(FOO);
    printf("%d\n", SQUARE(3 + 4)); // 3 + 4*3 + 4
    printf("%f\n", MAX(3.4, 3.5)); // 3.50000
    printf("%d\n", IS_EVEN(3)); // 0
    printf("%d\n", IS_EVEN(4)); // 1
    return 0;
}
