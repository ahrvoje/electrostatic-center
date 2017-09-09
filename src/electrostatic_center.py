#
#  electrostatic_center.py
#
#  Created on: 29.07.2014.
#      Author: Hrvoje Abraham
#

from math import log, exp, sqrt, hypot


def x5626_lambda_approx(a, b, c):
    return 3 * log(a + b + c) - log(-a + b + c) - log(a - b + c) - log(a + b - c) + 3 * log((2 + sqrt(3)) / 3)


def electrostatic_center_uvw(a, b, c):
    k = 2 * x5626_lambda_approx(a, b, c) / (a + b + c)

    ea = exp(k * a) - 1
    eb = exp(k * b) - 1
    ec = exp(k * c) - 1

    u = a * (1 + 2 / ea)
    v = b * (1 + 2 / eb)
    w = c * (1 + 2 / ec)

    return u, v, w


def electrostatic_center_2d(triangle_2d):
    """
    Computation of the triangle electrostatic center X(5626)
    using numerically robust approximation based on the article
    "From electrostatic potentials to yet another triangle center", by Hrvoje Abraham & Vjekoslav Kovac, 2013.
    http://arxiv.org/abs/1312.3176

    :param triangle_2d: three 2D tuples containing triangle coordinates
    :return: electrostatic center coordinates tuple
    """
    (xa, ya), (xb, yb), (xc, yc) = triangle_2d

    a = hypot(xc - xb, yc - yb)
    b = hypot(xa - xc, ya - yc)
    c = hypot(xb - xa, yb - ya)

    u, v, w = electrostatic_center_uvw(a, b, c)

    ta = xa * xa + ya * ya - v * w
    tb = xb * xb + yb * yb - w * u
    tc = xc * xc + yc * yc - u * v

    x = 0.5 * (ta * (yb - yc) + tb * (yc - ya) + tc * (ya - yb)) / (xa * (yb - yc) + xb * (yc - ya) + xc * (ya - yb))
    y = 0.5 * (ta * (xb - xc) + tb * (xc - xa) + tc * (xa - xb)) / (ya * (xb - xc) + yb * (xc - xa) + yc * (xa - xb))

    return x, y


def electrostatic_center_3d(triangle_3d):
    (ax, ay, az), (bx, by, bz), (cx, cy, cz) = triangle_3d

    dx, dy, dz = bx - ax, by - ay, bz - az
    c = sqrt(dx*dx + dy*dy + dz*dz)

    tx = (bx - ax) / c
    ty = (by - ay) / c
    tz = (bz - az) / c

    x0 = (cx - ax) * tx + (cy - ay) * ty + (cz - az) * tz

    nx = cx - ax - x0 * tx
    ny = cy - ay - x0 * ty
    nz = cz - az - x0 * tz

    y0 = sqrt(nx*nx + ny*ny + nz*nz)

    nx /= y0
    ny /= y0
    nz /= y0

    ect, ecn = electrostatic_center_2d(((0, 0), (c, 0), (x0, y0)))

    x = ax + ect * tx + ecn * nx
    y = ay + ect * ty + ecn * ny
    z = az + ect * tz + ecn * nz

    return x, y, z
