#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include <grp.h>
#include "shell.h"
#include "ls_exe.h"
int ls(char *s1, char *s2)
{
  
  
    if(strlen(s1)==0 && strlen(s2)==0)
    {
        struct dirent *de;
        DIR *dr=opendir("./");
        if(dr==NULL)
        {
            perror("Could not open the directory");
            return 0;
        }  
        while((de=readdir(dr))!=NULL)
        {   
            
            if ( !strncmp(de->d_name, ".",1) || !strcmp(de->d_name, "..") )
            {
                continue;
            }
            
            printf("%s\n",de->d_name);
        }
        
        closedir(dr);
        
    
    }
    else if(strlen(s1)!=0 && strlen(s2)==0)
    {
        if(strcmp(s1,"-a")==0)
        {
            struct dirent *de;
            DIR *dr=opendir(".");
            if(dr==NULL)
            {
                perror("Could not open the directory");
                return 0;
            }  
            while((de=readdir(dr))!=NULL)
            {   
                
            
                printf("%s\n",de->d_name);
            }
            closedir(dr);
        }
        else if(strcmp(s1,"-l")==0)
        {
            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
            int i;
            struct dirent *myfile;
            struct stat fileStat;
            mydir=opendir(".");
            stat(".",&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            {
                    if(!strncmp(myfile->d_name, ".",1) || !strcmp(myfile->d_name, ".."))    
                        continue;
                    stat(myfile->d_name,&fileStat);  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                    printf("%ld ",fileStat.st_nlink);
                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                    printf("%4ld ",fileStat.st_size);
                    c=ctime(&fileStat.st_mtime);
                    for(i=4;i<=15;i++)
                    printf("%c",c[i]);
                    printf(" ");
                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir);  
            return 0;
        }   
        else if(strcmp(s1,"-al")==0||strcmp(s1,"-la")==0)
        {
            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
            int i;
            struct dirent *myfile;
            struct stat fileStat;
            mydir=opendir(".");
            stat(".",&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            {
                   
                    stat(myfile->d_name,&fileStat);  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                    printf("%ld ",fileStat.st_nlink);
                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                    printf("%4ld ",fileStat.st_size);
                    c=ctime(&fileStat.st_mtime);
                    for(i=4;i<=15;i++)
                    printf("%c",c[i]);
                    printf(" ");
                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir);  
            return 0;           
        }
    }
    
    else if(strlen(s1)==0 && strlen(s2)!=0)
    {
        
        struct dirent *de;
          if(s2[0]=='~')
        {
                        char res[2000];
                        int i;
                        strcpy(res,path_name);
                    

                        for( i=1;i<strlen(s2);i++)
                        {
                            
                            strncat(res,&s2[i],1);
                        }
                        strcpy(s2,res);
                        
        }
        DIR *dr=opendir(s2);
        if(dr==NULL)
        {
            perror("Could not open the directory");
            return 0;
        }  
        while((de=readdir(dr))!=NULL)
        {   
            
            if ( !strncmp(de->d_name, ".",1) || !strcmp(de->d_name, "..") )
            {
                continue;
            }
            
            printf("%s\n",de->d_name);
        }
        closedir(dr);
      
    }
    else if(strlen(s1)!=0 && strlen(s2)!=0)
    {
        if(s2[0]=='~')
        {
                        char res[2000];
                        int i;
                        strcpy(res,path_name);
                    

                        for( i=1;i<strlen(s2);i++)
                        {
                            
                            strncat(res,&s2[i],1);
                        }
                        strcpy(s2,res);
                        
        }
        if(strcmp(s1,"-a")==0)
        {
            struct dirent *de;
            DIR *dr=opendir(s2);
            if(dr==NULL)
            {
                perror("Could not open the directory");
                return 0;
            }  
            while((de=readdir(dr))!=NULL)
            {   
             

                
                printf("%s\n",de->d_name);
            }
            closedir(dr);  
        }
        else if(strcmp(s1,"-l")==0)
        {
            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
            int i;
            struct dirent *myfile;
            struct stat fileStat;
            mydir=opendir(s2);
            stat(s2,&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            {
                    if(!strncmp(myfile->d_name, ".",1) || !strcmp(myfile->d_name, ".."))    
                        continue;
                    stat(myfile->d_name,&fileStat);  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                    printf("%ld ",fileStat.st_nlink);
                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                    printf("%4ld ",fileStat.st_size);
                    c=ctime(&fileStat.st_mtime);
                    for(i=4;i<=15;i++)
                    printf("%c",c[i]);
                    printf(" ");
                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir);  
            return 0;
        }
        else if(strcmp(s1,"-al")==0 || strcmp(s1,"-la")==0)
        {
            struct passwd *pw;
            struct group *gp;
            DIR *mydir;
            char *c;
            int i;
            struct dirent *myfile;
            struct stat fileStat;
            mydir=opendir(s2);
            stat(s2,&fileStat);
            while((myfile=readdir(mydir))!=NULL)
            {
                   
                    stat(myfile->d_name,&fileStat);  
                    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
                    printf(" ");
                    printf("%ld ",fileStat.st_nlink);
                    pw=getpwuid(fileStat.st_uid);
                    printf("%s ",pw->pw_name);
                    gp=getgrgid(fileStat.st_gid);
                    printf("%s ",gp->gr_name);
                    printf("%4ld ",fileStat.st_size);
                    c=ctime(&fileStat.st_mtime);
                    for(i=4;i<=15;i++)
                    printf("%c",c[i]);
                    printf(" ");
                    printf("%s\n",myfile->d_name);
            }
            closedir(mydir);  
            return 0;           
        }
    }
   
    
    return 0;
}
