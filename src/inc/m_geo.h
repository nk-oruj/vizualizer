#pragma once

///

#include "m_space.h"

////

#define M_GEO_PI 3.14159265
#define M_GEO_RENDER_DISTANCE 10

////

struct vec3
{
    float x;
    float y;
    float z;
};

////

struct vec3 m_math_rotate(struct vec3 *res, struct vec3 vec, struct vec3 ang);

struct vec3 m_math_dot(float *res, struct vec3 a, struct vec3 b);

struct vec3 m_math_add(struct vec3 *res, struct vec3 a, struct vec3 b);

struct vec3 m_math_sub(struct vec3 *res, struct vec3 a, struct vec3 b);

struct vec3 m_math_mul(struct vec3 *res, struct vec3 vec, float fac);

struct vec3 m_math_lerp(struct vec3 *res, struct vec3 a, struct vec3 b, float val);

////

void calc_face(struct m_space space, int id, struct vec3 vec, struct vec3 nrm, struct vec3 ang);

void calc_edge(struct m_space space, float val, struct vec3 a, struct vec3 b, struct vec3 ang);

////