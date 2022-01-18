//
// Created by xerne on 18/01/2022.
//

#ifndef MOZ_FASTMATH_H
#define MOZ_FASTMATH_H

#include "Constants.h"


inline float abs(float value) {
	union { float f; unsigned long int i; } v = { .f = value };
	v.i &= 0x7FFFFFFF;
	return v.f;
}

inline double abs(double value) {
	union { double f; unsigned long long int i; } v = { .f = value };
	v.i &= 0x7FFFFFFFFFFFFFFF;
	return v.f;
}


inline float  trunc(float  value) { return (float )((int)value); }
inline double trunc(double value) { return (double)((int)value); }

inline float  frac(float  value) { return value - trunc(value); }
inline double frac(double value) { return value - trunc(value); }

inline float  mod(float  v, float  modulo) { float  r = modulo * frac(v*(1/modulo)); return r < 0 ? r + modulo : r; }
inline double mod(double v, double modulo) { double r = modulo * frac(v*(1/modulo)); return r < 0 ? r + modulo : r; }

template<typename type>
type __taylor_cosine_approximation(type theta) {
	const type t_sq = theta*theta;
	const type t_qu = t_sq*t_sq;
	const type t_he = t_qu*t_sq;
	const type t_oc = t_qu*t_qu;
	const type t_de = t_he*t_qu;

	const type coef1 =  (type)(1)/(type)(1);
	const type coef2 = -(type)(1)/(type)(2*1);
	const type coef3 =  (type)(1)/(type)(4*3*2*1);
	const type coef4 = -(type)(1)/(type)(6*5*4*3*2*1);
	const type coef5 =  (type)(1)/(type)(8*7*6*5*4*3*2*1);
	const type coef6 = -(type)(1)/(type)(10*9*8*7*6*5*4*3*2*1);

	return coef1 +
		   coef2*t_sq +
		   coef3*t_qu +
		   coef4*t_he +
		   coef5*t_oc +
		   coef6*t_de;
}

inline float  cos(float  theta) { return -__taylor_cosine_approximation(abs(mod(theta, (float )(2*PI)) - PI)); }
inline double cos(double theta) { return -__taylor_cosine_approximation(abs(mod(theta, (double)(2*PI)) - PI)); }

inline float  sin(float  theta) { return cos(theta - (PI/2)); }
inline double sin(double theta) { return cos(theta - (PI/2)); }

#endif //MOZ_FASTMATH_H
