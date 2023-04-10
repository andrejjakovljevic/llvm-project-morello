#include<stdio.h>

typedef struct hello
{
    /* data */
    int p;
    int k;
};


int main()
{
    int l = 1;
    struct hello h;
    printf("size is=%lu",sizeof(h));
    printf("Hello world\n");
    return 0;
}