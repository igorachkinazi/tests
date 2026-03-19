#include<stdio.h>
#include<string.h>

#define TR_TRACE_MED 1
#define TR_TRACE_LOW 2

#define TRACE(a, str) \
    if(!strcmp(&#a[strlen(#a)-3], "MED")) func(TR_TRACE_MED, str); \
    else if(!strcmp(&#a[strlen(#a)-3], "LOW")) func(TR_TRACE_LOW, str); \
    else func(0, str);

//#define TRACE(a, str)   func(&#a[strlen(#a)-3], str)

void func(int t, char*str)
{
    printf("%d %s\n",t, str);
}

int main()
{
    TRACE(LVL_MED, "a");
    TRACE(LEVEL_LOW, "b");
    TRACE(LEVEL_HIGH, "c");
    return 0;
}
