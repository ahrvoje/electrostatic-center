Center of electrostatic potential X(5626)
=========================================

It is the point of maximal electrostatic potential inside a triangle having a homogeneous surface charge distribution. It's also a point of zero electric field of the same charge distribution, and happens to satisfy the mathematical definition of triangle center. A lot of technical details can be found in the article *'From electrostatic potentials to yet another triangle center'* by Hrvoje Abraham and Vjekoslav Kovac. (http://arxiv.org/pdf/1312.3176v2.pdf)

Center is also listed in Kimberling's Encyclopedia of triangle centers under *X(5626) = CENTER OF ELECTROSTATIC POTENTIAL.* (http://faculty.evansville.edu/ck6/encyclopedia/ETCPart4.html)

The point was successfully used to improve the stability and speed up the convergence of BEM methods for electrostatic problems.

This repository contains a few routines for numerical calculation of X(5626). Precise routines are written in Wolfram Mathematica, with practical approximation being implemented in C and Python.

Wolfram Mathematica
-------------------

A brief documentation for Mathematica functions available in __ElectrostaticCenter.nb__

### Functions

```
FindElectrostaticLambda[{{ax_,ay_},{bx_,by_},{cx_,cy_}}]
```

Finds numerical value of *lambda* parameter of triangle electrostatic center X(5626) based on 2D Cartesian coordinates of triangle vertices. Default value of *Precision* option is 12 decimal places.

```
ElectrostaticLine[{{ax_,ay_},{bx_,by_},{cx_,cy_}}, lambda_]
```

Computes a point on electrostatic line of the triangle based on 2D Cartesian coordinates of triangle vertices and *lambda* parameter. Returns electrostatic center X(5626) if its *lambda* is used.

```
FindElectrostaticCenter2D[{{ax_,ay_},{bx_,by_},{cx_,cy_}}]
```

Returns electrostatic center X(5626) of triangle defined with 2D Cartesian coordinates of its vertices. Default value of *Precision* option is 12 decimal places.

```
FindElectrostaticCenter3D[{{ax_,ay_,az_},{bx_,by_,bz_},{cx_,cy_,cz_}}]
```

Returns electrostatic center X(5626) of triangle defined with 3D Cartesian coordinates of its vertices. Default value of *Precision* option is 12 decimal places.

### Example

![alt tag](https://raw.githubusercontent.com/ahrvoje/electrostatic-center/master/resources/ElectrostaticCenter_MathematicaExample.png)

C
-

A brief documentation for C functions available in __electrostaticCenter.c__. These functions use approximate estimation of *lambda* parameter described in section 6 of the article mentioned in the header of this document. Estimation is implemented in a way which reduces the probability of numerical overflow or underflow.

### Functions

#### electrostaticCenter2D
_Description:_   
Computes coordinates of electrostatic center based on 2D Cartesian coordinates of triangle vertices.

_Syntax:_
```C
int electrostaticCenter2D(double ax, double ay, double bx, double by, double cx, double cy,
                          double* x, double* y)
```
_Parameters:_   
*ax, ay, bx, by, cx, cy* - Cartesian coordinates of ABC triangle vertices   
*x, y* - pointers to result variables for Cartesian coordinates of electrostatic center

_Return value:_   
*1* - if calculation is successfully executed   
*< 0* - if some calculation problem occured, it can vary between -8 and -1 depending on which step failed

#### electrostaticCenter3D

_Description:_   
Computes coordinates of electrostatic center based on 3D Cartesian coordinates of triangle vertices.

_Syntax:_
```C
int electrostaticCenter3D(double ax, double ay, double az, double bx, double by, double bz,
                          double cx, double cy, double cz, double* x, double* y, double* z)
```
_Parameters:_   
*ax, ay, bx, by, cx, cy* - Cartesian coordinates of ABC triangle vertices   
*x, y* - pointers to result variables for Cartesian coordinates of electrostatic center

_Return value:_   
*1* - if calculation is successfully executed   
*< 0* - if some calculation problem occured, it can vary between -8 and -1 depending on which step failed

### Example

```C
#include <stdio.h>
#include "..\src\electrostaticCenter.h"

int main(void)
{
    double cx, cy, cz;

    // compute electrostatic center for triangle ABC
    // A(-1,0), B(2,0), C(0,2)
    electrostaticCenter2D(-1, 0, 2, 0, 0, 2, &cx, &cy);
    printf("electrostatic center (x, y) = (%lf, %lf)\n", cx, cy);

    // compute electrostatic center for triangle ABC
    // A(-1,0,1), B(2,0,2), C(0,2,3)
    electrostaticCenter3D(-1, 0, 1, 2, 0, 2, 0, 2, 3, &cx, &cy, &cz);
    printf("electrostatic center (x, y, z) = (%lf, %lf, %lf)\n", cx, cy, cz);

    return 0;
}
```

![alt tag](https://raw.githubusercontent.com/ahrvoje/electrostatic-center/master/resources/ElectrostaticCenter_CExample.png)


Python
------

A brief documentation for Python functions available in __electrostaticCenter.py__. These functions use approximate estimation of *lambda* parameter described in section 6 of the article mentioned in the header of this document. Estimation is implemented in a way which reduces the probability of numerical overflow or underflow.

### Functions

```Python
[x, y] = electrostaticCenter2D([[ax, ay], [bx, by], [cx, cy]])
```

Returns electrostatic center of triangle defined as a triplet of 2D Cartesian coordinates of its vertices.

```Python
[x, y, z] = electrostaticCenter3D([[ax, ay, az], [bx, by, bz], [cx, cy, cz]])
```

Returns electrostatic center of triangle defined as a triplet of 3D Cartesian coordinates of its vertices.

### Example

```Python
from electrostaticCenter import *

print 'electrostatic center [x, y] =', electrostaticCenter2D([[-1, 0], [2, 0], [0, 2]])
print 'electrostatic center [x, y, z] =', electrostaticCenter3D([[-1, 0, 1], [2, 0, 2], [0, 2, 3]])
```

![alt tag](https://raw.githubusercontent.com/ahrvoje/electrostatic-center/master/resources/ElectrostaticCenter_PythonExample.png)

License
-------

All material in this repository is available under MIT license.
