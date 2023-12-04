#ifndef _RAY_H_
#define _RAY_H_

#include "geometric.h"

class Ray
{
  public:
	Ray(Point3<double> origin, Vec3<double> direction)
	: _origin{std::move(origin)}, _direction{std::move(direction)} {}

	template <typename T>
	Point3<double> at(T t) const
	{
		return _origin + (t * _direction);
	}

	constexpr auto origin() const& -> Point3<double> { return _origin; }
	constexpr auto origin() && -> Point3<double> { return std::move(_origin); }
	constexpr auto direction() const& -> Vec3<double> { return _direction; }
	constexpr auto direction() && -> Vec3<double> { return std::move(_direction); }

  private:
	Point3<double> _origin;
	Vec3<double> _direction;
};

#endif
