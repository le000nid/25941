#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <ulimit.h>

extern char **environ;

int main(int argc, char *argv[])
{
    char op[argc];
    char *arg[argc];
    int n = 0, c, i;

    opterr = 0;

    while ((c = getopt(argc, argv, "ispuU:cC:dvV:")) != -1) {
        op[n] = c;
        arg[n] = optarg;
        n++;
    }

    for (i = n - 1; i >= 0; i--) {
        switch (op[i]) {

        case 'i':
            printf("uid=%d euid=%d gid=%d egid=%d\n",
                   getuid(), geteuid(), getgid(), getegid());
            break;

        case 's':
            if (setpgid(0, 0) == -1)
                perror("setpgid");
            break;

        case 'p':
            printf("pid=%d ppid=%d pgid=%d\n",
                   getpid(), getppid(), getpgrp());
            break;

        case 'u':
            printf("ulimit=%ld\n", ulimit(UL_GETFSIZE));
            break;

        case 'U':
            if (ulimit(UL_SETFSIZE, atol(arg[i])) == -1)
                perror("ulimit");
            break;

        case 'c': {
            struct rlimit r;
            getrlimit(RLIMIT_CORE, &r);
            printf("core=%ld bytes\n", (long)r.rlim_cur);
            break;
        }

        case 'C': {
            struct rlimit r;
            getrlimit(RLIMIT_CORE, &r);
            r.rlim_cur = atol(arg[i]);

            if (setrlimit(RLIMIT_CORE, &r) == -1)
                perror("setrlimit");
            break;
        }

        case 'd': {
            char buf[1024];

            if (getcwd(buf, sizeof(buf)))
                puts(buf);
            else
                perror("getcwd");

            break;
        }

        case 'v': {
            char **p;

            for (p = environ; *p; p++)
                puts(*p);

            break;
        }

        case 'V':
            if (putenv(arg[i]) != 0)
                perror("putenv");
            break;

        case '?':
            fprintf(stderr, "bad option\n");
            break;
        }
    }

    return 0;
}