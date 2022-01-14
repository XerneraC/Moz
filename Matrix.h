//
// Created by Marc on 14/01/2022.
//

#ifndef MOZ_MATRIX_H
#define MOZ_MATRIX_H

#define MOZ_MATRIX__INCLUDE_COMPONENT_BINDINGS  // If this is defined, matrix components can be accessed with matrix.x, matrix.y, matrix.z, matrix.w

template <typename type, int cols, int rows>
struct Matrix {

#ifdef MOZ_MATRIX__INCLUDE_COMPONENT_BINDINGS
	union {
		type cells[rows*cols];
		struct { type x; type y; type z; type w; };
		struct { type r; type g; type b; type a; };
		struct { type s; type t; type u; type v; };
	}; // God, I love the unsafe!
#else
	type cells[rows*cols];
#endif

	Matrix() = default;

	explicit Matrix(type fill) { for (int i = 0; i < rows*cols; i++) cells[i] = fill; }

	template<typename... types>
	explicit Matrix(type first, types... values) {
		static_assert(sizeof...(values)+1 == rows*cols, "Not the correct number of arguments passed for matrix initialization");
		type newCells[rows*cols] = {first, values...};
		for (int i = 0; i < rows*cols; i++) cells[i] = newCells[i];
	}

	// TODO: This could use static_asserts
	inline type get_cell(int cell_x, int cell_y)      { return cells[cell_x*rows + cell_y]; }
	inline void set_cell(int cell_x, int cell_y, type value) { cells[cell_x*rows + cell_y] = value; }

	template <int other_cols>
	inline Matrix<type, other_cols, rows> operator*(Matrix<type, other_cols, cols> other) {
		Matrix<type, other_cols, rows> result;

		for (int cell_x = 0; cell_x < other_cols; cell_x++) { for (int cell_y = 0; cell_y < rows; cell_y++) {
			type total = get_cell(0, cell_y) * other.get_cell(cell_x, 0);
			for (int r = 1; r < cols; r++) {
				type a = get_cell(r, cell_y);
				type b = other.get_cell(cell_x, r);
				total = total + a*b;
			}
			result.set_cell(cell_x, cell_y, total);
		}}

		return result;
	}

	inline Matrix<type, cols, rows> operator*(type other) {
		Matrix<type, cols, rows> result;
		for (int i = 0; i < cols*rows; i++) {
			result.cells[i] = cells[i]*other;
		}
		return result;
	}

	inline Matrix<type, cols, rows> operator+(Matrix<type, cols, rows> other) {
		Matrix<type, cols, rows> result;
		for (int i = 0; i < cols*rows; i++) {
			result.cells[i] = other.cells[i]+cells[i];
		}
		return result;
	}

	inline Matrix<type, cols, rows> operator-(Matrix<type, cols, rows> other) {
		Matrix<type, cols, rows> result;
		for (int i = 0; i < cols*rows; i++) {
			result.cells[i] = other.cells[i]-cells[i];
		}
		return result;
	}

	template <type(*func)(type)>
	inline void apply_func() {
		for (int i = 0; i < cols*rows; i++) {
			cells[i] = func(cells[i]);
		}
	}

	inline bool operator==(Matrix<type, cols, rows> other) {
		for (int i = 0; i < cols*rows; i++) {
			if (cells[i] != other.cells[i]) return false;
		}
		return true;
	}

	inline type  operator[](unsigned i) const { return cells[i]; }
	inline type& operator[](unsigned i)       { return cells[i]; }

	inline Matrix<type, rows, cols> transpose() {
		Matrix<type, rows, cols> result;
		for (int cell_x = 0; cell_x < cols; cell_x++) { for (int cell_y = 0; cell_y < rows; cell_y++) {
			result.set_cell(cell_y, cell_x, get_cell(cell_x, cell_y));
		}}
		return result;
	}

	inline Matrix<type, rows, cols> T() { return transpose(); }

};


template <typename type, int components> using Vector = Matrix<type,  1, components>;

template <int cols, int rows> using fmat = Matrix<float,  cols, rows>;
template <int cols, int rows> using dmat = Matrix<double, cols, rows>;

template <int components> using fvec = Vector<float,  components>;
template <int components> using dvec = Vector<double, components>;

using fmat2 = fmat<2, 2>;
using fmat3 = fmat<3, 3>;
using fmat4 = fmat<4, 4>;

using dmat2 = dmat<2, 2>;
using dmat3 = dmat<3, 3>;
using dmat4 = dmat<4, 4>;

using fvec2 = fvec<2>;
using fvec3 = fvec<3>;
using fvec4 = fvec<4>;

using dvec2 = dvec<2>;
using dvec3 = dvec<3>;
using dvec4 = dvec<4>;






template<typename type, int components>
inline type dot(Vector<type, components> a, Vector<type, components> b) {
	return (a.T() * b)[0];
}

template<typename type>
inline Vector<type, 3> cross(Vector<type, 3> a, Vector<type, 3> b) {
	return Vector<type, 3>(a.y*b.z - a.z*b.y,
						   a.z*b.x - a.x*b.z,
						   a.x*b.y - a.y*b.x);
}



#endif //MOZ_MATRIX_H
