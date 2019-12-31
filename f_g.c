#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include "f_g.h"
#include "shell.h"
#include<signal.h>

pid_t pid;
pid_t z=0;

void sighandler(int sig_num) 
{ 
    
    if(z>0)
        kill(z,sig_num);
    z=0;
} 

int fg(char  str[][200],int len)
{
    int t=0;
    for(int i=0;i<len;i++)
    {
       
        if(strcmp(str[i],"&")==0)
        {
            t=1;
            break;
        }    
    }
    //printf("%d\n",jobs_length);
    
    pid=fork();
    int x=0;
    
    if(pid == 0)
    {
       
         
        if( t==1 && strcmp(str[0],"vim")==0)
        {
            
            setpgid(0,0);
        }
        
        
        
        
            
        char *args[len+1];
        for(int i=0;i<len;i++)
        {
            args[i]=str[i];
        }
        args[len]=NULL;
        x=execvp(args[0],args);
        
        
        if(x==-1)
        {
            if(t==1 && x==-1)
            {
               
                jobs_length--;
            }    
            printf("exec :No such command \n");
           
        }

        
        exit(0);
    }
    else if(pid>0)
    {
        
        if( t==1)
        {
            z=-1;
            int i;
            for( i=0;i<msize;i++)
            {
                if(p_num[i]==-1)
                {
                    p_num[i]=pid;
                    strcpy(p_name[i],str[0]);
                    
                    break;
                }
            }
            if(i==msize)
            {
                perror("Too many Background Process");
                return 0;
            }
            jobs_pid[jobs_length+1]=pid;
            strcpy(jobs_name[jobs_length+1],str[0]);
            jobs_length++;

        }
        else
        {
            z=pid;
            int status_child;
            signal(SIGTSTP, sighandler);
            signal(SIGINT, sighandler);	
            waitpid(pid,&status_child,WUNTRACED );
            if(WIFSTOPPED(status_child) || x==1)
            {
                jobs_pid[jobs_length+1]=pid;
                strcpy(jobs_name[jobs_length+1],str[0]);
                jobs_length++;
            }

        }
        
       
    }
    
    
    return 0;    
    
}