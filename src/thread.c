#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "thread.h"

/* Background monitoring thread */
static void *monitor_thread(void *arg)
{
    (void)arg;

    while (1)
    {
        printf("[Monitor] Shell Based Database Manager is running...\n");
        fflush(stdout);

        sleep(10);
    }

    return NULL;
}

/* Start monitoring thread */
void start_monitor_thread(void)
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, monitor_thread, NULL) != 0)
    {
        perror("pthread_create");
        return;
    }

    pthread_detach(thread);
}
