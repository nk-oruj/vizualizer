////

#include "inc/m_geo.h"

////

#include "math.h"

////

struct vec3 m_math_rotate(struct vec3 *res, struct vec3 vec, struct vec3 ang)
{
    float sin_a = sin(ang.x);
    float cos_a = cos(ang.x);

    float sin_b = sin(ang.y);
    float cos_b = cos(ang.y);

    float sin_c = sin(ang.z);
    float cos_c = cos(ang.z);

    res->x = vec.y * sin_a * sin_b * cos_c - vec.z * cos_a * sin_b * cos_c + vec.y * cos_a * sin_c + vec.z * sin_a * sin_c + vec.x * cos_b * cos_c;
    res->y = vec.y * cos_a * cos_c + vec.z * sin_a * cos_c - vec.y * sin_a * sin_b * sin_c + vec.z * cos_a * sin_b * sin_c - vec.x * cos_b * sin_c;
    res->z = vec.z * cos_a * cos_b - vec.y * sin_a * cos_b + vec.x * sin_b;
}

struct vec3 m_math_dot(float *res, struct vec3 a, struct vec3 b)
{
    *res = a.x * b.x + a.y * b.y + a.z * b.z;
}

struct vec3 m_math_add(struct vec3 *res, struct vec3 a, struct vec3 b)
{
    res->x = a.x + b.x;
    res->y = a.y + b.y;
    res->z = a.z + b.z;
}

struct vec3 m_math_sub(struct vec3 *res, struct vec3 a, struct vec3 b)
{
    res->x = a.x - b.x;
    res->y = a.y - b.y;
    res->z = a.z - b.z;
}

struct vec3 m_math_mul(struct vec3 *res, struct vec3 vec, float fac)
{
    res->x = fac * vec.x;
    res->y = fac * vec.y;
    res->z = fac * vec.z;
}

struct vec3 m_math_lerp(struct vec3 *res, struct vec3 a, struct vec3 b, float val)
{
    struct vec3 k, l;

    m_math_sub(&k, b, a);
    m_math_mul(&l, k, val);
    m_math_add(res, l, a);
}

////

void calc_face(struct m_space space, int id, struct vec3 vec, struct vec3 nrm, struct vec3 ang)
{

    ////

    struct vec3 rnrm;
    m_math_rotate(&rnrm, nrm, ang);

    float lum;
    m_math_dot(&lum, (struct vec3){0, 0, -1}, rnrm);

    m_space_write(&space, 0, (5 + id), "lum %d: %f", id, lum);

    char ascii[] = " .'`^\",:;Il!i><~+_-?][}{1)(tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    char vf = ascii[(lum > 0) ? (int)(lum * (sizeof ascii - 1)) : 0];

    if (vf == ' ')
    {
        return;
    }

    ////

    struct vec3 rvec;
    m_math_rotate(&rvec, vec, ang);

    rvec.z += M_GEO_RENDER_DISTANCE;

    int k = 2 * ((space.width < space.height) ? space.width : space.height);

    int xp = (int)(space.width / 2 + k * 2 * rvec.x / rvec.z);
    int yp = (int)(space.height / 2 + k * rvec.y / rvec.z);

    int idx = xp + yp * space.width;

    if (idx < 0 || idx >= space.size)
    {
        return;
    }

    ////

    space.buffer[idx] = vf;

    ////
}

void calc_edge(struct m_space space, float val, struct vec3 a, struct vec3 b, struct vec3 ang)
{

    ////

    struct vec3 d;
    m_math_sub(&d, a, b);

    struct vec3 n1 = (d.x != 0) ? (struct vec3){0, 0, 0} : (struct vec3){a.x, 0, 0};
    struct vec3 n2 = (d.y != 0) ? (struct vec3){0, 0, 0} : (struct vec3){0, a.y, 0};
    struct vec3 n3 = (d.z != 0) ? (struct vec3){0, 0, 0} : (struct vec3){0, 0, a.z};

    m_math_rotate(&n1, n1, ang);
    m_math_rotate(&n2, n2, ang);
    m_math_rotate(&n3, n3, ang);

    float dn1;
    m_math_dot(&dn1, (struct vec3){0, 0, -1}, n1);

    float dn2;
    m_math_dot(&dn2, (struct vec3){0, 0, -1}, n2);

    float dn3;
    m_math_dot(&dn3, (struct vec3){0, 0, -1}, n3);

    if (dn1 <= 0 && dn2 <= 0 && dn3 <= 0)
    {
        return;
    }

    ////

    struct vec3 rp;
    m_math_lerp(&rp, a, b, val);
    m_math_rotate(&rp, rp, ang);

    rp.z += 10;

    int k = 2 * ((space.width < space.height) ? space.width : space.height);

    int xp = (int)(space.width / 2 + k * 2 * rp.x / rp.z);
    int yp = (int)(space.height / 2 + k * rp.y / rp.z);

    int idx = xp + yp * space.width;

    if (idx < 0 || idx > space.size)
    {
        return;
    }

    ////

    m_math_rotate(&d, d, ang);

    d.z = 0;

    float da1;
    m_math_dot(&da1, (struct vec3){1, 0, 0}, d);

    float da2;
    m_math_dot(&da2, (struct vec3){0, 1, 0}, d);

    float v1 = 4 * atan(-da1 / da2) / M_GEO_PI;
    float v2 = ((v1 < 0) ? 4 + v1 : v1) + .5;
    char vf = "|/=\\"[(int)((v2 > 4) ? v2 - 4 : v2)];

    ////

    space.buffer[idx] = vf;

    ////
}

////