#include "inc/m_time.h"

////

void m_sleep(float s)
{
    s = s > 0 ? s : 0;

    struct timespec ts;
    ts.tv_sec = (int)s;
    ts.tv_nsec = (int)((s - ts.tv_sec) * 1e+9);
    nanosleep(&ts, NULL);
}

////

void m_time_init(struct m_time *t)
{
    clock_gettime(CLOCK_REALTIME, &t->init);
    t->prv = 0;
    t->now = 0;
    t->dlt = 0;
}

float m_time_cont(struct m_time t)
{
    struct timespec c;
    clock_gettime(CLOCK_REALTIME, &c);
    return (c.tv_sec - t.init.tv_sec) + (c.tv_nsec - t.init.tv_nsec) / (float)(1e+9);
}

////

void frame_time_header(struct m_time *t)
{
    t->now = m_time_cont(*t);
    t->dlt = t->now - t->prv;
}

void frame_time_footer(struct m_time *t)
{
    m_sleep(M_TIME_DLT_TARGET + t->now - m_time_cont(*t));
    t->prv = t->now;
}

////