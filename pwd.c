#include <unistd.h>
#include <stdio.h>
#include <limits.h>
void main() 
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
       printf("Current working dir: %s\n", cwd);
    } 
    else 
    {
      printf("\n error");
    }
   
}
