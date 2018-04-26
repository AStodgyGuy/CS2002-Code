#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "process1.h"
#define PORT 1238

/**
 * Method to read from client
 */
void read_client(int socket, char* KEY_PATH)
{
    int valread;
    char buffer[1024] = {0};
    char decrypt[1024] = {0};
    FILE* kfp = fopen(KEY_PATH, "r");
    valread = read( socket , buffer, 1024);
    //read and display the encrypted string
    printf("Encrypted string received from client: %s\n", buffer);

    for (u_long i = 0; i < strlen(buffer); ++i)
    {
        decrypt[i] = cipher(buffer[i], kfp);
    }

    //display the decrypted string
    printf("Decrypted string: %s\n", decrypt);

}

/**
 * Method to check the input variables
 */
void chkin(char* KEY_PATH)
{

    //check if output path is accessible
    if (KEY_PATH != NULL)
    {
        assert(fopen(KEY_PATH, "r") != NULL);
    }
}


int main(int argc, char *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int flag = 0; /* Flag to detect invalid arg */
    char* key_file = NULL;
    int opti;

    //input flags
    while ((opti = getopt(argc, argv, "k:" )) != -1)
    {
        switch (opti)
        {
            case 'k':
                key_file = optarg;
                flag = 1;
                break;
            case ':': /* Fall through is intentional */
            case '?': /* Fall through is intentional */
            default:
                printf("usage: server -k keyfile\n");
                return 0;
        }
    }
    
    
    //no key file check
    if (flag == 0)
    {
        printf("usage: server -k keyfile\n");
        return 0;
    }
  
    //check the validity of the input files
    chkin(key_file);
      
    //creating the socket for clients to connect to
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    //attaching socket to the port specified above
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
      
    //attatch socket to the port specified above
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //listen for clients
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //when client connects, accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //read from client
    read_client(new_socket, key_file);

    return 0;
}