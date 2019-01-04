#include "my_otp.h"
#include "process1.h"
#include "process2.h"
#include <sys/wait.h>

int main(int argc, char* argv []) 
{
    int flag = 0; /* Flag to detect invalid arg */
    int opt;
    char* in_path = NULL;
    char* out_path = NULL;
    char* key_file = NULL;

    //input flags
    while ((opt = getopt(argc, argv, "i:k:o:" )) != -1)
    {
        switch (opt)
        {
            case 'i':
                in_path = optarg;
                break;
            case 'o':
                out_path = optarg;
                break;
            case 'k':
                key_file = optarg;
                flag = 1;
                break;
            case ':': /* Fall through is intentional */
            case '?': /* Fall through is intentional */
            default:
                printf("usage: my_otp [-i infile] [-o outfile] -k keyfile\n");
                return 0;
        }
    }
    
    //no key file check
    if (flag == 0)
    {
        printf("usage: my_otp [-i infile] [-o outfile] -k keyfile\n");
        return 0;
    }

    //check the validity of the input files
    chkin(in_path, out_path, key_file);

    //process the files
    process(in_path, out_path, key_file);

    return 0;
}

/**
 * Method which encrypts a message and exports it
 */
void process(char* IN_PATH, char* OUT_PATH, char* KEY_PATH)
{
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
        //create process 2 for writing
        int child2 = fork();
        chkfork(child2);
        if (child2 == 0)
        {
            //run writing
            pexport(OUT_PATH, fd);
        }
        else
        {
            //close everything
            close(fd[0]);
            close(fd[1]);
            waitpid(child1, NULL, 0);
            waitpid(child2, NULL, 0);
        }
    }
}


/**
 * Method to check the input variables
 */
void chkin(char* INPUT_PATH, char* OUT_PATH, char* KEY_PATH)
{
    //check input path is accessible
    if (INPUT_PATH != NULL)
    {
        assert(fopen(INPUT_PATH, "r") != NULL);
    }

    //check output path is createable
    if (OUT_PATH != NULL)
    {
        assert(fopen(OUT_PATH, "a") != NULL);
    }

    //check if output path is accessible
    if (KEY_PATH != NULL)
    {
        assert(fopen(KEY_PATH, "r") != NULL);
    }
}

/**
 * Method to check the fork process did not fail
 */
void chkfork(int child)
{
    //check child1
    assert(child != -1);
}
