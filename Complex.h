//
// Created by xerne on 17/01/2022.
//

#ifndef MOZ_COMPLEX_H
#define MOZ_COMPLEX_H



template<typename type>
struct Complex {
	union { type real, x; };
	union { type imag, y; };

	Complex(type real, type imag) : real(real), imag(imag) {}
	Complex(type real) : real(real), imag() {}
	Complex() : real(), imag() {}

	inline Complex<type> operator+(Complex<type> other) { return Complex<type>(real + other.real, imag + other.imag); }
	inline Complex<type> operator-(Complex<type> other) { return Complex<type>(real - other.real, imag - other.imag); }

	inline Complex<type> operator-() { return Complex<type>(-real, -imag); }

	inline Complex<type> operator*(type other) { return Complex<type>(real * other, imag * other); }
	inline Complex<type> operator*(Complex<type> other) {
		return Complex<type>(real * other.real - imag * other.imag,
							 real * other.imag + imag * other.real);
	}

	inline Complex<type> conj() { return Complex<type>(real, -imag); }
	inline Complex<type>  inv() { return conj()/len2(); }
	inline type          len2() { return operator*(conj()).real; }

	inline Complex<type> operator/(type other) { return Complex<type>(real/other, imag/other); }
	inline Complex<type> operator/(Complex<type> other) { return operator*(other.inv()); }
};

using fcomp = Complex<float>;
using dcomp = Complex<double>;

#endif //MOZ_COMPLEX_H
