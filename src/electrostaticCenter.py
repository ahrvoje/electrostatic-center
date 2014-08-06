#
# electrostaticCenter.py
#
#  Created on: 29.07.2014.
#      Author: Hrvoje Abraham
#

from sys import exc_info
from math import log, exp, sqrt

def sqr(x):
    return x*x

class eLAException(Exception):
    pass

def electrostaticLambdaApprox(a, b, c):
    try:
        l = 3*log(a+b+c) - log(-a+b+c) - log(a-b+c) - log(a+b-c) + 3*log((2+sqrt(3))/3)
        return l
    except Exception as e:
        raise eLAException, eLAException(e), exc_info()[2]

class eCUVWException(Exception):
    pass

def electrostaticCenterUVW(a, b, c):
    try:
        l = electrostaticLambdaApprox(a, b, c)
        k = 2*l / (a+b+c)

        ea = exp(k*a) - 1
        eb = exp(k*b) - 1
        ec = exp(k*c) - 1

        u = a * (1 + 2/ea)
        v = b * (1 + 2/eb)
        w = c * (1 + 2/ec)

        return [u, v, w]
    except eLAException as e:
        raise eCUVWException, eCUVWException(e), exc_info()[2]

class eC2DException(Exception):
    pass

# computation of triangle electrostatic center X(5626)
# using numerically robust approximation based on the article
# "From electrostatic potentials to yet another triangle center", by Hrvoje Abraham & Vjekoslav Kovac, 2013.
# http://arxiv.org/abs/1312.3176
def electrostaticCenter2D(triangle2D):
    try:
        [[xa, ya], [xb, yb], [xc, yc]] = triangle2D

        a = sqrt(sqr(xc-xb) + sqr(yc-yb))
        b = sqrt(sqr(xa-xc) + sqr(ya-yc))
        c = sqrt(sqr(xb-xa) + sqr(yb-ya))

        [u, v, w] = electrostaticCenterUVW(a, b, c)

        ta = xa*xa + ya*ya - v*w
        tb = xb*xb + yb*yb - w*u
        tc = xc*xc + yc*yc - u*v

        x = 0.5 * (ta*(yb-yc) + tb*(yc-ya) + tc*(ya-yb)) / (xa*(yb-yc) + xb*(yc-ya) + xc*(ya-yb))
        y = 0.5 * (ta*(xb-xc) + tb*(xc-xa) + tc*(xa-xb)) / (ya*(xb-xc) + yb*(xc-xa) + yc*(xa-xb))

        return [x, y]
    except eCUVWException as e:
        raise eC2DException, eC2DException(e), exc_info()[2]

class eC3DException(Exception):
    pass

# 3D case
def electrostaticCenter3D(triangle3D):
    try:
        [[ax, ay, az], [bx, by, bz], [cx, cy, cz]] = triangle3D

        c = sqrt(sqr(bx-ax) + sqr(by-ay) + sqr(bz-az))
        rc = 1/c

        tx = (bx-ax) * rc
        ty = (by-ay) * rc
        tz = (bz-az) * rc

        x0 = (cx-ax)*tx + (cy-ay)*ty + (cz-az)*tz

        nx = cx-ax - x0*tx
        ny = cy-ay - x0*ty
        nz = cz-az - x0*tz

        y0 = sqrt(sqr(nx) + sqr(ny) + sqr(nz))
        ry0 = 1 / y0

        nx *= ry0
        ny *= ry0
        nz *= ry0

        [ect, ecn] = electrostaticCenter2D([[0, 0], [c, 0], [x0, y0]])

        x = ax + ect*tx + ecn*nx
        y = ay + ect*ty + ecn*ny
        z = az + ect*tz + ecn*nz

        return [x, y, z]
    except eC2DException as e:
        raise eC3DException, eC3DException(e), exc_info()[2]
