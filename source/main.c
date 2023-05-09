#include <stdio.h>
#include "../libs/include/list.h"

int main()
{
    int n, val;

    List *l = list_construct();

    n = 200000;

    for (int i = 0; i < n; i++)
    {
        list_push_back(l, i, NULL);
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", list_get(l, i));

    // test the destroy function
    list_destroy(l);

    return 0;
}