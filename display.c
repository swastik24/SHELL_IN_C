#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/utsname.h>
#include<string.h>

#include "display.h"

int dis(char * original_path)
{
    char s[2000];
    s[0]='~';
    char host_name[2000];
    int hostname;
    hostname=getlogin_r(host_name,sizeof(host_name));
    if(hostname==-1)
    {
    
        perror("gethostname");
        exit(1);
    }
   
    struct utsname sys_data;
    int ret=uname(&sys_data);
    if(ret==-1)
    {
        perror("uname");
        exit(1);
    }
  
    char path_n[20000];
    if(getcwd(path_n,sizeof(path_n))==NULL)
    {
        perror("getcwd() error");
        exit(1);

    }
    int x=strlen(original_path);
    if(strcmp(path_n,original_path)==0 )
    {
        
        s[0]='~';
        s[1]='\0';
        printf("\e[1m\e[31m<%s@%s\e[0m:\e[1m\e[36m%s>\e[0m",host_name,sys_data.sysname,s);
    }
    else
    {
        if(strncmp(path_n,original_path,x)==0 && path_n[x]=='/')
        {
            for( ;x<strlen(path_n);x++)
            {

                strncat(s,&path_n[x],1);
            }    
            printf("\e[1m\e[31m<%s@%s\e[0m:\e[1m\e[36m%s>\e[0m",host_name,sys_data.sysname,s); 
            
        }
        else
        printf("\e[1m\e[31m<%s@%s\e[0m:\e[1m\e[36m%s>\e[0m",host_name,sys_data.sysname,path_n);
    }
    
    return 0;
    

}