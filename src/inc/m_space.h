#pragma once

////

struct m_space
{
    char *buffer;
    int size;
    int width;
    int height;
};

////

void m_space_set(struct m_space *s);

void m_space_write(struct m_space *s, int left, int line, char *str, ...);

////

void frame_space_header(struct m_space *s);

void frame_space_footer(struct m_space *s);

////