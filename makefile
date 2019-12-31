install:
		gcc -Wall shell.c back.c map.c arg.c pwd.c display.c info.c  f_g.c ls_exe.c execute.c jobs.c fore.c kjob.c setenv.c unsetenv.c -o shell