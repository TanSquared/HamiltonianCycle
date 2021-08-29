#include<stdio.h>
#include<stdlib.h>

void printarray(int *nc, int size)
{
    //nc is the solution array
    printf("A possible cycle is\n[");
    int i;
    for(i = 0; i < size-1; i++)
    {
        printf("%d, ", *(nc + i));
    }
    printf("%d, 1]\n", *(nc + size - 1));
}


void nodemark(int **g, int *n, int size, int i)
{
    //n is the solution aray and g is the graph
    //This function marks each value in the solution array
    *(n + i) = ((*(n + i)) + 1)%(size + 1);
    if(*(n + i) == 0)
    {
        return;
    }
    int pos = *(n + i) - 1;
    int prevpos = *(n + i - 1) - 1;
    if(*((*(g + pos)) + prevpos) == 0)  //Checks if consecutive positions are connected
    {
        nodemark(g, n, size, i);
        return;
    }
    for(int j = 0; j < size; j++)
    {
        if(i != j && *(n + i) == *(n + j))  //Checks if there are any repeating values in the solution array
        {
            nodemark(g, n, size, i);
            return;
        }
    }

    if (i == size - 1)
    {
        if(*((*(g + pos))) == 1)    //Checks if last and first position are connected
            printarray(n, size);
        nodemark(g, n, size, i);
    }
}

void graph(int **g, int *n, int size)
{
    for(int i = 1; i < size; i++)
    {
        nodemark(g, n, size, i);
        if(*(n + i) == 0)
        {
            if(i != 1)
            i = i - 2;  //At this step we go back to the previous position. We subtract by 2 as for loop is going to add 1
            else
            break;
        }
    }
}

int main()
{
    int size, i, j;
    printf("Enter the number of nodes that you want: ");
    scanf("%d", &size);
    int **g = (int **)malloc(size * sizeof(int *));
    for(i = 0; i < size; i++)
        *(g + i) = (int *)calloc(size, sizeof(int));
    int *n = (int *)calloc(size, sizeof(int));
    *n = 1;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(i == j)
            continue;
            if(i > j)
            {
                *((*(g + i)) + j) = *((*(g + j)) + i);
                continue;
            }
            printf("Enter value of edge (%d, %d): ", i+ 1, j + 1);
            scanf("%d", (*(g + i)) + j);
        }
    }

    graph(g, n, size);

    for(i = 0; i < size; i++)
    free(*(g + i));
    free(n);
    return 0;
}
