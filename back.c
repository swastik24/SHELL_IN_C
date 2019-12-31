#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "execute.h"
#include "shell.h"
#include "back.h"
#include <signal.h>
void back(char str[][200],int len)
{
    if(len!=2)
    {   
        if(len>2)
            perror("Too many argument");
        else
        {
            perror("Not many argument");
        }
        return ;
    }
    
    int job_index=0;
    
    int i;
    int job_exist=0;
    
    for(i=0;i<1020;i++)
    {
        //printf("%d\n",i);
        char filename[200];
        sprintf(filename,"/proc/%d/status",jobs_pid[i]);
        FILE * f=fopen(filename,"r");
        if(f!=NULL)
        {
           
            job_index++;
        }
        else
        {
            continue;
        }
        
        char job_str[200];
        sprintf(job_str,"%d",job_index);
        
        if(strcmp(job_str,str[1])==0)
        {
          
            job_exist=1;
            break;
        }
    }
    if(job_index==1020 || job_exist==0)
    {
        perror("Job doesn't exist");
        return ;

    }
    kill(jobs_pid[i],SIGCONT);
}