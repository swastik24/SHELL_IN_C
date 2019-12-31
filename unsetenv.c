#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "execute.h"
#include "unsetenv.h"

void exe_unsetenv(char str[][200],int len)
{
    if(len==2)
    {
        if(unsetenv(str[1])!=0)
        {
            perror("Cannot unset the variable");
            return ;
        }
    }
    else
    {
        perror("Number  of argument is not correct");
        return ;
    }
    
}