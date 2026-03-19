#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#include <fcntl.h>
#include <unistd.h>
//#define __USE_LARGEFILE64 // no need in powerflex makefile
#include <aio.h>

// gcc -g test_write.c -o test_wr -lrt -lpthread 

#define MAX_INFLIGHTS 256
//#define O_DIRECT 0x4000

u_int64_t monoUsec(void)
{
    u_int64_t microsec;
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    microsec = (u_int64_t)ts.tv_sec * 1000000 +
                       ts.tv_nsec / 1000;

    return microsec;
}

sem_t sendSem, completeSem;
struct aiocb64 req[MAX_INFLIGHTS];
u_int64_t start[MAX_INFLIGHTS];
u_int16_t max_reqs = 0;
u_int16_t inflights = 0;
u_int64_t timeUsec = 0;

void *completion(void *arg)
{
    u_int64_t i = 0;
    (void)arg;

    for(i = 0; i < max_reqs; i++)
    {
       int errRet, rc;

       sem_wait(&completeSem);
       while((errRet = aio_error64(&req[i % inflights])) == EINPROGRESS)
          ;

      rc = aio_return64(&req[i % inflights]);

      if(rc < 0)
         printf("Async write %u failed, aio_return %d (%s), aio_error %d (%s)\n",
                  i, rc, strerror(errno), errRet, strerror(errRet) );

      timeUsec += monoUsec() - start[i % inflights];
      sem_post(&sendSem);
    }
}

int main( int argc, char *argv[] )
{
        int fd;
        int rc;
        int size = 1024*1024;
        unsigned char *buf[MAX_INFLIGHTS];
        unsigned char *pool_buf;
        u_int64_t i;
        pthread_t t1;

        if(argc < 2)
        {
            printf("Give me inflights and max size(in MB)\n");
            return 0;
        }

        inflights = atoi(argv[1]);
        max_reqs = atoi(argv[2]);
        timeUsec = 0;

        memset(req, 0, sizeof(req));

        pool_buf = aligned_alloc(4*1024, size * inflights);
        if(pool_buf == NULL)
        {
             printf("buf alloc failed\n");
             return 0;
        }

        fd = open("/dev/nvme0n1", O_RDWR | O_DIRECT);
        if(fd < 0)
        {
           printf("cannot open /dev/nvme0n1, %s\n", strerror(errno));
           return 0;
        }

        for(i = 0; i < inflights; i++)
        {
            buf[i] = pool_buf + i * size;
            req[i].aio_fildes = fd;
            req[i].aio_offset = size * i;
            req[i].aio_buf = buf[i];
            req[i].aio_nbytes = size;
            memset(buf[i], i+1, size);
        }

        sem_init(&sendSem, 0, inflights);
        sem_init(&completeSem, 0, 0);
        pthread_create(&t1,NULL,completion,NULL);

        for(i = 0; i < max_reqs; i++)
        {
            sem_wait(&sendSem);
            start[i % inflights] = monoUsec();
            rc = aio_write64(&req[i % inflights]);
            if(rc)
            {
                printf("aio_write64 failed for request %llu, errno %d\n", i, errno);
                return 0;
            }
            sem_post(&completeSem);
        }

        //while(sem_getvalue(&sendSem) != inflights)
        //   sem_wait(&sendSem);

        pthread_join(t1,NULL);


        close(fd);
        printf("Average time %u usec\n", timeUsec/max_reqs);

        return 0;
}

