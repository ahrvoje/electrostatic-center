Center of electrostatic potential X(5626)
=========================================

It is a maximum point of electrostatic potential of homogeneous charge distribution on a triangle domain. It's also a point of zero electric field of the same charge distribution, and happens to satisfy the mathematical definition of triangle center. A lot of technical details can be found in the article *'From electrostatic potentials to yet another triangle center'* by Hrvoje Abraham and Vjekoslav Kovac. (http://arxiv.org/pdf/1312.3176v2.pdf)

Center is also listed in Kimberling's Encyclopedia of triangle centers under *X(5626) = CENTER OF ELECTROSTATIC POTENTIAL.* (http://faculty.evansville.edu/ck6/encyclopedia/ETCPart4.html)

This repository containes a few routines for numerical calculation of X(5626). Routines are mainly written in Wolfram Mathematica, but practical approximation is also implemented in C and Python.

Wolfram Mathematica
-------------------

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

### Functions

### Examples

Python
------

### Functions

### Examples

License
-------

All material in this repository is available under MIT license.
