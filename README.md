Center of electrostatic potential X(5626)
=========================================

It is the point of maximal electrostatic potential inside a triangle having a homogeneous surface charge distribution. It's also a point of zero electric field of the same charge distribution, and happens to satisfy the mathematical definition of triangle center. A lot of technical details can be found in the article *'From electrostatic potentials to yet another triangle center'* by Hrvoje Abraham and Vjekoslav Kovac. (http://arxiv.org/pdf/1312.3176v2.pdf)

Center is also listed in Kimberling's Encyclopedia of triangle centers under *X(5626) = CENTER OF ELECTROSTATIC POTENTIAL.* (http://faculty.evansville.edu/ck6/encyclopedia/ETCPart4.html)

This repository containes a few routines for numerical calculation of X(5626). Routines are mainly written in Wolfram Mathematica, but practical approximation is also implemented in C and Python.

Wolfram Mathematica
-------------------

Prototypes and examples for Mathematica functions available in __ElectrostaticCenter_X(5626).nb__

### Functions

```
FindElectrostaticLambda[{{xa_,ya_},{xb_,yb_},{xc_,yc_}}]
```

Finds numerical value of *lambda* parameter of triangle electrostatic center X(5626) based on the Cartesian coordinates of triangle vertices. Default value of *Precision* option is 12 decimal places.

```
ElectrostaticLine[{{xa_,ya_},{xb_,yb_},{xc_,yc_}}, lambda_]
```

Computes a point on electrostatic line of the triangle based on the Cartesian coordinates of triangle vertices and *lambda* parameter. Returns electrostatic center X(5626) if its *lambda* is used.

```
FindElectrostaticCenter[{{xa_,ya_},{xb_,yb_},{xc_,yc_}}]
```

Returns electrostatic center X(5626) of triangle defined with Cartesian coordinates of its vertices. Default value of *Precision* option is 12 decimal places.

### Examples

![alt tag](https://raw.githubusercontent.com/ahrvoje/electrostatic-center/master/ElectrostaticCenter_MathematicaExamples.png)

C
-

Prototypes and examples for C functions available in __electrostaticCenter_X(5626).h__. These functions use approximative estimation of *lambda* parameter and is implemented in a way which reduces the probability of numerical overflow or underflow. Approximation is described in section 6 of the article mentioned in the header of this document.

### Functions

```
int electrostaticCenterXY(double xa, double ya, double xb, double yb, double xc, double yc, double& x, double& y)
```

Computes coordinates of electrostatic center based on Cartesian coordinates of triangle vertices. Result is returned in variables *x*, *y* by reference.

```
int electrostaticCenterXYZ(double ax, double ay, double az, double bx, double by, double bz,
                           double cx, double cy, double cz, double& x, double& y, double& z)

```

3D version of function for computation of triangle electrostatic center. Result is returned in variables *x*, *y*, *z* by reference.

### Examples

```C
#include <stdio.h>
#include "..\electrostaticCenter_X(5626).h"

int main(void)
{
    double cx, cy, cz;

    // compute electrostatic center for triangle ABC
    // A(-1,0), B(2,0), C(0,2)
    electrostaticCenterXY(-1, 0, 2, 0, 0, 2, cx, cy);
    printf("electrostatic center (x, y) = (%lf, %lf)\n", cx, cy);

    // compute electrostatic center for triangle ABC
    // A(-1,0,1), B(2,0,2), C(0,2,3)
    electrostaticCenterXYZ(-1, 0, 1, 2, 0, 2, 0, 2, 3, cx, cy, cz);
    printf("electrostatic center (x, y, z) = (%lf, %lf, %lf)\n", cx, cy, cz);

    return 0;
}

```

![alt tag](https://raw.githubusercontent.com/ahrvoje/electrostatic-center/master/ElectrostaticCenter_CExamples.png)


Python
------

### Functions

### Examples

License
-------

All material in this repository is available under MIT license.
