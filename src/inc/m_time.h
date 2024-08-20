#pragma once

////

#include "time.h"

////

#define M_TIME_DLT_TARGET 0.04f

////

void m_sleep(float s);

////

struct m_time
{
    struct timespec init;
    float prv;
    float now;
    float dlt;
};

////

void m_time_init(struct m_time *t);

float m_time_cont(struct m_time t);

////

void frame_time_header(struct m_time *t);

void frame_time_footer(struct m_time *t);

////