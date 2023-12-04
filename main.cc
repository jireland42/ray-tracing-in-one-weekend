#include <iomanip>
#include <iostream>

#include "geometric.h"
#include "colour.h"
#include "ray.h"

auto ray_colour(Ray const& ray)
{
	auto unit_direction{normalize(ray.direction())};
	auto sample_point{0.5 * (y(unit_direction) + 1.0)}; // -1 <= y <= 1
												  //
	Colour range_start{1.0, 1.0 , 1.0};
	Colour range_end{0.5, 0.7 , 1.0};

	return ((1 - sample_point) * range_start) + sample_point*range_end;
}

int main()
{
	constexpr double aspect_ratio{16.0 / 9.0};

	// Image
	constexpr int image_width{1920};
	constexpr int image_height{static_cast <int> (image_width / aspect_ratio)};

	// Camera
	constexpr double focal_length{1.0};
	constexpr Point3<double> camera_origin{};

	// Viewport
	constexpr double viewport_width{16.0};
	constexpr double viewport_height{(viewport_width * image_height) / static_cast <double> (image_width)};

	// Viewport Vectors in Viewport Space
	constexpr Vec3<double> viewport_u{viewport_width, 0, 0};
	constexpr Vec3<double> viewport_v{0, -viewport_height, 0};
	constexpr Vec3<double> pixel_resoluton_u{viewport_u / image_width};
	constexpr Vec3<double> pixel_resoluton_v{viewport_v / image_height};

	// Viewport Origin in World Space
	Point3<double> viewport_center{0, 0, focal_length};
	Point3<double> viewport_origin{camera_origin + viewport_center - (viewport_u / 2) - (viewport_v / 2)};

	Point3<double>
	upper_left_viewport_pixel{viewport_origin + (pixel_resoluton_u + pixel_resoluton_v) * 0.5};

	// Render
	std::cout << "P3\n";
	std::cout << image_width << ' ' << image_height << '\n';
	std::cout << "255\n";

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

	std::clog << "\rDone.                              \n";
	
	std::cout << '\n';
}

