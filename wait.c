#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
int x = 0xD4C3B2A1;

printf("x = %p :: WEXITSTATUS(x) = %p\n",x,WEXITSTATUS(x));

return 0;
}
