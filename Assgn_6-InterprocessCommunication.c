// Reader :
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#define FIFO_PIPE "xyz"
int main()
{
    int fd,i,c=0,w=0,l=0;
    char str[100];
    fd = open(FIFO_PIPE,O_RDONLY);
    read(fd,str,sizeof(str));
    for(i=0;str[i]!='\0';i++)
    {
        if(str[i] == ' '|| str[i] == '\n')
        w++;
        if(str[i] == '\n')
        l++;
    c++;
    }
printf("\n No of characters = %d",c);
printf("\n No of lines = %d", l+1);
printf("\n No of words = %d \n",w);
close(fd);
return 0;
}

// Writer : 
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#define FIFO_PIPE "xyz"
int main()
{
    int fd,i=0;
    char str[200], ch;
    mkfifo(FIFO_PIPE,0644);//Pipe Created 
    printf("\n Pipe Successfully created \n");
    printf("\n Enter your message(press @ to terminate) \n");
    while((ch = fgetc(stdin)) != '@')
    {
        str[i++] = ch;
    }
    str[i] = '\0';//Null character
    fd = open(FIFO_PIPE,O_WRONLY);
    write(fd,str,strlen(str));
    close(fd);
    return 0;
}


// 1. Theory: Interprocess Communication (IPC) is a mechanism provided by operating systems that allows two or more independent processes to exchange data and communicate with one another. A process is a program that is currently executing, and each process normally has its own separate memory space. Since independent processes cannot directly access each other's memory, IPC mechanisms are required to transfer information between them. Common IPC techniques include pipes, named pipes (FIFOs), message queues, shared memory, sockets, and signals. A pipe is an IPC mechanism that allows data to flow from one process to another in the form of a continuous stream of bytes. Pipes are generally used for communication between processes, where one process writes data into the pipe and another process reads that data. There are two main types of pipes: unnamed pipes and named pipes. An unnamed pipe is generally used for communication between related processes, such as a parent and child process, and does not have a permanent name in the file system. A named pipe, also called FIFO (First In, First Out), allows independent or unrelated processes to communicate using a common pipe name. FIFO follows the principle that data written first is read first, maintaining the order in which information is transferred. A named pipe is created using the mkfifo() system call, which creates a special file in the file system that processes can access using its name. Unlike a regular file, a FIFO does not store data permanently; instead, the operating system temporarily buffers the data until another process reads it. The open() system call is used to open the FIFO for reading or writing. The mode O_WRONLY opens the FIFO for writing, while O_RDONLY opens it for reading. The write() system call sends data into the pipe, and the read() system call receives data from it. The close() system call closes the file descriptor after communication is completed. By default, opening a FIFO for reading or writing may block until another process opens the opposite end. Unidirectional communication means data flows in only one direction, from sender to receiver, whereas bidirectional communication allows both processes to send and receive information. In full-duplex communication, both processes can exchange data in both directions, and two named pipes are commonly used to provide separate communication channels. In this assignment, the Writer Process accepts a message from the user and sends it through a named pipe called xyz, while the Reader Process receives the message and calculates the number of characters, words, and lines. The writer accepts input until the user enters the termination character @, which indicates that the message is complete. The reader then processes the received string using a loop. Characters are counted by examining each character in the string, words are estimated by counting spaces and newline characters, and lines are estimated by counting newline characters and adding one. This demonstrates how one process can transfer information to another process without directly sharing memory. However, the provided code implements only one-way communication, because the writer sends data to the reader through a single FIFO. The assignment specifies full-duplex communication, where the reader should also save the calculated results in a text file and send the file contents back to the writer through a second FIFO. These additional operations are not implemented in the given code. Also, counting spaces and newline characters does not always calculate the correct number of words, especially when multiple spaces are present. Thus, this program demonstrates the basic concepts of interprocess communication, named pipes, FIFO operation, data transfer, file descriptors, and communication between independent processes in an operating system.

// 2. Code Explanation: The program consists of two separate C programs called the Reader Program and Writer Program, which communicate using a named pipe. Both programs include header files such as stdio.h, string.h, fcntl.h, and unistd.h. The stdio.h header provides functions such as printf() and fgetc() for input and output, string.h provides string-handling functions such as strlen(), fcntl.h provides file-opening modes such as O_RDONLY and O_WRONLY, and unistd.h provides system calls such as read(), write(), and close(). The writer additionally includes sys/types.h and sys/stat.h, which provide definitions required for creating a named pipe using mkfifo(). Both programs use the statement #define FIFO_PIPE "xyz" to define the common name of the FIFO through which communication takes place. In the Writer Program, the main function begins by declaring the integer variables fd and i, where fd stores the file descriptor returned by the open() system call, and i keeps track of the current position in the character array. The variable i is initialized to zero. The character array str[200] is declared to store the message entered by the user, while the variable ch temporarily stores each character entered from the keyboard. The statement mkfifo(FIFO_PIPE, 0644) creates a named pipe called xyz in the current directory. Here, 0644 represents the file permissions, allowing the owner to read and write while other users have read permission, subject to the process's permission mask. The printf() statements display a message indicating that the pipe has been created and instruct the user to enter a message ending with @. The while loop uses the condition (ch = fgetc(stdin)) != '@' to read characters one by one from standard input until the termination character @ is encountered. The statement str[i++] = ch stores each entered character in the string and automatically increments the index for the next character. Once the user enters @, the loop terminates, and str[i] = '\0' adds a null character at the end of the string to indicate its termination. The statement fd = open(FIFO_PIPE, O_WRONLY) opens the named pipe in write-only mode. If no process has opened the FIFO for reading, this operation normally waits until a reader becomes available. The statement write(fd, str, strlen(str)) sends the entered message through the FIFO. The function strlen(str) calculates the number of characters in the string, excluding the terminating null character, so only the message characters are written. The statement close(fd) closes the pipe's file descriptor after writing is completed, and return 0 terminates the writer program. In the Reader Program, the main function begins by declaring integer variables fd, i, c, w, and l, where fd represents the file descriptor, i is the loop counter, c stores the character count, w stores the word count, and l stores the newline count. The variables c, w, and l are initialized to zero. The character array str[100] is declared to store the message received from the writer. The statement fd = open(FIFO_PIPE, O_RDONLY) opens the same named pipe xyz in read-only mode. If the writer has not opened the pipe, this operation normally waits until a writer becomes available. The statement read(fd, str, sizeof(str)) reads up to 100 bytes of data from the FIFO and stores them in the character array. After receiving the data, the program uses the for loop for(i = 0; str[i] != '\0'; i++) to examine each character until a null character is encountered. Inside the loop, the condition if(str[i] == ' ' || str[i] == '\n') checks whether the current character is a space or newline. If either condition is true, w++ increases the word counter by one. The condition if(str[i] == '\n') checks whether the character represents a newline, and if so, l++ increases the line counter. The statement c++ increases the character counter for every character examined, including spaces and newline characters. Once the loop finishes, the statement printf("\n No of characters = %d", c) displays the total number of characters. The statement printf("\n No of lines = %d", l+1) displays the estimated number of lines by adding one to the newline count, assuming that the message contains at least one line. The statement printf("\n No of words = %d \n", w) displays the estimated word count. Finally, close(fd) closes the reader's file descriptor, and return 0 terminates the program. One important limitation in the given code is that the writer does not transmit the terminating null character because strlen(str) excludes it, while the reader assumes that the received data ends with '\0'. Since read() does not automatically append a null character, the reader may access uninitialized memory or read beyond its array. The writer also allows a message larger than the reader's 100-character buffer, and neither program checks for input or system-call errors. Additionally, the reader does not save the results to a text file or send them back through a second FIFO, as required for the full-duplex assignment. Therefore, the current program demonstrates basic unidirectional interprocess communication using a named pipe, where one process writes a message and another process reads it and calculates character, word, and line counts.