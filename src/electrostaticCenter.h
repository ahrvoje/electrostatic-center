/*
 * electrostaticCenter.h
 *
 *  Created on: 11.12.2013.
 *      Author: Hrvoje Abraham
 */

#ifndef ELECTROCENTER_H_
#define ELECTROCENTER_H_

// uncomment for debugging purposes
//#define ELECTROCENTERDEBUG

// enforce C names decoration
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// computation of triangle electrostatic center X(5626)
// using numerically robust approximation based on the article
// "From electrostatic potentials to yet another triangle center", by Hrvoje Abraham & Vjekoslav Kovac, 2013.
// http://arxiv.org/abs/1312.3176
int electrostaticCenter2D(double ax, double ay, double bx, double by, double cx, double cy, double* x, double* y);

// 3D case
int electrostaticCenter3D(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz, double* x, double* y, double* z);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* ELECTROCENTER_H_ */
