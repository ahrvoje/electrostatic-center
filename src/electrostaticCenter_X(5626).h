/*
 * electrostaticCenter_X(5626).h
 *
 *  Created on: 11.12.2013.
 *      Author: Hrvoje Abraham
 */

#ifndef ELECTROCENTER_H_
#define ELECTROCENTER_H_

#include <math.h>

inline double sqr(double x)
{
    return x*x;
}

int triangleCenterUVW(double a, double b, double c, double& u, double& v, double& w)
{
    if (!isnormal(a+b+c) || !isnormal(-a+b+c) || !isnormal(a-b+c) || !isnormal(a+b-c))
        return -1;

    double k, ea, eb, ec;

    k = 2 * (3*log(a+b+c) - log(-a+b+c) - log(a-b+c) - log(a+b-c) + 3*log((2+sqrt(3))/3)) / (a+b+c);

    ea = exp(k*a) - 1;
    eb = exp(k*b) - 1;
    ec = exp(k*c) - 1;

    if (!isnormal(ea) || !isnormal(eb) || !isnormal(ec))
        return -2;

    u = a * (1 + 2/ea);
    v = b * (1 + 2/eb);
    w = c * (1 + 2/ec);

    if ((u!=0 && !isnormal(u)) || (v!=0 && !isnormal(v)) || (w!=0 && !isnormal(w)))
        return -3;

    return 1;
}

// computation of triangle electrostatic center X(5626)
// using numerically robust approximation based on the article
// "From electrostatic potentials to yet another triangle center", by Hrvoje Abraham & Vjekoslav Kovac, 2013.
// http://arxiv.org/abs/1312.3176
int electrostaticCenterXY(double xa, double ya, double xb, double yb, double xc, double yc, double& x, double& y)
{
    double a, b, c;
    double u, v, w;
    double ta, tb, tc;

    a = sqrt(sqr(xc-xb) + sqr(yc-yb));
    b = sqrt(sqr(xa-xc) + sqr(ya-yc));
    c = sqrt(sqr(xb-xa) + sqr(yb-ya));

    if (!isnormal(a) || !isnormal(b) || !isnormal(c))
        return -4;

    int statusUVW = triangleCenterUVW(a, b, c, u, v, w);

    if (statusUVW < 0 )
        return statusUVW;

    ta = xa*xa + ya*ya - v*w;
    tb = xb*xb + yb*yb - w*u;
    tc = xc*xc + yc*yc - u*v;

    if ((ta!=0 && !isnormal(ta)) || (tb!=0 && !isnormal(tb)) || (tc!=0 && !isnormal(tc)))
        return -5;

    x = 0.5 * (ta*(yb-yc) + tb*(yc-ya) + tc*(ya-yb)) / (xa*(yb-yc) + xb*(yc-ya) + xc*(ya-yb));
    y = 0.5 * (ta*(xb-xc) + tb*(xc-xa) + tc*(xa-xb)) / (ya*(xb-xc) + yb*(xc-xa) + yc*(xa-xb));

    if ((x!=0 && !isnormal(x)) || (y!=0 && !isnormal(y)))
        return -6;

    return 1;
}

// 3D case
int electrostaticCenterXYZ(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz, double& x, double& y, double& z)
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
    ry0 = 1 / y0;

    nx *= ry0;
    ny *= ry0;
    nz *= ry0;

    int statusXY = electrostaticCenterXY(0, 0, c, 0, x0, y0, ect, ecn);

    if (statusXY < 0)
        return statusXY;

    x = ax + ect*tx + ecn*nx;
    y = ay + ect*ty + ecn*ny;
    z = az + ect*tz + ecn*nz;

    if ((x!=0 && !isnormal(x)) || (y!=0 && !isnormal(y)) || (z!=0 && !isnormal(z)))
        return -7;

    return 1;
}

#endif /* ELECTROCENTER_H_ */
