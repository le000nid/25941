#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *str;
    struct node *next;
};

int main()
{
    char buf[256];
    struct node *head = NULL;
    struct node *tail = NULL;

    while (fgets(buf, sizeof(buf), stdin) != NULL) {

        if (buf[0] == '.')
            break;

        struct node *p = malloc(sizeof(struct node));

        p->str = malloc(strlen(buf) + 1);
        strcpy(p->str, buf);

        p->next = NULL;

        if (head == NULL)
            head = p;
        else
            tail->next = p;

        tail = p;
    }

    struct node *p = head;

    while (p != NULL) {
        printf("%s", p->str);
        p = p->next;
    }

    return 0;
}