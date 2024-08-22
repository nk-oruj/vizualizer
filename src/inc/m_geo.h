#pragma once

///

#include "m_space.h"

////

#define M_GEO_PI 3.14159265
#define M_GEO_RENDER_DISTANCE 10

////

struct vec
{
    float x;
    float y;
    float z;
};

////

struct vec m_math_rotate(struct vec *res, struct vec vec, struct vec ang);

struct vec m_math_dot(float *res, struct vec a, struct vec b);

struct vec m_math_add(struct vec *res, struct vec a, struct vec b);

struct vec m_math_sub(struct vec *res, struct vec a, struct vec b);

struct vec m_math_mul(struct vec *res, struct vec vec, float fac);

struct vec m_math_lerp(struct vec *res, struct vec a, struct vec b, float val);

////

void calc_face(struct m_space space, int id, struct vec vec, struct vec nrm, struct vec ang);

void calc_edge(struct m_space space, float val, struct vec a, struct vec b, struct vec ang);

////