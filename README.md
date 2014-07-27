Center of electrostatic potential X(5626)
=========================================

This repository containes a few routines for numerical calculation of Center of electrostatic potential, characteristic triangle point X(5626). Routines are mainly written in Wolfram Mathematica, but practical approximation is also implemented in C and Python.

Center of electrostatic potential is a maximum point of electrostatic potential of homogeneous charge distribution on a triangle domain. It's also a point of zero electric field of the same charge distribution. A lot of technical details can be found in the article *'From electrostatic potentials to yet another triangle center'* by Hrvoje Abraham and Vjekoslav Kovac. (http://arxiv.org/pdf/1312.3176v2.pdf)

Center is also incorporated into Kimberling's Encyclopedia of triangle centers as point *X(5626) = CENTER OF ELECTROSTATIC POTENTIAL.* (http://faculty.evansville.edu/ck6/encyclopedia/ETCPart4.html)

Wolfram Mathematica functions
-----------------------------

```
FindElectrostaticLambda[{{xa_,ya_},{xb_,yb_},{xc_,yc_}}, *options*]
```

```
ElectrostaticLine[{{xa_,ya_},{xb_,yb_},{xc_,yc_}}, *options*]
```

```
FindElectrostaticCenter[{{xa_,ya_},{xb_,yb_},{xc_,yc_}}, *options*]
```

C functions
------

Python functions
----------------
