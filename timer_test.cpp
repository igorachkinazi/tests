#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <sys/times.h>
#include <syscall.h>
#include <thread>
#include <chrono>
#include <unistd.h>


struct TR_TimerReq;
typedef void (*TR_TimerCK)(TR_TimerReq* pCkParam);

struct TR_TimerReq
{
    uint64_t state;
    void *timer;
};

#define TR_TIMER__ACTIVE      1
#define TR_TIMER__IDLE        2
#define TR_TIMER__DESTROY     3

class LinuxTimer {
    TR_TimerReq* m_pReq = nullptr;
    TR_TimerCK m_pCK = nullptr;
    bool m_running = false;
    std::thread m_thread;
public:
    LinuxTimer(TR_TimerReq* pReq, TR_TimerCK pCK) { m_pReq = pReq; m_pCK = pCK; }
    virtual ~LinuxTimer() {
        m_thread.~thread();
    }
    void start(uint32_t millisToSleep) {
        m_running = true;
        m_thread = std::thread([this, millisToSleep](){
            std::this_thread::sleep_for(std::chrono::milliseconds(millisToSleep));
            if (m_running) {
                m_pCK(m_pReq);
            }
        });
        m_thread.detach();
    }
    void stop() {
        m_running = false;
    }
};


void  TR_TimerReq_Init(TR_TimerReq* pReq, TR_TimerCK pCK)
{
    pReq->state = TR_TIMER__IDLE;
    pReq->timer = new LinuxTimer(pReq, pCK);
}

uint32_t TR_TimerReq_Add(TR_TimerReq* pReq, uint32_t millisToSleep)
{
    ((LinuxTimer*)pReq->timer)->start(millisToSleep);
    pReq->state = TR_TIMER__ACTIVE;
    return 0;
}

uint32_t TR_TimerReq_Abort(TR_TimerReq* pReq)
{
    ((LinuxTimer*)pReq->timer)->stop();
    pReq->state = TR_TIMER__IDLE;
    return 0;
}

void  TR_TimerReq_Destroy(TR_TimerReq* pReq)
{
    delete (LinuxTimer*)pReq->timer;
    pReq->state = TR_TIMER__DESTROY;
}

void timercallback(TR_TimerReq* pReq)
{
    printf("%s is called\n", __func__);
    TR_TimerReq_Add(pReq, 300);
}

int main()
{
    TR_TimerReq treq;
    TR_TimerReq_Init(&treq, timercallback);
    TR_TimerReq_Add(&treq, 400);
    sleep(1);
    printf("%s waited 1 sec, timer state %u\n", __func__, treq.state);
    sleep(1);
    printf("%s waited 2 sec, timer state %u\n", __func__, treq.state);
    TR_TimerReq_Abort(&treq);
    sleep(1);
    printf("%s waited 3 sec, timer state %u\n", __func__, treq.state);
    TR_TimerReq_Destroy(&treq);
    return 0;
}

