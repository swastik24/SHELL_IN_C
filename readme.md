HOW TO RUN THE FILE?

    1.To run first go to  the folder which all the .c and .h file.
    2.Type "make install" to run the shell
    3.Now from any directory u can run "./shell" 

Function Of Each .c File

1.shell.c
    This has the main func which find the ~ and loop for taking input continuously.

2.arg.c
    This has "input" func which divide the command on ; and store ach command in 2d string array.
3.map.c
    This has "commnd" func which check which has be given as input.
4.pwd.c
    Print absolute path  of the current working directory.
5.ls_exe.c
    This has "ls" func whicjh implements "ls" command along with various flag.
6.display.c
    Print prompt.
7.info.c 
    Implement pinfo command.
8.f_g.c
    Contains execvp command to execcute commands like vim ,emacs etc. 
9.setenv  and unsetenv.c 
    For creating and deleting environment variable
10.fore.c
    Bring a background process to foreground 
11.Back.c
    To run a stopped background process in background.
12. execute.c 
    Execute command
                