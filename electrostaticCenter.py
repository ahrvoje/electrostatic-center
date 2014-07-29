__author__ = 'Hrvoje Abraham, ahrvoje@gmail.com, 2014'

from math import log, exp, sqrt

def sqr(x):
    return x*x

def electrostaticCenterUVW(a, b, c):
    try:
        k = 2 * (3*log(a+b+c) - log(-a+b+c) - log(a-b+c) - log(a+b-c) + 3*log((2+sqrt(3))/3)) / (a+b+c);

        ea = exp(k*a) - 1;
        eb = exp(k*b) - 1;
        ec = exp(k*c) - 1;

        u = a * (1 + 2/ea);
        v = b * (1 + 2/eb);
        w = c * (1 + 2/ec);

        return [u, v, w]
    except:
        return [0, 0, 0]

# computation of triangle electrostatic center X(5626)
# using numerically robust approximation based on the article
# "From electrostatic potentials to yet another triangle center", by Hrvoje Abraham & Vjekoslav Kovac, 2013.
# http://arxiv.org/abs/1312.3176
def electrostaticCenterXY(triangle):
    try:
        [[xa, ya], [xb, yb], [xc, yc]] = triangle

        a = sqrt(sqr(xc-xb) + sqr(yc-yb));
        b = sqrt(sqr(xa-xc) + sqr(ya-yc));
        c = sqrt(sqr(xb-xa) + sqr(yb-ya));

        [u, v, w] = electrostaticCenterUVW(a, b, c);

        ta = xa*xa + ya*ya - v*w;
        tb = xb*xb + yb*yb - w*u;
        tc = xc*xc + yc*yc - u*v;

        x = 0.5 * (ta*(yb-yc) + tb*(yc-ya) + tc*(ya-yb)) / (xa*(yb-yc) + xb*(yc-ya) + xc*(ya-yb));
        y = 0.5 * (ta*(xb-xc) + tb*(xc-xa) + tc*(xa-xb)) / (ya*(xb-xc) + yb*(xc-xa) + yc*(xa-xb));

        return [x, y]
    except:
        raise NameError('electrostaticCenterXY numerical error')

# 3D case
def electrostaticCenterXYZ(triangle):
    try:
        [[ax, ay, az], [bx, by, bz], [cx, cy, cz]] = triangle

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

        [ect, ecn] = electrostaticCenterXY([[0, 0], [c, 0], [x0, y0]])

        x = ax + ect*tx + ecn*nx;
        y = ay + ect*ty + ecn*ny;
        z = az + ect*tz + ecn*nz;

        return [x, y, z]
    except:
        raise NameError('electrostaticCenterXYZ numerical error')
