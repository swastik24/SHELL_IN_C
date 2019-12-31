#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"
#include "kjob.h"

void  kjob(char str[][200],int len)
{
    int x=0;
    int job_index=0;
    char res[20]="-";
    strcat(res,str[2]);
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
            //printf("%s\n",job_str);
            job_exist=1;
            break;
        }
    }
    if(job_index==1020 || job_exist==0)
    {
        perror("Job doesn't exist");
        return ;

    }   
    

    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        char answer[100];
        sprintf(answer,"%d",jobs_pid[i]); 
        char *arg[4];
        strcpy(str[0],"kill");
        arg[0]=str[0];
        arg[1]=res;
        arg[2]=answer;
        arg[3]=NULL;
        //printf("%s %s %s\n",arg[0],arg[1],arg[2]);
         x=execvp(arg[0],arg);
        if(x==-1)
        {
            perror("exec");
        }
        
        
        exit(0);
    }
    else if(pid>0)
    {
        if(wait(NULL)==-1)
        {
            perror("wait");
        }
    }    
    if(x!=-1)
    {
        printf("KILLED %d\n",jobs_pid[i]);
    }
    return ;
}
