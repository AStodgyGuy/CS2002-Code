#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include "process1.h"
#include "msg_queue.h"
#define PORT 1238
  
/**
 * Method to check the fork process did not fail
 */
void chkfork(int child)
{
    //check child1
    assert(child != -1);
}


/**
 * Method to check the input variables
 */
void chkin(char* INPUT_PATH, char* KEY_PATH)
{
    //check input path is accessible
    if (INPUT_PATH != NULL)
    {
        assert(fopen(INPUT_PATH, "r") != NULL);
    }

    //check if output path is accessible
    if (KEY_PATH != NULL)
    {
        assert(fopen(KEY_PATH, "r") != NULL);
    }
}

/**
 * Method to read from user
 */
void read_in(char* IN_PATH, char* KEY_PATH, int sock)
{
    MQueue* s = malloc(sizeof(MQueue));
    initMQueue(s);
    //create pipe
    int fd[2];
    pipe(fd);

    //create process 1 for encrpytion
    int child1 = fork();
    chkfork(child1);
    if (child1 == 0)
    {
        //run encrpytion
        pcipher(KEY_PATH, IN_PATH, fd);
    }
    else
    {
        //wait for encrpytion
        waitpid(child1, NULL, 0);
        char enc = EOF;
        close(fd[1]);

        //multi threading operation would come here

        //send ecnrypted message onto the queue
        while (read(fd[0], &enc, sizeof(char)) > 0)
        {
            send_msg(s, enc);
        }

        //dequeue all elements in the queue to send across network
        close(fd[0]);
        char buff[1024];
        int i = 0;
        Node* temp = s->head;
        while(temp != NULL)
        {
            buff[i] = read_msg(s)->data;
            ++i;
            temp = temp->next;
        }
        send(sock, buff, strlen(buff), 0);
    }
}


int main(int argc, char *argv[])
{
    
    int flag = 0; /* Flag to detect invalid arg */
    int opt;
    char* in_path = NULL;
    char* key_file = NULL;
    char* ip = NULL;
    int sock = 0;
    struct sockaddr_in serv_addr;

    //input flags
    while ((opt = getopt(argc, argv, "i:k:e:" )) != -1)
    {
        switch (opt)
        {
            case 'i':
                in_path = optarg;
                break;
            case 'k':
                key_file = optarg;
                flag = 1;
                break;
            case 'e':
                ip = optarg;
                flag = 2;
                break;
            case ':': /* Fall through is intentional */
            case '?': /* Fall through is intentional */
            default:
                printf("usage: client [-i infile] -k keyfile -e [server ip]\n");
                return 0;
        }
    }
    
    //no key file check
    if (flag != 2)
    {
        printf("usage: client [-i infile] -k keyfile -e [server ip]\n");
        return 0;
    }

    //check the validity of the input files
    chkin(in_path, key_file);

    //create the socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    //convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    //check if server is listening
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //read user input
    read_in(in_path, key_file, sock);
    
    return 0;
}
