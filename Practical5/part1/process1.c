#include "process1.h"

/**
 * Method which utilises One Time Pad
 */
int cipher(int c, FILE* KEY_PATH)
{
    int key = fgetc(KEY_PATH);
    int output = (key^c);
    return output;
}

/**
 * Method which encrypts text
 */
void pcipher(char* KEY_PATH, char* IN_PATH, int* fd)
{
    close(fd[0]);
    int c;
    char e;
    FILE* kfp = fopen(KEY_PATH, "r");

    //input file exists
    if (IN_PATH != NULL)
    {
        FILE* ifp = fopen(IN_PATH,"r");
        while(1)
        {
            c = fgetc(ifp);
            if (feof(ifp))
            {
                break;
            }
            e = cipher(c, kfp);
            write(fd[1], &e, sizeof(char));
        }
      fclose(ifp);
    }
    //input file does not exist user passes input as stdin
    else
    {
        while ((c = fgetc(stdin)) != EOF)
        {
            e = cipher(c, kfp);
            write(fd[1], &e, sizeof(char));
        }
    }
    fclose(kfp);
}
