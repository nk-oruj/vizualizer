////

#include "stdlib.h"
#include "stdio.h"

////

#include "inc/m_space.h"
#include "inc/m_time.h"
#include "inc/m_geo.h"

////

struct m_space _space;
struct m_time _time;

////

struct vec rot_angles;

////

int main()
{
    {
        m_time_init(&_time);

        ////

        rot_angles.x = 0;
        rot_angles.y = 0;
        rot_angles.z = 0;
    }

    while (1)
    {
        frame_space_header(&_space);
        frame_time_header(&_time);

        ////

        for (float i = -1; i < 1; i += 0.04)
        {
            for (float j = -1; j < 1; j += 0.04)
            {
                calc_face(_space, 0, (struct vec){+i, +j, -1}, (struct vec){0, 0, -1}, rot_angles);
                calc_face(_space, 1, (struct vec){+1, +j, +i}, (struct vec){+1, 0, 0}, rot_angles);
                calc_face(_space, 2, (struct vec){-1, +j, -i}, (struct vec){-1, 0, 0}, rot_angles);
                calc_face(_space, 3, (struct vec){-i, +j, +1}, (struct vec){0, 0, +1}, rot_angles);
                calc_face(_space, 4, (struct vec){+i, -1, -j}, (struct vec){0, -1, 0}, rot_angles);
                calc_face(_space, 5, (struct vec){+i, +1, +j}, (struct vec){0, +1, 0}, rot_angles);
            }
        }

        for (float i = 0; i < 1; i += 0.04)
        {
            // calc_edge(_space, i, (struct vec){+1, +1, +1}, (struct vec){+1, +1, -1}, rot_angles);
            // calc_edge(_space, i, (struct vec){+1, -1, +1}, (struct vec){+1, -1, -1}, rot_angles);
            // calc_edge(_space, i, (struct vec){-1, +1, +1}, (struct vec){-1, +1, -1}, rot_angles);
            // calc_edge(_space, i, (struct vec){-1, -1, +1}, (struct vec){-1, -1, -1}, rot_angles);

            // calc_edge(_space, i, (struct vec){+1, +1, +1}, (struct vec){+1, -1, +1}, rot_angles);
            // calc_edge(_space, i, (struct vec){+1, +1, -1}, (struct vec){+1, -1, -1}, rot_angles);
            // calc_edge(_space, i, (struct vec){-1, +1, +1}, (struct vec){-1, -1, +1}, rot_angles);
            // calc_edge(_space, i, (struct vec){-1, +1, -1}, (struct vec){-1, -1, -1}, rot_angles);

            // calc_edge(_space, i, (struct vec){+1, +1, +1}, (struct vec){-1, +1, +1}, rot_angles);
            // calc_edge(_space, i, (struct vec){+1, +1, -1}, (struct vec){-1, +1, -1}, rot_angles);
            // calc_edge(_space, i, (struct vec){+1, -1, +1}, (struct vec){-1, -1, +1}, rot_angles);
            // calc_edge(_space, i, (struct vec){+1, -1, -1}, (struct vec){-1, -1, -1}, rot_angles);
        }

        m_space_write(&_space, 1, _space.height - 1, "Vizualizer.EXE | time: %f delta: %f width: %d height: %d  ", _time.now, _time.dlt, _space.width, _space.height);

        rot_angles.x += 0.06f * _time.dlt / M_TIME_DLT_TARGET;
        rot_angles.y += 0.06f * _time.dlt / M_TIME_DLT_TARGET;
        rot_angles.z += 0.02f * _time.dlt / M_TIME_DLT_TARGET;

        m_space_write(&_space, 0, 0, "alpha: %f betta: %f gamma: %f", rot_angles.x, rot_angles.y, rot_angles.z);

        m_space_write(&_space, 0, 3, "borders:  %c", "|/-\\|/-\\"[(int)(_time.now * 10) % 8]);

        ////

        frame_space_footer(&_space);
        frame_time_footer(&_time);
    }

    return 0;
}

////
