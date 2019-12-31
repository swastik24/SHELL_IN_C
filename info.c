#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "shell.h"
#include "info.h"
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
int pinfo(char *s)
{
    char filename[1000];
   
    char * buff=(char *)malloc(sizeof(char)*2000);
    if(strlen(s)==0)
    {
        
        
        sprintf(filename,"/proc/%d/stat",piid);
    }
    else
    {
        
        strcpy(filename,"/proc/");
        strcat(filename,s);
        strcat(filename,"/stat");
        
    }    
    FILE *f=fopen(filename,"r");
    if(f!=NULL)
    {
        if(strlen(s)==0)
            printf("pid -- %d\n",piid);
        else
        {
            printf("pid -- %s\n",s);
        }
            
        size_t sz=0;
        char str[200][200];
        int index=0;
        while(getline(&buff,&sz,f)!=-1)
        {
            for(char *p = strtok(buff," "); p != NULL  ; p = strtok(NULL, " "))
            {
                strcpy(str[index],p);
          
                index++;
                
            }            

    
        }
        printf("Process Status -- %s\n",str[2]);
        printf("memory -- %s {Virtual Memory}\n",str[22]);
        free(buff);
        if(strlen(s)==0)
        sprintf(filename,"/proc/%d/exe",piid);
        else
        {
            strcpy(filename,"/proc/");
            strcat(filename,s);
            strcat(filename,"/exe"); 
        }
        
        char path[2000];
        if(readlink(filename,path,63)==-1)
        {
            printf("Error:unable to find executable\n");
            return 0;

        }
        int x=strlen(path_name);
        if(strncmp(path_name,path,x)==0)
        {
            char sys[200]="~";
            for(int i=x;i<strlen(path);i++)
            {
                strncat(sys,&path[i],1);
            }
            printf("Executable path -- %s\n",sys);
        }
        else        
        printf("Executable path -- %s\n",path);

    }
    else
    {
        perror("File does not exist");

    }
    
    
  
    return 0;
}
