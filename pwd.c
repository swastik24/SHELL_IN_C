#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <sys/utsname.h>
#include<string.h>

#include "pwd.h"

int parent ( )
{
    char path_name[20000];
    if(getcwd(path_name,sizeof(path_name))==NULL)
    {
        perror("getcwd() error");
        exit(1);

    }
    printf("%s\n",path_name);
    
    return 0;
}