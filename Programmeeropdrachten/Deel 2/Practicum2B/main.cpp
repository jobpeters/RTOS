
#include <unistd.h>
#include <cstdlib>
//#include <cstudio>
#include <pthread.h>
#include <iostream>

int fd[2];

void *reader(void *threadid) {
    while (1) {
        int ch;
        int result;

        result = read(fd[0], &ch, sizeof(ch));

        printf("Reader result: %i\n", result);
        if( result != 4) {
            perror("read");
            exit(3);
        }
        printf("Reader: %i\n", ch);
    }
}

void *writer(void *threadid) {
    int ch = 105;
    int result;
    while (1) {
        result = write(fd[1], &ch, sizeof(ch));
        printf("Writer result: %i\n", result);
        if( result == 1) {
            perror("write");
            exit(2);
        }
        printf("Writer: %i\n", ch);
        ch++;
    }
}



int main() {
    pthread_t reader_tid, writer_tid;
    int result;
    pthread_attr_t tattr;
//    int t1, t2;

    pthread_attr_init(&tattr);

    result = pipe(fd);
    if (result < 0) {
        perror("pipe");
        exit(1);
    }

    int reader_thread = pthread_create(&reader_tid, &tattr, reader, nullptr);
    int writer_thread = pthread_create(&writer_tid, &tattr, writer, nullptr);

    pthread_join(reader_tid, NULL);
    pthread_join(writer_tid, NULL);
    return 0;
}