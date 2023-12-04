#include <iostream>

#include "geometric.h"

int main()
{
	// default construction
	Matrix <int, 2, 2> m1;
	Matrix <int, 2, 3> m2;
	Matrix <int, 4, 2> m3;
	print(m1);
	print(m2);
	print(m3);

	Vector <int, 2> v1;
	Vector <int, 3> v2;
	Vector <int, 4> v3;
	print(v1);
	print(v2);
	print(v3);

	Covector <int, 2> c1;
	Covector <int, 3> c2;
	Covector <int, 4> c3;
	print(c1);
	print(c2);
	print(c3);

	Scalar <int> s1;
	print(s1);

	// std::array
	std::array <int, 4> matrix_elems3{4, -2, 9, -1};
	std::array <int, 2> vector_elems3_2{4, -2};
	std::array <int, 4> vector_elems3_4{-2, 2, 0, -1};
	std::array <int, 1> scalar_elem3{-2};

	Matrix <int, 2, 2> m4{matrix_elems3};
	Matrix <int, 2, 2> m5{std::move(matrix_elems3)};
	print(m4);
	print(m5);

	Vector <int, 2> v4{vector_elems3_2};
	Covector <int, 4> c4{std:move(vector_elems3_4)};
	print(v4);
	print(c4);

	Covector <int, 2> c5{std:move(vector_elems3_2)};
	Vector <int, 4> v5{std::move(vector_elems3_4)};
	print(v5);
	print(c5);

	Scalar <int> s2{scalar_elem3};
	Scalar <int> s3{std::move(scalar_elem3)};
	print(s2);
	print(s3);

	// initializer list
	Matrix <int, 2, 2> id{1, 0, 0, 1};
	Matrix <int, 2, 2> m6{1, 4, -2, 6};
	Matrix <int, 2, 5> m7{1, 9, -2, 4, -2, 1, 1, 0, 6, -3};
	Matrix <int, 4, 3> m8{-9, 8, 21, 0, -7, 0, 6, 1, 4, -2, 0, 6};
	print(id);
	print(m6);
	print(m7);
	print(m8);

	Vector <int, 2> v6{1, 0};
	Vector <int, 4> v7{0, -1, 0, 1};
	print(v6);
	print(v7);

	Covector <int, 3> c6{6, 0, 2};
	Covector <int, 4> c7{-1, -1, 9, 5};
	print(c6);
	print(c7);

	Scalar <int> s4{42};
	print(s4);

	// row extraction
	Matrix <int, 2, 3> m9{-11, 9, 4, 0, -9, 2};
	Covector <int, 3> c8_0{m9[0]};
	Covector <int, 3> c8_1{m9[1]};
	print(m9);
	print(c8_0);
	print(c8_1);

	// negation
	Matrix <int, 2, 2> m10{1, 4, -2, 6};
	Vector <int, 4> v8{0, -1, 0, 1};
	Covector <int, 3> c9{-6, 0, 2};
	print(-m10);
	print(-v8);
	print(-c9);

	// product assignment
	Matrix <int, 2, 2> m11{1, 4, -2, 6};
	Vector <int, 4> v9{0, -1, 0, 1};
	Covector <int, 3> c10{-6, 0, 2};
	m11 *= 2;
	v9 *= -2;
	c10 *= 3;
	print(m11);
	print(v9);
	print(c10);

	// quotient assignment
	Matrix <double, 2, 2> m12{10.0, 4.0, -2.0, 6.0};
	Vector <double, 4> v10{0.0, -8.0, 0.0, 4};
	Covector <double, 3> c11{-6, -3, 9};
	m12 /= 2;
	v10 /= -4;
	c11 /= 3;
	print(m12);
	print(v10);
	print(c11);

	// sum assignment
	Matrix <int, 2, 2> m13{1, 4, -2, 6};
	Matrix <int, 2, 2> m13_other{-1, 5, 4, -2};
	Vector <int, 4> v11{0, -1, 0, 1};
	Vector <int, 4> v11_other{2, 2, -2, -2};
	Covector <int, 3> c12{-6, 0, 2};
	Covector <int, 3> c12_other{2, 0, 3};
	m13 += m13_other;
	v11 += v11_other;
	c12 += c12_other;
	print(m13);
	print(v11);
	print(c12);

	// square root

	// scalar multiplication

	// addition
	//Matrix <int, 2, 2> m90{id + m5};
	//print(m90);

	// subtraction
	//Matrix <int, 2, 2> m100{id - m5};
	//print(m100);

	// multiplication
	//Matrix <int, 2, 2> m110{id * m5};
	//print(m110);

	// transpose (square)
	Matrix <int, 2, 2> m14{1, -3, -2, -1};
	Matrix <int, 3, 3> m15{2, 4, -5, 7, 1, 0, -3, 12, 10};
	print(transpose(m14));
	print(transpose(m15));

	// transpose (rectangular)
	Matrix <int, 2, 5> m16{1, 9, -2, 4, -2, 1, 1, 0, 6, -3};
	Matrix <int, 4, 3> m17{-9, 8, 21, 0, -7, 0, 6, 1, 4, -2, 0, 6};
	print(transpose(m16));
	print(transpose(m17));

	Vector <int, 2> v12{1, 0};
	Vector <int, 4> v13{0, -1, 0, 1};
	print(transpose(v12));
	print(transpose(v13));

	Covector <int, 3> c13{6, 0, 2};
	Covector <int, 4> c14{-1, -1, 9, 5};
	print(transpose(c13));
	print(transpose(c14));

	// length squared
	Vector <int, 4> v14{0, -1, 0, 1};
	Vector <int, 4> v15{2, 2, -2, -2};
	print(length_squared(v14));
	print(length_squared(v15));

	// length

	// retrieving scalars/coordinates
}

