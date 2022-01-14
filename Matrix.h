//
// Created by Marc on 14/01/2022.
//

#ifndef MOZ_MATRIX_H
#define MOZ_MATRIX_H



template <typename type, int cols, int rows>
struct matrix {
	union {
		type cells[rows*cols];
		struct {type x; type y; type z; type w;};
		struct {type r; type g; type b; type a;};
		struct {type s; type t; type u; type v;};
	}; // God I love the unsafe!


	matrix() = default;

	explicit matrix(type fill) {
		for (int i = 0; i < rows*cols; i++) cells[i] = fill;
	}

	template<typename... types>
	explicit matrix(type first, types... values) {
		static_assert(sizeof...(values)+1 == rows*cols, "Not the correct number of arguments passed for matrix initialization");
		type newCells[rows*cols] = {first, values...};
		for (int i = 0; i < rows*cols; i++) cells[i] = newCells[i];
	}

	inline type get_cell(int cell_x, int cell_y) {
		return cells[cell_x*rows + cell_y];
	}
	inline void set_cell(int cell_x, int cell_y, type value) {
		cells[cell_x*rows + cell_y] = value;
	}

	template <int other_cols>
	inline matrix<type, other_cols, rows> operator*(matrix<type, other_cols, cols> other) {
		matrix<type, other_cols, rows> result;

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

	inline matrix<type, cols, rows> operator*(type other) {
		matrix<type, cols, rows> result;
		for (int i = 0; i < cols*rows; i++) {
			result.cells[i] = cells[i]*other;
		}
		return result;
	}

	inline matrix<type, cols, rows> operator+(matrix<type, cols, rows> other) {
		matrix<type, cols, rows> result;
		for (int i = 0; i < cols*rows; i++) {
			result.cells[i] = other.cells[i]+cells[i];
		}
		return result;
	}

	inline matrix<type, cols, rows> operator-(matrix<type, cols, rows> other) {
		matrix<type, cols, rows> result;
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

	bool operator==(matrix<type, cols, rows> other) {
		for (int i = 0; i < cols*rows; i++) {
			if (cells[i] != other.cells[i]) return false;
		}
		return true;
	}
};



template <int cols, int rows> using fmat = matrix<float,  cols, rows>;
template <int cols, int rows> using dmat = matrix<double, cols, rows>;

using fmat2 = fmat<2, 2>;
using fmat3 = fmat<3, 3>;
using fmat4 = fmat<4, 4>;

using dmat2 = dmat<2, 2>;
using dmat3 = dmat<3, 3>;
using dmat4 = dmat<4, 4>;

template <int components> using fvec = matrix<float,  1, components>;
template <int components> using dvec = matrix<double, 1, components>;

using fvec2 = fvec<2>;
using fvec3 = fvec<3>;
using fvec4 = fvec<4>;

using dvec2 = dvec<2>;
using dvec3 = dvec<3>;
using dvec4 = dvec<4>;

#endif //MOZ_MATRIX_H
