#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

typedef struct ST
{
    int sp;
    int *a;
    int size;
}stack;

stack* CreateStack(int size);
void push(stack *st,int v);
int pop(stack *st);
bool is_full(stack *st);
bool is_empty(stack *st);

int main() {
    int res;
    char c;
    stack *st=CreateStack(100);
    for(scanf("%c",&c);c!='\n';scanf("%c",&c))
    {
        if(c>='0'&&c<='9')
        {
            push(st,c-'0');
        }
        else
        {
            int a,b;
            b=pop(st);
            a=pop(st);
            switch(c)
            {
                case'+':
                    push(st,a+b);
                    break;
                case'-':
                    push(st,a-b);
                    break;
                case'*':
                    push(st,a*b);
                    break;
                case'/':
                    push(st,a/b);
                    break;
            }
        }
    }
    res=pop(st);
    printf("Result:%d\n",res);
    return 0;
}
stack *CreateStack(int size)
{
    stack *ret=malloc(sizeof(stack));
    memset(ret,0,sizeof(stack));
    ret->a=malloc(sizeof(int)*(size+1));
    memset(ret->a,0,sizeof(int)*(size+1));
    ret->size=size;
    return ret;
}
void push(stack *st,int v)
{
    if(is_full(st)) return;
    st->a[st->sp++]=v;
    return;
}
int pop(stack *st)
{
    int ret;
    if(is_empty(st)) return 0;
    ret=st->a[--(st->sp)];
    return ret;
}
bool is_full(stack *st)
{
    return st->sp==st->size;
}
bool is_empty(stack *st)
{
    return st->sp==0;
}