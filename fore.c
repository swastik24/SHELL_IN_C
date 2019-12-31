#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "execute.h"
#include "shell.h"
#include "fore.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<unistd.h>
//#include "f_g.h"
pid_t zz=0;
void sighand(int sig_num) 
{ 
    //printf("FFDD\n");
    if(zz>0)
        kill(zz,sig_num);
    zz=0;
}

void fore(char str[][200],int len)
{
    pid_t shellpid=getpid();
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
    zz=jobs_pid[i];
    signal(SIGTTOU,SIG_IGN);
    tcsetpgrp(0,getpgid(jobs_pid[i]));
    kill(jobs_pid[i],SIGCONT);
    signal(SIGTTOU,SIG_DFL);
    //int status_fore;
   // printf("FFF\n");
    signal(SIGTSTP, sighand);
    signal(SIGINT, sighand);	
    waitpid(jobs_pid[i],NULL,WUNTRACED);
    signal(SIGTTOU,SIG_IGN);
    tcsetpgrp(0,shellpid);
    signal(SIGTTOU,SIG_DFL);
    return;
}