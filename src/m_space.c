////

#include "inc/m_space.h"

////

#ifdef __unix__

#include "sys/ioctl.h"
#include "unistd.h"

#elif defined(_WIN32) || defined(WIN32)

#include "windows.h"

#endif

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"

////

void m_space_set(struct m_space *s)
{
    int col, row;

#ifdef __unix__

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    col = w.ws_col;
    row = w.ws_row;

#elif defined(_WIN32) || defined(WIN32)

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

#endif

    s->width = col;
    s->height = row;

    int size = col * row;

    if (s->size == size)
    {
        memset(s->buffer, 32, s->size);
        return;
    }

    s->size = col * row;

    if (s->buffer != NULL)
    {
        free(s->buffer);
    }

    s->buffer = (char *)malloc(s->size);
    memset(s->buffer, 32, s->size);
}

void m_space_write(struct m_space *s, int left, int line, char *str, ...)
{
    va_list argList;
    char *res = (char *)malloc(s->width);

    va_start(argList, str);
    vsprintf(res, str, argList);
    va_end(argList);

    int size = strlen(res);
    int iter = size;

    if (line > s->height)
    {
        free(res);
        return;
    }

    if (size > s->width)
    {
        free(res);
        return;
    }

    while (iter-- > 0)
    {
        s->buffer[s->width * line + iter + (s->width - size) * left] = *(res + iter);
    }

    free(res);
}

////

void frame_space_header(struct m_space *s)
{
    m_space_set(s);
}

void frame_space_footer(struct m_space *s)
{
    printf("\x1b[H\x1b[2J%.*s", s->size, s->buffer);
}

////
