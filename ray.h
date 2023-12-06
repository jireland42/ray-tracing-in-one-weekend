#ifndef _RAY_H_
#define _RAY_H_

#include "geometric.h"

template <typename T>
class Ray
{
  public:
	Ray(Point3<T> origin, Vec3<T> direction)
	: _origin{std::move(origin)}, _direction{std::move(direction)} {}

	template <typename U>
	Point3<T> at(U time_of_hit) const
	{
		return _origin + (time_of_hit * _direction);
	}

	constexpr auto origin() const& -> Point3<T> { return _origin; }
	constexpr auto origin() && -> Point3<T> { return std::move(_origin); }
	constexpr auto direction() const& -> Vec3<T> { return _direction; }
	constexpr auto direction() && -> Vec3<T> { return std::move(_direction); }

  private:
	Point3<T> _origin;
	Vec3<T> _direction;
};

#endif
