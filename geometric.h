#ifndef _GEOMETRIC_H_
#define _GEOMETRIC_H_

#include <array>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <initializer_list>

#include <iostream>

template <typename T, size_t R, size_t C>
class Matrix
{
  public:
	std::array <T, C*R> elements;

	constexpr Matrix() : elements{std::array <T, C*R>{}} {}
	constexpr Matrix(std::array <T, R*C> elements) : elements{std::move(elements)} {}
	constexpr Matrix(std::initializer_list <T> initial_elements) : elements{std::array <T, C*R> {}}
	{
		auto new_elements_iterator{initial_elements.begin()};
		auto member_elements_iterator{elements.begin()};
		auto end{elements.end()};
		// verify the size here

		for (; member_elements_iterator != end;)
		{
			*member_elements_iterator = *new_elements_iterator;

			++member_elements_iterator;
			++new_elements_iterator;
		}
	}

	constexpr auto operator[](int const row) const -> Matrix <T,1,C>
	{
		Matrix <T,1,C> result;

		for (size_t i{0}; i < C; i += 1)
		{
			result.elements[i] += elements[row*C + i];
		}

		return result;
	}

	constexpr auto operator-() -> Matrix <T,R,C>&
	{
		std::transform(
			elements.cbegin(),
			elements.cend(),
			elements.begin(),
			[](T element) { return -1 * element; }
		);

		return *this;
	}

	constexpr auto operator*=(int const t) -> Matrix<T,R,C>
	{
		std::transform(
			elements.cbegin(),
			elements.cend(),
			elements.begin(),
			[t](T element) { return t * element; }
		);

		return *this;
	}

	template <typename K>
	constexpr auto operator/=(K const k) -> Matrix<T,R,C>
	{
		std::transform(
			elements.cbegin(),
			elements.cend(),
			elements.begin(),
			[k](T element) { return element / k; }
		);

		return *this;
	}

	constexpr auto operator+=(Matrix <T,R,C> const& other) -> Matrix<T,R,C>&
	{
		for (size_t i{0}; i < R*C; i += 1)
		{
			elements[i] += other.elements[i];
		}

		return *this;
	}
};

template <typename T, size_t R>
using Vector = Matrix<T,R,1>;

template <typename T>
using Vec3 = Vector<T,3>;

template <typename T, size_t C>
using Covector = Matrix<T,1,C>;

template <typename T>
using Cov3 = Covector<T,3>;

template <typename T>
using Scalar = Matrix<T,1,1>;

template <typename T>
using Point4 = Vector<T,4>;

template <typename T>
using Point3 = Vector<T,3>;

template <typename T>
using Plane = Covector<T,4>;

template <typename T>
constexpr decltype(auto) value(T&& scalar)
{
	return scalar.elements[0];
}

template <typename T, size_t R, size_t C>
constexpr auto sqrt(Matrix <T,R,C> const& matrix) -> Matrix <T,R,C>
{
	Matrix <T,R,C> result{};

	for (size_t i{0}; i < R*C; i += 1)
	{
		result.elements[i] = std::sqrt(matrix.elements[i]);
	}

	return result;
}

template <typename T, size_t R, size_t C>
constexpr auto sqrt(Matrix <T,R,C> && matrix) -> Matrix <T,R,C>
{
	for (size_t i{0}; i < R*C; i += 1)
	{
		matrix.elements[i] = std::sqrt(matrix.elements[i]);
	}

	return matrix;
}

template <typename T, size_t R, size_t C, typename K>
constexpr auto operator*(K k, Matrix <T,R,C> const& rhs) -> Matrix <T,R,C>
{
	Matrix <T,R,C> result{};

	for (size_t i{0}; i < R*C; i += 1)
	{
		result.elements[i] = k * rhs.elements[i];
	}

	return result;
}

template <typename T, size_t R, size_t C, typename K>
constexpr auto operator*(Matrix <T,R,C> const& lhs, K k) -> Matrix <T,R,C>
{
	return k * lhs;
}

template <typename T, size_t R, size_t C, typename K>
constexpr auto operator/(Matrix <T,R,C> const& rhs, K k) -> Matrix <T,R,C>
{
	Matrix <T,R,C> result{};

	for (size_t i{0}; i < R*C; i += 1)
	{
		result.elements[i] = rhs.elements[i] / k;
	}

	return result;
}

template <typename T, size_t N, typename K>
constexpr auto operator/(Vector<T,N> const& rhs, K k) -> Vector <T,N>
{
	Vector <T,N> result{};

	for (size_t i{0}; i < N; i += 1)
	{
		result.elements[i] = rhs.elements[i] / k;
	}

	return result;
}

template <typename T, size_t R, size_t C>
constexpr auto operator+(Matrix <T,R,C> const& lhs, Matrix <T,R,C> const& rhs) -> Matrix <T,R,C>
{
	Matrix <T,R,C> result{};

	for (size_t i{0}; i < R*C; i += 1)
	{
		result.elements[i] = lhs.elements[i] + rhs.elements[i];
	}

	return result;
}

template <typename T, size_t R, size_t C>
constexpr auto operator-(Matrix <T,R,C> const& lhs, Matrix <T,R,C> const& rhs) -> Matrix <T,R,C>
{
	Matrix <T,R,C> result{};

	for (size_t i{0}; i < R*C; i += 1)
	{
		result.elements[i] = lhs.elements[i] - rhs.elements[i];
	}

	return result;
}

template <typename T, size_t RL, size_t N, size_t CR>
constexpr auto operator*(Matrix <T,RL,N> const& lhs, Matrix <T,N,CR> const& rhs) -> Matrix <T,RL,CR>
{
	Matrix <T,RL,CR> result{};

	for (size_t c{0}; c < CR; c += 1)
	{
		for (size_t r{0}; r < RL; r += 1)
		{
			T value{};
			for (size_t i{0}; i < N; i += 1)
			{
				// lhs[r, i] * rhs[i, c]
				value += lhs.elements[r*N + i] * rhs.elements[i*CR + c];
			}

			result.elements[r*CR + c] = value;
		}
	}

	return result;
}

template <typename T, size_t R, size_t C>
constexpr auto transpose(Matrix <T,R,C> const& matrix) -> Matrix <T,C,R>
{
	Matrix <T,C,R> result{};

	for (size_t r{0}; r < R; r += 1)
	{
		for (size_t c{0}; c < C; c += 1)
		{
			result.elements[c*R + r] = matrix.elements[r*C + c];
		}
	}

	return result;
}

template <typename T, size_t N>
constexpr auto transpose(Matrix <T,N,N> const& matrix) -> Matrix <T,N,N>
{
	Matrix <T,N,N> result{};

	for (size_t r{0}; r < N; r += 1)
	{
		result.elements[r * (N + 1)] = matrix.elements[r * (N + 1)];

		for (size_t c{r + 1}; c < N; c += 1)
		{
			result.elements[r*N + c] = matrix.elements[r + c*N];
			result.elements[r + c*N] = matrix.elements[r*N + c];
		}
	}

	return result;
}

template <typename T>
constexpr decltype(auto) length_squared(T&& vec)
{
	return transpose(vec) * vec;
}

template <typename T>
constexpr decltype(auto) length(T&& vec)
{
	return sqrt(value(length_squared(std::forward<T>(vec))));
}

template <typename T>
constexpr decltype(auto) normalize(T && vec)
{
	return vec / length(vec);
}

template <typename T, size_t N>
constexpr auto x(Vector <T,N> const& vec) -> T
{
	return vec.elements[0];
}

template <typename T, size_t N>
constexpr auto y(Vector <T,N> const& vec) -> T
{
	return vec.elements[1];
}

template <typename T, size_t N>
constexpr auto z(Vector <T,N> const& vec) -> T
{
	return vec.elements[2];
}

template <typename T, size_t N>
constexpr auto x(Covector <T,N> const& vec) -> T
{
	return vec.elements[0];
}

template <typename T, size_t N>
constexpr auto y(Covector <T,N> const& vec) -> T
{
	return vec.elements[1];
}

template <typename T, size_t N>
constexpr auto z(Covector <T,N> const& vec) -> T
{
	return vec.elements[2];
}

template <typename T, size_t R, size_t C>
auto print(Matrix <T,R,C> const& matrix)
{
	for (size_t r{0}; r < R; r += 1)
	{
		for (size_t c{0}; c < C; c += 1)
		{
			std::cout << matrix.elements[r*C + c];
			if (c != (C - 1)) { std::cout << ", "; }
		}

		std::cout << '\n';
	}

	std::cout << '\n';
}

#endif
