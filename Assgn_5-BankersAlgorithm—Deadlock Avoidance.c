
#include <stdio.h>

int main()
{
    int n, m;
    int alloc[10][10], max[10][10];
    int need[10][10], avail[10];
    int work[10], finish[10] = {0};
    int safe[10], count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available resources:\n");
    for (int j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]);
        work[j] = avail[j];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nNeed matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    while (count < n)
    {
        int found = 0;

        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 1;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        flag = 0;
                        break;
                    }
                }

                if (flag)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += alloc[i][j];
                    }

                    safe[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            break;
        }
    }

    if (count == n)
    {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe sequence: ");

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safe[i]);

            if (i != n - 1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is in UNSAFE state.\n");
        printf("Safe sequence does not exist.\n");
    }

    return 0;
}