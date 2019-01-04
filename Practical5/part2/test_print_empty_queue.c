#include "msg_queue.h"

int main()
{
    MQueue* s = malloc(sizeof(MQueue));
    if (s == NULL)
    {
        perror("Error: malloc failed");
        exit(EXIT_FAILURE);
    }
    initMQueue(s);

    printMQueue(s);

    return 0;
}