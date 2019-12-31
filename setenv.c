#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "execute.h"
#include "setenv.h"
void exe_setenv(char str[][200],int len)
{
    if(len==2)
    {
        if(setenv(str[1],"",1)!=0)
        {
            perror("Cannot set variable");
            return ;
        }

    }
    else if(len==3)
    {
        if(setenv(str[1],str[2],1)!=0)
        {
            perror("Cannot set variable");
            return ;
        }

    }
    else
    {
        if(len<2)
        {
            printf("Too  few argument for setenv\n");
        }
        else if(len>3)
        {
            printf("Too many arguments for setenv\n");
        }
        return ;
    }
    
}