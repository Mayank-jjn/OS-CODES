#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2], fd2[2], n;
    char buffer[100];

    pipe(fd);
    pipe(fd2);

    pid_t p = fork();

    if (p > 0)
    {
        printf("Passing value to child\n");
        write(fd[1], "hello\n", 6);

        n = read(fd2[0], buffer, 100);
        printf("Parent received: ");
        write(1, buffer, n);
    }
    else
    {
        n = read(fd[0], buffer, 100);
        printf("Child received: ");
        write(1, buffer, n);

        printf("Passing value to parent\n");
        write(fd2[1], "Hi Parent\n", 10);
    }

    return 0;
}