#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

static void
create_thread(pthread_t *thread, void *(*start_routine) (void *), void *arg) {
    if (pthread_create(thread,NULL, start_routine, arg)) {
        fprintf(stderr, "Create thread failed");
        exit(1);
    }
}

static void *
_timer(void *p) {
    server_timer_init();
    for (;;) {
        server_timer_updatetime();
        usleep(2500);
    }
    return NULL;
}

int
main(int argc, char *argv[]) {
    pthread_t pid;
    create_thread(&pid, _timer, "_timer");
    sleep(1);
    server_timer_timeout(1, 20, 1001);
    server_timer_timeout(2, 40, 1002);
    server_timer_timeout(3, 60, 1003);
    server_timer_timeout(4, 80, 1004);
    server_timer_timeout(5, 100, 1005);
    for (;;) {
        sleep(1);
    }
    return 0;
}