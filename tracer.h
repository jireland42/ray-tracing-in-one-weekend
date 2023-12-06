#ifndef _TRACER_H_
#define _TRACER_H_

#include "ray.h"
#include "colour.h"

#include <iostream>

template <typename T>
decltype(auto) hit_sphere(Point3<T> const& centre, T radius, Ray<T> const& ray)
{
	// TODO: profile this for using wedge product?
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
	auto centre_normal_length_squared{length_squared(centre_normal)};

	auto a{direction_length_squared};
	auto half_b{transpose(centre_normal) * ray.direction()};
	auto c{value(centre_normal_length_squared) - radius*radius};
	auto quarter_discriminant{value((half_b)*(half_b) - a*c)};

	if ((4*quarter_discriminant) < 0.0)
	{
		return -1.0;
	}
	else
	{
		//std::cerr << "Nat a: " << value(a) << '\n';
		//std::cerr << "Mul a: " << 1.0*value(a) << '\n';
		//std::cerr << "Nat: " << (-value(half_b) + sqrt((quarter_discriminant))) / value(a) << '\n';
		//std::cerr << "Mul: " << (-value(half_b) + sqrt((quarter_discriminant))) / (1.0*value(a)) << '\n' << '\n';
		return (-value(half_b) + sqrt(quarter_discriminant)) / 1*value(a);
	}
}

template <typename T>
auto ray_colour(Ray<T> const& ray)
{
	Point3<T> circle_centre{0.0, 0.0, 1.0};
	T circle_radius{0.80};
	Colour circle_colour{1.0, 0.0, 0.0};

	auto time_of_hit{hit_sphere(circle_centre, circle_radius, ray)};

	if (time_of_hit > 0.0)
	{
		auto normal{normalize(ray.at(time_of_hit) - circle_centre)};
		auto colour_vec{0.5 * (normal + Point3<T>({1.0, 1.0, 1.0}))};
		return Colour{x(colour_vec), y(colour_vec), z(colour_vec)};
	}

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
