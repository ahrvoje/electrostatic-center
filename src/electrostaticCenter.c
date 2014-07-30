/*
 * electrostaticCenter.c
 *
 *  Created on: 11.12.2013.
 *      Author: Hrvoje Abraham
 */

#include <math.h>
#include "electrostaticCenter.h"

inline double sqr(double x)
{
    return x*x;
}

// enforce C names decoration
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int electrostaticLambdaApprox(double a, double b, double c, double *lambda)
{
    *lambda = 3*log(a+b+c) - log(-a+b+c) - log(a-b+c) - log(a+b-c) + 3*log((2+sqrt(3))/3);

    if (*lambda!=0 && !isnormal(*lambda))
        return -1;

    return 1;
}

int electrostaticCenterUVW(double a, double b, double c, double *u, double *v, double *w)
{
    double lambda, k, ea, eb, ec;

    int statusLambda = electrostaticLambdaApprox(a, b, c, &lambda);

    if (statusLambda < 0)
        return statusLambda;

    k = 2*lambda / (a+b+c);

    ea = exp(k*a) - 1;
    eb = exp(k*b) - 1;
    ec = exp(k*c) - 1;

    if (!isnormal(ea) || !isnormal(eb) || !isnormal(ec))
        return -2;

    *u = a * (1 + 2/ea);
    *v = b * (1 + 2/eb);
    *w = c * (1 + 2/ec);

    if ((*u!=0 && !isnormal(*u)) || (*v!=0 && !isnormal(*v)) || (*w!=0 && !isnormal(*w)))
        return -3;

    return 1;
}

// computation of triangle electrostatic center X(5626)
// using numerically robust approximation based on the article
// "From electrostatic potentials to yet another triangle center", by Hrvoje Abraham & Vjekoslav Kovac, 2013.
// http://arxiv.org/abs/1312.3176
int electrostaticCenterXY(double ax, double ay, double bx, double by, double cx, double cy, double *x, double *y)
{
    double a, b, c;
    double u, v, w;
    double ta, tb, tc;

    a = sqrt(sqr(cx-bx) + sqr(cy-by));
    b = sqrt(sqr(ax-cx) + sqr(ay-cy));
    c = sqrt(sqr(bx-ax) + sqr(by-ay));

    if (!isnormal(a) || !isnormal(b) || !isnormal(c))
        return -4;

    int statusUVW = electrostaticCenterUVW(a, b, c, &u, &v, &w);

    if (statusUVW < 0 )
        return statusUVW;

    ta = ax*ax + ay*ay - v*w;
    tb = bx*bx + by*by - w*u;
    tc = cx*cx + cy*cy - u*v;

    if ((ta!=0 && !isnormal(ta)) || (tb!=0 && !isnormal(tb)) || (tc!=0 && !isnormal(tc)))
        return -5;

    *x = 0.5 * (ta*(by-cy) + tb*(cy-ay) + tc*(ay-by)) / (ax*(by-cy) + bx*(cy-ay) + cx*(ay-by));
    *y = 0.5 * (ta*(bx-cx) + tb*(cx-ax) + tc*(ax-bx)) / (ay*(bx-cx) + by*(cx-ax) + cy*(ax-bx));

    if ((*x!=0 && !isnormal(*x)) || (*y!=0 && !isnormal(*y)))
        return -6;

    return 1;
}

// 3D case
int electrostaticCenterXYZ(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz, double *x, double *y, double *z)
{
    double tx, ty, tz;
    double nx, ny, nz;
    double c, rc, x0, y0, ry0, ect, ecn;

    c = sqrt(sqr(bx-ax) + sqr(by-ay) + sqr(bz-az));
    rc = 1/c;

    tx = (bx-ax) * rc;
    ty = (by-ay) * rc;
    tz = (bz-az) * rc;

    x0 = (cx-ax)*tx + (cy-ay)*ty + (cz-az)*tz;

    nx = cx-ax - x0*tx;
    ny = cy-ay - x0*ty;
    nz = cz-az - x0*tz;

    y0 = sqrt(sqr(nx) + sqr(ny) + sqr(nz));

    // c OR y0 must not be 0
    if (!isnormal(c) || (x0!=0 && !isnormal(x0)) || !isnormal(y0))
        return -7;

    int statusXY = electrostaticCenterXY(0, 0, c, 0, x0, y0, &ect, &ecn);

    if (statusXY < 0)
        return statusXY;

    ry0 = 1/y0;

    nx *= ry0;
    ny *= ry0;
    nz *= ry0;

    *x = ax + ect*tx + ecn*nx;
    *y = ay + ect*ty + ecn*ny;
    *z = az + ect*tz + ecn*nz;

    if ((*x!=0 && !isnormal(*x)) || (*y!=0 && !isnormal(*y)) || (*z!=0 && !isnormal(*z)))
        return -8;

    return 1;
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
