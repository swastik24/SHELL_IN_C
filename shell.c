#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#include <errno.h>
#include <sys/utsname.h>
#include "display.h"
#include "arg.h"
#include "shell.h"
#include "f_g.h"
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include<fcntl.h> 
#include<signal.h>
int main();
int  loop();
char path_name[20000];
int piid;
char his[20][100];
int no=-1;
int msize=1020;
char  p_name[1020][200];
int p_num[1020];
char path_his[2000];
char jobs_name[1020][200];
int jobs_pid[1020];
int jobs_length=-1;

int main()
{
     
    for(int i=0;i<msize;i++)
    {
        p_num[i]=-1;
    }
     
    piid=getpid();
    char filename[1000];
    sprintf(filename,"/proc/%d/exe",piid);
    char path[2000];
    if(readlink(filename,path,93)==-1)
    {
        printf("Error:unable to find executable\n");
        return 0;
    }

    strncpy(path_name,path,strlen(path)-6);
    strcpy(path_his,path_name);
    strcat(path_his,"/history.txt");
    FILE *fp = fopen(path_his, "wx"); 
    

    loop();
    fclose(fp);
    return 0;
}
int  loop()
{
    z=0;
    int count_upkey=0;
    signal(SIGTSTP, sighandler);
    signal(SIGINT, sighandler);
    z=0;
    char str[20000];
	no=-1;
  
    for(int row=0;row<=19;row++)
    {
        for(int col=0;col<=99;col++)
        {
            his[row][col]='\0';
        }
    }
    FILE * my;
    my=fopen(path_his,"r");
    
    size_t len=0;
    char *line=NULL;
    ssize_t read;

    while ((read = getline(&line, &len, my)) != -1) {
        no=no%20;
       
        if(line[read-1]=='\n')
        {
            line[read-1]='\0';
            read-=1;
        }    
        strncpy(his[(no+1)%20],line,read); 
       // printf("%s\n",his[(no+1)%20]); 
        no+=1;  
        no=no%20;
    }
    
    
    fclose(my);
   // printf("SHIT\n");
 
 
        do{
        int pid,pid_status;
        while((pid=waitpid(-1,&pid_status, WNOHANG | WUNTRACED))>0)
        {
            if(WIFEXITED(pid_status)){
                for(int i=0;i<msize;i++)
                {
                    if(p_num[i]==pid)
                    {
                        
                        printf("%s with pid %d exited normally.\n",p_name[i],p_num[i]);
                        p_num[i]=-1;
                        break;
                    }
                }
            }
        }
        break;
    }while(1==1);

    dis(path_name);


    
    fgets(str,2000,stdin);
    int str_length=strlen(str);
    if(str[str_length-1]=='\n')
    {
        //printf("HELP\n");
        str[str_length-1]='\0';
        str_length-=1;
    }
   // printf("%s %ld %d\n",str,strlen(str),str_length);
    if((str_length)%3==0)
    {
        for(int j=0;j<str_length;j++)
        {
            if((int)str[j]==27 && (int)str[j+1]==91 && (int)str[j+2]==65)
            {
                j=j+2;
                count_upkey++;
                continue;
            }
            else
            {
                break;
            }
            
        
        }
    }    
   // printf("1\n");
    int countofkey=count_upkey;
    int upkey=no;
    while(count_upkey>1 && upkey>=0)
    {
        upkey--;
        upkey=(upkey+20)%20;
        count_upkey--;
    }
   // printf("2\n");

    if(no!=-1 && countofkey==str_length/3 && countofkey>0)
    {
        //printf("SOME PROBLEM\n");
        strcpy(str,"\0");
        strcpy(str,his[(upkey+20)%20]);
        dis(path_name);
        printf("%s\n",str);
        
        
        
    }
    if(countofkey!=str_length/3 && countofkey>0)
        loop();
    //printf("%s\n",str);
    input(str);
    loop();
    return 0;
       
    
}
