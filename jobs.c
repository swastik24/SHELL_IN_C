#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"
#include "jobs.h"
void job()
{
    
    int job_index=0;
    for(int i=0;i<=jobs_length;i++)
    {
        char filename[200];
        char * buff=(char *)malloc(sizeof(char)*2000);
        sprintf(filename,"/proc/%d/status",jobs_pid[i]);
        FILE *f=fopen(filename,"r");
        char str[200];
        if(f!=NULL)
        {
            size_t sz=0;
            job_index++;
            int index=0;
            while(getline(&buff,&sz,f)!=-1)
            {
                if(index==2)
                    break;
                index++;
            }
            index=0;
            int no_count=0;
            int j=0;
            while(no_count<2)
            {
                if(buff[j]==')')
                    break;
                if(no_count==1)
                {
                    str[index]=buff[j];
                    index++;
                    
                }
                if(buff[j]=='(')
                    no_count++;
                j++;    
                    
            }
            str[index]='\0';
            if(strlen(str)==0)
            {
                job_index--;
                continue;
            }
            printf("[%d] %s %s [%d]\n",job_index,str,jobs_name[i],jobs_pid[i]);
           
            
           
            
            
        }
        
    }    
    return ;    

    
}