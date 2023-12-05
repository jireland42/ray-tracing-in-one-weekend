#ifndef _TRACER_H_
#define _TRACER_H_

#include "ray.h"
#include "colour.h"

#include <iostream>

template <typename T>
auto hit_sphere(Point3<T> const& centre, T radius, Ray<T> const& ray) -> bool
{
	// finding the intersection of the ray
	//     r.origin + t * ray.direction
	// and the sphere defined by points, P, such that
	//     <P - centre | P - center> = radius * radius
	// Expanding and simplifying yields the quadratic
	//     t^2 * <ray.direction|ray.direction>
	//     + 2 * t * <ray.direction|ray.origin - centre>
	//     + <ray.origin - centre|ray.origin - centre>
	//     - radius^2
	auto centre_normal{ray.origin() - centre};
	auto direction_length_squared{length_squared(ray.direction())};
	auto deviation{2 * transpose(ray.direction()) * centre_normal};
	auto centre_normal_length_squared{length_squared(centre_normal)};

	auto a{direction_length_squared};
	auto b{2.0 * transpose(centre_normal) * ray.direction()};
	auto c{value(centre_normal_length_squared) - radius*radius};
	auto discriminant{value(b*b - 4*a*c)};

	return (discriminant >= 0.0);
}

template <typename T>
auto ray_colour(Ray<T> const& ray)
{
	Point3<T> circle_centre{0.0, 0.0, 1.0};
	T circle_radius{0.60};
	Colour circle_colour{1.0, 0.0, 0.0};

	if (hit_sphere (circle_centre, circle_radius, ray)) { return circle_colour; }

	auto unit_direction{normalize(ray.direction())};
	auto sample_point{0.5 * (y(unit_direction) + 1.0)}; // -1 <= y <= 1

	Colour range_start{1.0, 1.0 , 1.0};
	Colour range_end{0.5, 0.7 , 1.0};

	return ((1 - sample_point) * range_start) + sample_point*range_end;
}

template <typename T>
auto trace(
	int image_height,
	int image_width,
	Point3<T> upper_left_viewport_pixel,
	Vec3<T> pixel_resoluton_u,
	Vec3<T> pixel_resoluton_v,
	Point3<T> camera_origin)
{
	for (int j{0}; j < image_height; j += 1)
	{
		std::clog << "\rScanlines Remaining: " << (image_height - j) << ' ' << std::flush;

		for (int i{0}; i < image_width; i += 1)
		{
			auto pixel_centre{upper_left_viewport_pixel + (i * pixel_resoluton_u) + (j * pixel_resoluton_v)};
			auto ray_direction{pixel_centre - camera_origin};
			Ray ray{camera_origin, ray_direction};

			Colour colour{ray_colour(ray)};
			write_colour(std::cout, colour);
		}
	}
}

#endif
