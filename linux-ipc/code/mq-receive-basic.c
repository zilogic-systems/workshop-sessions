#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME "/demo_queue"

int main()
{
    mqd_t mq;
    char buffer[100];

    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    if (mq_receive(mq, buffer, sizeof(buffer), NULL) == -1) {
        perror("mq_receive");
        return 1;
    }

    printf("Message Received: %s\n", buffer);

    mq_close(mq);

    // Remove the queue after use
    mq_unlink(QUEUE_NAME);

    return 0;
}
