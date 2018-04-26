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

    send_msg(s, 1);
    send_msg(s, 2);
    send_msg(s, 3);
    send_msg(s, 4);
    send_msg(s, 5);

    printMQueue(s);

    return 0;
}