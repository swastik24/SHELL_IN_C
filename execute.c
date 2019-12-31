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
#include "jobs.h"
#include "kjob.h"
#include "back.h"
#include "setenv.h"
#include "unsetenv.h"
#include "fore.h"
#include<signal.h>

int  execute(char  str[][200],int len)
{

    for(int i=0;i<len;i++)
    {
        char *p=strtok(str[i],"\n");
        strcpy(str[i],p);
    }
    if(strcmp(str[0],"setenv")==0)
    {
        exe_setenv(str,len);
        return 0;
    }
    else if(strcmp(str[0],"unsetenv")==0)
    {
        exe_unsetenv(str,len);
        return 0;
    }
	else if(strcmp(str[0],"bg")==0)
	{
		back(str,len);
		return 0;
	}
	else if(strcmp(str[0],"fg")==0)
	{
		fore(str,len);
		return 0;
	}

	if(len==1)
	{


		if(strcmp(str[0],"pwd")==0)
			parent();
        else if(strcmp(str[0],"overkill")==0)
        {
			for(int i=0;i<1020;i++)
			{
				if(kill(jobs_pid[i],0)==0 && jobs_pid[i]>0)
				{
					kill(jobs_pid[i],9);
				}
			}
		}  
        else if(strcmp(str[0],"quit")==0)
            exit(0);    
        else if(strcmp(str[0],"jobs")==0)
        {
            job();   
        }    
		else if(strcmp(str[0],"pinfo")==0)
		{
			char emp[20];
			pinfo(emp);
		} 
		else if(strcmp(str[0],"history")==0)
		{
			//printf("FUCK OFF!!!\n")
			int ini=no;
			ini=(no)%20;
			int total=0;
			int sum=0;
			for(;total<10 && sum<20;)
			{
				sum++;

				if(strlen(his[ini%20])==0)
					continue;
				else
				{
					printf("%s\n",his[ini%20]);
					ini--;
					ini=(ini+20)%20;
					total++;
				}    

			}
			return 0;
		}
		else if(strcmp(str[0],"cd")==0)
		{

			chdir(path_name);
		}  
		else if(strcmp(str[0],"ls")==0)
		{
			char s_1[20];
			char s_2[20];
			s_1[0]='\0';
			s_2[0]='\0';
			ls(s_1,s_2);

		} 
		else
		{

			
			fg(str,len);
		}
		return 0;

	}
	else if(len>=2)
	{
		
		if(strcmp(str[0],"echo")==0)
		{   
			for(int j=1;j<len;j++)
			{
				
				printf("%s ",str[j]);
			}
			printf("\n");
			return 0;

		}
		if(len==3 && strcmp(str[0],"ls")==0)
		{
			char *q_1=strtok(str[1],"\n");
			char *q_2=strtok(str[2],"\n");
			ls(q_1,q_2);
		}
        if(len==3 && strcmp(str[0],"kjob")==0)
        {
            kjob(str,len);
            return 0;
        }
		if(len==3)
		{

			fg(str,len);
             
		}
		if(len==2)
		{
			char *h=strtok(str[1],"\n");
			if(strcmp(str[0],"cd")==0)
			{


				char *q=strtok(str[1],"\n");
				//pr//intf
				if(strcmp(q,"~")==0)
				{
					chdir(path_name);  
				}
				else if(q[0]=='~')
				{
					char res[2000];
					int i;
					strcpy(res,path_name);


					for( i=1;i<strlen(q);i++)
					{

						strncat(res,&q[i],1);
					}


					chdir(res);
				}
				else
					chdir(q);

			}
			else if(strcmp(str[0],"pinfo")==0)
			{
				char *q=strtok(str[1],"\n");
				pinfo(q);
			}
			else if(strcmp(str[0],"history")==0)
			{
				//printf("SUCKSSSSSSSSS\n");
				int max=h[0]-'0';
				int ini=no;
				ini=(no+20)%20;
				int total=0;
				int sum=0;
				for(;total<max && sum<20;)
				{
					
					if(strlen(his[(ini+20)%20])==0)
					{
						sum++;
						continue;
					}
					else
					{
						printf("%s\n",his[(ini+20)%20]);
						ini--;
						ini=(ini+20)%20;
						total++;
					}    
					sum++;
				}
				return 0;
			}
			else if(strcmp(str[0],"ls")==0)
			{

				char *q=strtok(str[1],"\n");

				char s_r[20];
				s_r[0]='\0';
				if(q[0]=='-')
				{

					ls(q,s_r);
				}
				else
				{

					ls(s_r,q);
				}


			}
			else
			{

				fg(str,len);
			}


		}
	}
	else
	{
		fg(str,len);
		return 0;
	}
	return 0;
}

