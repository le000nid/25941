#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char options[] = "f:dg:"; /* допустимые опции */
    int c, invalid = 0, dflg = 0, fflg = 0, gflg = 0;
    char *f_ptr, *g_ptr;

    printf("argc equals %d\n", argc);
    
    // Цикл разбора аргументов командной строки с помощью getopt
    while ((c = getopt(argc, argv, options)) != -1) {
        switch (c) {
        case 'd':
            dflg++;
            break;
        case 'f':
            fflg++;
            f_ptr = optarg; /* optarg указывает на аргумент опции -f */
            break;
        case 'g':
            gflg++;
            g_ptr = optarg; /* optarg указывает на аргумент опции -g */
            break;
        case '?':
        default:
            invalid++;
            break;
        }
    }

    printf("dflg equals %d\n", dflg);
    printf("fflg equals %d\n", fflg);
    printf("gflg equals %d\n", gflg);
    printf("invalid equals %d\n", invalid);
    printf("optind equals %d\n", optind);

    // Вывод оставшихся аргументов (не являющихся опциями), если они есть
    if (optind < argc) {
        printf("next parameter = %s\n", argv[optind]);
    }

    return 0;
}