#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *f;

    printf("uid = %d, euid = %d\n", getuid(), geteuid());

    f = fopen("file", "r");
    if (f == NULL)
        perror("fopen");
    else {
        printf("file opened\n");
        fclose(f);
    }

    if (setuid(getuid()) == -1)
        perror("setuid");

    printf("uid = %d, euid = %d\n", getuid(), geteuid());

    f = fopen("file", "r");
    if (f == NULL)
        perror("fopen");
    else {
        printf("file opened\n");
        fclose(f);
    }

    return 0;
}