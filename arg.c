#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arg.h"
#include "map.h"
#include "arg.h"
int input(char *s)
{
    char str[100][200];
    int i=0;
    int count=0;
    for(int i=0;i<strlen(s);i++)
    {
        if(i>0 && s[i]==';' && s[i-1]==';')
        {    
            perror("Command does not exist");
            return 1;
        }
    }
    for(char *p = strtok(s,";"); p != NULL; p = strtok(NULL, ";"))
    {
        //printf("%s %ld\n",p,strlen(p));
        if(strlen(p)==0||strcmp(p,";")==0||strcmp(p," ")==0)
        {
            perror("Command does not exist");
            return 0;
        }
        strcpy(str[i],p);
        count++;
        i++;
    }
 //  printf("%d %d\n",i,count);
    command(str,count);
    return 0;
}
