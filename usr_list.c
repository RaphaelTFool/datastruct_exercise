/*************************************************************************
	> File Name: usr_list.c
	> Author: 
	> Mail: 
	> Created Time: Fri 12 Oct 2018 02:20:10 AM EDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"

#define N 10

#define DBG_PRINT(fmt, ...) \
        printf("[%-6.5s:%06d] "fmt"\n", __func__, __LINE__, ##__VA_ARGS__)

struct numnode_t
{
    int num;
    struct list_head list;
};

struct numhead_t
{
    int count;
    struct list_head list;
};

static int doublelist_init(struct numhead_t *head, int n)
{
    struct numnode_t *listnode;
    int i;

    DBG_PRINT("starting init double list ...");
    INIT_LIST_HEAD(&head->list);
    head->count = 0;

    for (i = 0; i < n; i++)
    {
        listnode = (struct numnode_t *)malloc(sizeof(struct numnode_t));
        if (NULL == listnode)
        {
            DBG_PRINT("failed to malloc a memory for \"struct numnode_t\"");
            continue;
        }
        listnode->num = i + 1;
        list_add_tail(&listnode->list, &head->list);
        head->count++;
        DBG_PRINT("Node %d has been added to the double list", i + 1);
    }

    return head->count;
}

static void doublelist_print(struct numhead_t *head)
{
    int i = 1;
    struct numnode_t *work;
    struct list_head *pos;

    DBG_PRINT("There is total %d nodes in double list", head->count);
    list_for_each(pos, &head->list)
    {
        work = list_entry(pos, struct numnode_t, list);
        DBG_PRINT("Node %d's data: %d", i, work->num);
        i++;
    }

    return;
}

static int doublelist_destroy(struct numhead_t *head)
{
    struct list_head *pos, *n;
    struct numnode_t *p;
    int i = 1;

    DBG_PRINT("There is total %d nodes in double list", head->count);
    list_for_each_safe(pos, n, &head->list)
    {
        list_del(pos);
        p = list_entry(pos, struct numnode_t, list);
        free(p);
        head->count--;
        DBG_PRINT("Node %d has been removed from the doublelist ...", i++);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    struct numhead_t head;
    int n = N;

    if (argc > 2)
    {
        printf("Usage: %s [node count#]\n", argv[0]);
        printf("e.g. %s %d(default)\n\n", argv[0], N);
        exit(EXIT_FAILURE);
    }

    if (argc == 2)
    {
        n = atoi(argv[1]);
    }

    if (0 == doublelist_init(&head, n))
    {
        DBG_PRINT("failed to add node to doublelist");
        exit(EXIT_FAILURE);
    }
    doublelist_print(&head);
    doublelist_destroy(&head);
    
    return 0;
}
