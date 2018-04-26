#include "process2.h"

/**
 * Method which prints or exports the contents of the pipe to a file or stdout
 */
void pexport(char* OUT_PATH, int* fd)
{
    char enc = EOF;
    close(fd[1]);

    //print to stdout
    if (OUT_PATH == NULL)
    {
        while (read(fd[0], &enc, sizeof(char)) > 0)
        {
            fprintf(stdout, "%c", enc);
        }
    }
    
    //export to file
    else
    {
        FILE* ofp = fopen(OUT_PATH, "a");
        while (read(fd[0], &enc, sizeof(char)) > 0)
        {
            fprintf(ofp, "%c", enc);
        }
        fclose(ofp);
    }
}
