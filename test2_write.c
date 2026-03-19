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
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
//#define __USE_LARGEFILE64 // no need in powerflex makefile
//#include <sys/syscall.h>
//#include <linux/aio_abi.h>
//#include <linux/time.h> 
#include <libaio.h>

// gcc -g test_write.c -o test_wr -lrt -lpthread  -laio

#define MAX_INFLIGHTS 256
//#define O_DIRECT 0x4000

#if 0
static int
io_setup(unsigned n, aio_context_t* c)
{
    return syscall(__NR_io_setup, n, c);
}

static int
io_destroy(aio_context_t c)
{
    return syscall(__NR_io_destroy, c);
}

static int
io_submit(aio_context_t c, long n,  struct iocb** b)
{
    return syscall(__NR_io_submit, c, n, b);
}

static int
io_getevents(aio_context_t c, long min, long max, struct io_event* e, struct timespec* t)
{
    return syscall(__NR_io_getevents, c, min, max, e, t);
}
#endif

u_int64_t monoUsec(void)
{
    u_int64_t microsec;
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    microsec = (u_int64_t)ts.tv_sec * 1000000 +
                       ts.tv_nsec / 1000;

    return microsec;
}

io_context_t c = 0;
sem_t sendSem, completeSem;
struct iocb req[MAX_INFLIGHTS];
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
       struct io_event evt;
       struct timespec timeout;

       //sem_wait(&completeSem);
       timeout.tv_sec = 0;
       timeout.tv_nsec = 0;
       while(io_getevents(c, 1, 1, &evt, &timeout) == 0)
             ;
       struct iocb *ctx = (struct iocb*)evt.obj;

       if(ctx->u.c.nbytes != evt.res || evt.res2 !=0) {
          evt.res = -evt.res;
          printf("evt data 0x%lx, obj 0x%lx, res %ld res2 %ld, %s\n", evt.data, evt.obj, evt.res, evt.res2, strerror(evt.res));
       }
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
             printf("buf alloc failed, %s\n", strerror(errno));
             return 0;
        }

        fd = open("/dev/nvme0n1", O_RDWR | O_DIRECT);
        if(fd < 0)
        {
           printf("cannot open /dev/nvme0n1, %s\n", strerror(errno));
           return 0;
        }

        if(io_setup(inflights, &c) < 0)
        {
           printf("io_setup failed, %s\n", strerror(errno));
           free(pool_buf);
           close(fd);
           return 0;
        }

        for(i = 0; i < inflights; i++)
        {
            buf[i] = pool_buf + i * size;
            req[i].data = (void*)0xdead;
            req[i].aio_fildes = fd;
            req[i].aio_lio_opcode = IO_CMD_PWRITE;
            req[i].u.c.offset = size * i;
            req[i].u.c.buf = buf[i];
            req[i].u.c.nbytes = size;
            memset(buf[i], i+1, size);
        }

        sem_init(&sendSem, 0, inflights);
        sem_init(&completeSem, 0, 0);
        pthread_create(&t1,NULL,completion,NULL);

        for(i = 0; i < max_reqs; i++)
        {
            struct iocb* ptr_array[1];

            ptr_array[0] = &req[i % inflights];
            sem_wait(&sendSem);
            start[i % inflights] = monoUsec();
            rc = io_submit(c, 1, ptr_array);
            if(rc != 1)
            {
                printf("io_submit failed for request %llu, errno %d (%s)\n", i, errno, strerror(errno));
                return 0;
            }
            //sem_post(&completeSem);
        }

        //while(sem_getvalue(&sendSem) != inflights)
        //   sem_wait(&sendSem);

        pthread_join(t1,NULL);


        close(fd);
        free(pool_buf);
        io_destroy(c);
        printf("Average time %u usec\n", timeUsec/max_reqs);

        return 0;
}

