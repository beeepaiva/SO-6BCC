#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define BUF_SIZE 64000 

void *descarregaBuffer();

int main() {

    //Buffer
    char *buff = (char *) malloc(BUF_SIZE);
    memset(buff, '\0', BUF_SIZE);
    setvbuf(stdout, buff, _IOFBF, BUF_SIZE);

    //Thread
    pthread_t thread1;
    pthread_create(&thread1, NULL, descarregaBuffer, NULL);


    //syscall while 1 pq n tem fim
    while(1) {
        fwrite_unlocked("*\n", 1, 3, stdout);
    }

    return(0);
}

void *descarregaBuffer() {

    while(1) {
        fflush_unlocked(stdout);
    }

    return NULL;
}