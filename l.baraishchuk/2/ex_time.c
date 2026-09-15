#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

extern char *tzname[];

int main() {
    time_t now;
    struct tm *sp;

    // Получаем текущее календарное время (количество секунд с эпохи UNIX)
    time(&now);

    // Выводим время в стандартном строковом формате (ctime)
    printf("%s", ctime(&now));

    // Преобразуем время в локальное для работы со структурой tm
    sp = localtime(&now);

    // Выводим дату и время в формате ММ/ДД/ГГ ЧЧ:ММ и часовой пояс
    printf("%d/%d/%02d %d:%02d %s\n",
        sp->tm_mon + 1, sp->tm_mday,
        sp->tm_year, sp->tm_hour,
        sp->tm_min, tzname[sp->tm_isdst]);

    exit(0);
}