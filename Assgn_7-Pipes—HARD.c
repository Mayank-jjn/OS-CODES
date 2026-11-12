
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2], fd, n;
    char filename[100], buffer[100];

    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        // Child Process
        close(p1[1]);
        close(p2[0]);

        read(p1[0], filename, 100);
        fd = open(filename, O_RDONLY);

        if (fd < 0) {
            printf("File not found\n");
            return 1;
        }

        while ((n = read(fd, buffer, 100)) > 0)
            write(p2[1], buffer, n);

        close(fd);
        close(p1[0]);
        close(p2[1]);
    }
    else {
        // Parent Process
        close(p1[0]);
        close(p2[1]);

        printf("Enter filename: ");
        scanf("%s", filename);

        write(p1[1], filename, strlen(filename) + 1);
        close(p1[1]);

        printf("\nFile Contents:\n");
        while ((n = read(p2[0], buffer, 100)) > 0)
            write(1, buffer, n);

        close(p2[0]);
        wait(NULL);
    }

    return 0;
}


// 1. Theory: Interprocess Communication (IPC) is a mechanism provided by operating systems that allows two or more processes to exchange information and coordinate their activities. A process is a program that is currently executing, and each process normally has its own separate memory space. Since independent processes cannot directly access each other's memory, IPC mechanisms are required to transfer data between them. Common IPC methods include pipes, named pipes (FIFOs), shared memory, message queues, sockets, and signals. A pipe is a communication mechanism that allows one process to send data to another process through a temporary buffer maintained by the operating system. Pipes follow the First In, First Out (FIFO) principle, meaning that the data written first is read first, maintaining the order of communication. A pipe is created using the pipe() system call, which creates two file descriptors: one for reading and another for writing. The reading end is represented by index 0, while the writing end is represented by index 1. For example, p1[0] represents the reading end of pipe p1, while p1[1] represents its writing end. There are two main types of pipes: unnamed pipes and named pipes. Unnamed pipes are generally used for communication between related processes, such as a parent and child process, whereas named pipes can be used for communication between independent processes through a common name in the file system. The fork() system call is used to create a new process called the child process, which is created from an existing process called the parent process. After fork() executes successfully, both the parent and child processes continue execution independently. The fork() function returns 0 in the child process and the child's process ID in the parent process. The child process inherits copies of the parent's open file descriptors, including the pipe descriptors, allowing both processes to communicate. Unidirectional communication means data flows in only one direction, whereas bidirectional communication allows data to flow in both directions. Full-duplex communication means that two processes can send and receive information in both directions, potentially at the same time. Since an ordinary unnamed pipe provides a one-way communication channel, two pipes can be used to establish full-duplex communication between a parent and child process. In this assignment, two pipes named p1 and p2 are created. The first pipe, p1, transfers a filename from the parent process to the child process, while the second pipe, p2, transfers the contents of the requested file from the child process back to the parent process. The parent process first accepts a filename from the user and writes it into the first pipe. The child process reads the filename from the first pipe and attempts to open the specified file using the open() system call. If the file exists, the child reads its contents using the read() system call and sends the data to the parent through the second pipe using the write() system call. The parent receives this data and displays it on the screen using standard output, which is generally the terminal. The operating system manages the transfer of data through the pipes, so the parent and child do not need to access each other's memory directly. The close() system call is used to close unnecessary pipe ends, which helps prevent resource wastage and ensures proper communication. The wait() system call allows the parent process to wait until the child process completes execution and collects its termination status, preventing the child from remaining as a zombie process. A zombie process is a process that has finished execution but whose termination status has not yet been collected by its parent. The program also demonstrates process synchronization, because reading from an empty pipe normally causes the process to wait until data becomes available or all writing ends are closed. Similarly, writing to a pipe may block when its buffer is full. Thus, this assignment demonstrates how two related processes communicate using unnamed pipes, how the fork() system call creates a child process, and how two separate pipes provide bidirectional communication. Although the two pipes allow full-duplex communication, this particular program uses them sequentially: the parent sends a filename, and the child returns the file contents. This technique is useful in operating systems for exchanging information, transferring data, and coordinating the execution of related processes.

// 2. Code Explanation: The program begins by including five header files: stdio.h, unistd.h, fcntl.h, string.h, and sys/wait.h. The stdio.h header provides functions such as printf() and scanf() for input and output operations. The unistd.h header provides system calls such as pipe(), fork(), read(), write(), and close(). The fcntl.h header provides file-opening functions and modes such as open() and O_RDONLY. The string.h header provides string-handling functions such as strlen(), while sys/wait.h provides the wait() function used for parent-child process synchronization. Inside the main function, the statement int p1[2], p2[2], fd, n declares two integer arrays representing the two pipes, along with the variables fd and n. The variable fd stores the file descriptor of the file opened by the child process, while n stores the number of bytes read during file operations. The character arrays filename[100] and buffer[100] are declared to store the filename and the file contents temporarily. The statements pipe(p1) and pipe(p2) create two unnamed pipes, each containing a reading end and a writing end. The first pipe is used to transfer the filename from the parent to the child, while the second pipe is used to transfer file contents from the child to the parent. The statement if (fork() == 0) creates a new child process using the fork() system call. Since fork() returns zero in the child process, the statements inside the if block are executed by the child, while the statements inside the else block are executed by the parent. In the Child Process, the statement close(p1[1]) closes the writing end of the first pipe because the child only needs to read the filename from this pipe. Similarly, close(p2[0]) closes the reading end of the second pipe because the child only needs to write the file contents into it. The statement read(p1[0], filename, 100) reads the filename sent by the parent through the first pipe and stores it in the filename array. The statement fd = open(filename, O_RDONLY) attempts to open the specified file in read-only mode. If the file cannot be opened, open() returns -1, and the condition if (fd < 0) becomes true. The program then displays "File not found" and returns 1, indicating unsuccessful execution of the child process. If the file opens successfully, the program enters the while loop while ((n = read(fd, buffer, 100)) > 0). The read() system call reads up to 100 bytes from the file and stores them in the buffer array. The return value is stored in n, representing the number of bytes successfully read. The loop continues as long as read() returns a positive value, meaning that file data is still available. Inside the loop, the statement write(p2[1], buffer, n) sends the bytes read from the file through the writing end of the second pipe. This process repeats until the entire file has been read. When the end of the file is reached, read() returns zero, causing the loop to terminate. The statements close(fd), close(p1[0]), and close(p2[1]) close the opened file and the remaining pipe descriptors used by the child. In the Parent Process, the statement close(p1[0]) closes the reading end of the first pipe because the parent only needs to send the filename. Similarly, close(p2[1]) closes the writing end of the second pipe because the parent only needs to receive the file contents. The statement printf("Enter filename: ") asks the user to enter the name or path of the file, and scanf("%s", filename) accepts the filename from the keyboard and stores it in the character array. The statement write(p1[1], filename, strlen(filename) + 1) sends the filename to the child through the first pipe. The function strlen(filename) calculates the length of the filename, and + 1 includes the terminating null character '\0', allowing the received data to be treated as a properly terminated C string. The statement close(p1[1]) closes the writing end of the first pipe after sending the filename. The parent then displays "File Contents:" and enters the loop while ((n = read(p2[0], buffer, 100)) > 0). This loop reads the file contents received from the child through the second pipe in blocks of up to 100 bytes. The statement write(1, buffer, n) displays the received bytes directly on the terminal. Here, the number 1 represents the standard output file descriptor (stdout). The loop continues until the child finishes sending data and closes its writing end, after which read() returns zero to indicate the end of the data stream. The statement close(p2[0]) closes the reading end of the second pipe once the file contents have been displayed. The statement wait(NULL) makes the parent wait for the child process to terminate and collects its termination status. Finally, the statement return 0 terminates the program successfully. The program uses two pipes to transfer information in opposite directions: Parent → Child through p1 and Child → Parent through p2. Thus, it demonstrates bidirectional interprocess communication using unnamed pipes, file handling, parent-child process creation, and process synchronization. For simplicity, the given code does not check whether pipe() or fork() succeeds, and scanf("%s", filename) does not restrict input length, so a very long filename could overflow the array. A more robust implementation would also check the return values of read() and write(). However, the program demonstrates the main working principle of full-duplex communication between parent and child processes using two pipes.