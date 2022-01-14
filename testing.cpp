//
// Created by Marc on 14/01/2022.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "library.h"
#include "Matrix.h"



TEST_CASE("Matrix initialization", "[matrix][init]") {
	matrix<float, 2, 2> a;
	a.set_cell(0, 0, 6.f);
	a.set_cell(0, 1, 9.f);
	a.set_cell(1, 0, 2.f);
	a.set_cell(1, 1, 3.f);

	matrix<float, 2, 2> b = matrix<float, 2, 2>(6.f, 9.f, 2.f, 3.f);
	bool same1 = a == b;

	REQUIRE(same1);

	a.set_cell(0, 0, 18.f);
	a.set_cell(0, 1, 18.f);
	a.set_cell(1, 0, 18.f);
	a.set_cell(1, 1, 18.f);

	b = matrix<float, 2, 2>(18.f);
	bool same2 = a == b;
	REQUIRE(same2);


}

TEST_CASE("Matrix equality check", "[matrix][equality]") {
	matrix<float, 2, 2> a = matrix<float, 2, 2>(1.f, 2.f, 3.f, 4.f);
	matrix<float, 2, 2> b = matrix<float, 2, 2>(1.f, 2.f, 3.f, 4.f);
	matrix<float, 2, 2> c = matrix<float, 2, 2>(23.f, 34.f, 31.f, 46.f);

	bool a_is_a = a == a;
	bool a_is_b = a == b;
	bool a_is_c = a == c;

	REQUIRE(a_is_a);
	REQUIRE(a_is_b);
	REQUIRE_FALSE(a_is_c);



}


TEST_CASE("Check for correct matrix multiplication", "[matrix][multiplication]") {
	matrix<float, 2, 2> a = matrix<float, 2, 2>(1.f, 2.f, 3.f, 4.f);
	matrix<float, 2, 2> b = matrix<float, 2, 2>(5.f, 6.f, 7.f, 8.f);
	matrix<float, 2, 2> c = matrix<float, 2, 2>(23.f, 34.f, 31.f, 46.f);

	bool t = c == a*b;
	REQUIRE(t);

}


TEST_CASE("Vector Components", "[matrix][vector][components]") {
	fvec4 v = fvec4(1.f, 3.f, 2.f, 7.f);

	REQUIRE(v.x == v.get_cell(0, 0));
	REQUIRE(v.y == v.get_cell(0, 1));
	REQUIRE(v.z == v.get_cell(0, 2));
	REQUIRE(v.w == v.get_cell(0, 3));

	v.x = 8.f;
	v.y = 9.f;
	v.z = 6.f;
	v.w = 5.f;

	REQUIRE(8.f == v.get_cell(0, 0));
	REQUIRE(9.f == v.get_cell(0, 1));
	REQUIRE(6.f == v.get_cell(0, 2));
	REQUIRE(5.f == v.get_cell(0, 3));

	REQUIRE(v.x == v.get_cell(0, 0));
	REQUIRE(v.y == v.get_cell(0, 1));
	REQUIRE(v.z == v.get_cell(0, 2));
	REQUIRE(v.w == v.get_cell(0, 3));
}