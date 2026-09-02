#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/demo_queue"

int main()
{
    mqd_t mq;
    char message[] = "Hello Message Queues!";

    struct mq_attr attr = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_msgsize = 100,
        .mq_curmsgs = 0
    };

    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
        perror("mq_send");
        return 1;
    }

    printf("Message Sent: %s\n", message);

    mq_close(mq);

    return 0;
}
