#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/utsname.h>
#include<string.h>
#include "map.h"
#include "pwd.h"
#include "shell.h"
#include "info.h"
#include "f_g.h"
#include "execute.h"
#include "ls_exe.h"

int command(char s[][200],int count)
{
    int fd[2];
    int saved_stdout=dup(1);
    int saved_stdin=dup(0);
    int check_redirect=0;
    int fd_in;
    int no_command=0;
    char command[100][200];
    int no_redirect=-1;
    for(int i=0;i<count;i++)
    {
        //char *copy=s[i];
       if(s[i][0]!=' ')
       {
            //printf("%s",s[i]);
            int last=strlen(s[i]);
            if(s[i][last-1]=='\n')
                s[i][last-1]='\0';
            if(strcmp(his[(no+20)%20],s[i])!=0 || no==-1 )
            {
                strcpy(his[(no+1)%20],s[i]);
                int re=strlen(s[i]);
                if(his[(no+1)%20][re-1]=='\n')
                    his[(no+1)%20][re-1]='\0';
                no+=1;
               // printf("%s NNNNN\n",his[no%20]); 

                no=no%20;
                    
            } 
           

        }
	    

	    char ans[200];
        strcpy(ans,s[i]);/* code */
        int len=0;
        char str[100][200];
        int index=0;
        for(char *p = strtok(s[i]," "); p != NULL  ; p = strtok(NULL, " "))
        {   
            
            if(strlen(p)==0|| strcmp(p," ")==0 ||strcmp(p,"\0")==0 ||p[0]==10||p[0]==9)
            {
            
                continue;
            }
            
            
            strcpy(str[index],p);
            len++;
            index++;
        }
    
        char fake_string[100][200];
        for(int j=0;j<100;j++)
        {
            for(int z=0;z<200;z++)
            {
                fake_string[j][z]='\0';
            }
        }
        int indexsplit_1=0;
        int indexsplit_2=0;
        int indexsplit_3=0;
        for(;indexsplit_1<len;indexsplit_1++)
        {
           // printf("%s\n",str[indexsplit_1]);
            for(int j=0;j<strlen(str[indexsplit_1]);j++)
            {
                if(str[indexsplit_1][j]=='|')
                {
                    if(j!=0)
                        indexsplit_2++;
                    indexsplit_3=0;
                    fake_string[indexsplit_2][indexsplit_3]='|';
                    
                    indexsplit_2++;
                    continue;
                }
                else if(str[indexsplit_1][j]=='>' && j<strlen(str[indexsplit_1]) && str[indexsplit_1][j+1]=='>')
                {
                    if(j!=0)
                        indexsplit_2++;
                    indexsplit_3=0;
                    fake_string[indexsplit_2][indexsplit_3]='>';
                    fake_string[indexsplit_2][indexsplit_3+1]='>';
                    
                        indexsplit_2++;
                    j++;
                    continue;
                }
                else if(str[indexsplit_1][j]=='>')
                {
                    if(j!=0)
                        indexsplit_2++;
                    indexsplit_3=0;
                    fake_string[indexsplit_2][indexsplit_3]='>';
                    
                        indexsplit_2++;
                    continue;
                }
                else if(str[indexsplit_1][j]=='<')
                {
                    if(j!=0)
                        indexsplit_2++;
                    indexsplit_3=0;
                    fake_string[indexsplit_2][indexsplit_3]='<';
                    
                        indexsplit_2++;
                    continue;
                }
                fake_string[indexsplit_2][indexsplit_3]=str[indexsplit_1][j];
                indexsplit_3++;
            }
            if(strlen(fake_string[indexsplit_2])!=0)
                indexsplit_2++;
            indexsplit_3=0;
        }
        for(int j=0;j<indexsplit_2;j++)
        {
            strcpy(str[j],fake_string[j]);
           // printf("%s %ld\n",str[j],strlen(str[j]));
        }


    len=indexsplit_2;
    index=indexsplit_2;

    //printf("%d\n",len);

    for(int it=0;it<len;it++)
    {
        if(strcmp(str[it],">")==0 || strcmp(str[it],"<")==0 || strcmp(str[it],"|")==0 ||strcmp(str[it],">>")==0)
        {
            check_redirect=1;
            strcpy(command[no_command],str[it]);
            no_command++;
        }
    }
    if(check_redirect==1)
    {
        int it=0;
        char str_command[5][200];
        for(int iterate=0;iterate<len;iterate++)
        {
           // printf("%s\n",str[iterate]);
           // printf("shit\n");
            if(strcmp(str[iterate],"<")==0)
            {
                no_redirect+=1;
                if(strcmp(command[no_redirect+1],">")==0)
                {
                    no_redirect+=1;
                    //printf("HELLO\n");
                    char *p=strtok(str[len-1],"\n");
                    int fd_out=open(p,O_CREAT|O_WRONLY|O_TRUNC,0644);
                    char * q=strtok(str[iterate+1],"\n");
                   // printf("%d %s %s\n",it,p,q);
                    fd_in=open(q,O_RDONLY);
                    dup2(fd_in,0);
                   dup2(fd_out,1);
                    
                    execute(str_command,it);
                    dup2(saved_stdin,0);
                    dup2(saved_stdout,1);
                    close(fd_out);
                    close(fd_in);
                    break;
                }
                else if(strcmp(command[no_redirect+1],">>")==0)
                {
                    char *p=strtok(str[iterate+1],"\n");
                    fd_in=open(p,O_RDONLY);
                    dup2(fd_in,0);
                    char * q=strtok(str[iterate+3],"\n");
                    int fd_out=open(q,O_CREAT|O_WRONLY|O_APPEND,0644);
                    dup2(fd_out,1);
                    execute(str_command,it);
                    close(fd_in);
                    close(fd_out);
                    dup2(saved_stdin,0);
                    dup2(saved_stdout,1);
                    no_redirect+=1;
                    iterate+=3;
                    break;
                }
                else if(strcmp(command[no_redirect+1],"|")==0)
                {
                   // printf("AA GAYE\n");
                   no_redirect+=1;
                    if(pipe(fd)<0)
                    {
                        perror("Pipe");
                        
                    }
                    else
                    {
                       
                            char * q=strtok(str[iterate+1],"\n");
                           
                            fd_in=open(q,O_RDONLY);
                            dup2(fd_in,0);
                            
                        
                        
                        dup2(fd[1],1);
                        execute(str_command,it);
                        dup2(saved_stdout,1);
                        close(fd_in);
                        dup2(fd[0],0);
                        close(fd[1]);
                        close(fd[0]);
                        iterate+=2;
                        //printf("%s\n",str[iterate]);
                    }
                    it=0;
                }
                else
                {
                    char *p=strtok(str[len-1],"\n");
                    fd_in=open(p,O_RDONLY);
                    dup2(fd_in,0);
                    execute(str_command,it);
                    dup2(saved_stdin,0);
                    dup2(saved_stdout,1);
                    close(fd_in);
                    break;
                }
                
            }
            else if(strcmp(str[iterate],"|")==0)
            {
                no_redirect+=1;
                
                    if(pipe(fd)<0)
                    {
                        perror("Pipe");
                        
                    }
                    else
                    {
                        dup2(fd[1],1);
                        execute(str_command,it);
                        dup2(saved_stdin,0);
                        close(fd[1]);
                        dup2(fd[0],0);
                        dup2(saved_stdout,1);
                        close(fd[0]);
                    }
                    it=0;
                
                

            }
            else if(strcmp(str[iterate],">")==0)
            {
               // printf("DHIT\n");
                no_redirect+=1;
                if(no_command==1)
                {
                    char *p=strtok(str[iterate+1],"\n");
                    int fd_out=open(p,O_CREAT|O_WRONLY|O_TRUNC,0644);
                    dup2(fd_out,1);
                    execute(str_command,it);
                    close(fd_out);
                    dup2(saved_stdout,1);
                    break;
                }
                else if(strcmp(command[no_redirect-1],"|")==0)
                {
                //    printf("SHHHHHHIT\n");
                    char *p=strtok(str[iterate+1],"\n");
                    int fd_out=open(p,O_CREAT|O_WRONLY|O_TRUNC,0644);
                    dup2(fd_out,1);
                    execute(str_command,it);
                    dup2(saved_stdout,1);
                    close(fd_out);
                    dup2(saved_stdin,0);
                    break;
                }
                
            }
            else if(strcmp(str[iterate],">>")==0)
            {
                //printf("OHSHIT\n");
                char * p=strtok(str[iterate+1],"\n");
                //printf("%s %d %ld\n",p,it,strlen(p));
                int fd_out=open(p,O_WRONLY|O_CREAT|O_APPEND,0644);
                dup2(fd_out,1);
                execute(str_command,it);
                
                dup2(saved_stdout,1);
                dup2(saved_stdin,0);
                close(fd_out);
                break;

            }
            else
            {
                strcpy(str_command[it],str[iterate]);
                it++;
                continue;
            }
            
            
        }
        
        if(strcmp(command[no_command-1],"|")==0)
        {
            dup2(saved_stdout,1);
            //printf("FUCK\n");
            
            //printf("%s",str_command[0]);
            execute(str_command,it);
            dup2(saved_stdin,0);
            dup2(saved_stdout,1);
        }  
        

    }
    else
    {
        //printf("SHIT %s\n",path_his);
        execute(str,len);
    }
    if(check_redirect==1)
    {
       
        dup2(saved_stdout,1);
        dup2(saved_stdin,0);
    }
    // dup2(saved_stdout,1);
    // dup2(saved_stdin,0);
    //printf("SHIT OH FUCK\n");
    FILE *my;
    my=fopen(path_his,"w");
   

    no=no+1;
    int sum_total=0;
    for(; sum_total<20;)
    {

        no=(no+20)%20;
        sum_total++;    
        
        if(strlen(his[(no)%20])==0)
        {
            no+=1;
            continue;
        }
        fprintf(my,"%s",his[(no)%20]);
        fprintf(my,"%s","\n");
        no+=1;
    }
    fclose(my);
    }
    return 0;

}
