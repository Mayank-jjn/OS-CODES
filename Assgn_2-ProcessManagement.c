#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int n, i, j, temp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Create child process
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!");
        return 1;
    }

    // Child process
    else if (pid == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        // Sort array using Bubble Sort
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        printf("Sorted array by Child: ");
        for (i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }

        printf("\nChild process completed.\n");
        exit(0);
    }

    // Parent process
    else
    {
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        // Sort array using Bubble Sort
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        printf("Sorted array by Parent: ");
        for (i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }

        // Wait for child process
        wait(NULL);

        printf("\nParent process completed.\n");
    }

    return 0;
}

/*
                    // Zombie Process

        if (pid == 0) {
            printf("Child finished\n");
            exit(0);
        }
        else {
            printf("Parent sleeping for 20 seconds\n");
            sleep(20);
            wait(NULL);
            printf("Zombie process removed\n");
        }

                    // Orphan Process

        if (pid == 0) {
            sleep(5);
            printf("Orphan Child\n");
            printf("Child PID: %d\n", getpid());
            printf("New Parent PID: %d\n", getppid());
        }
        else {
            printf("Parent exiting\n");
            exit(0);
        }

*/