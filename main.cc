#include <iomanip>
#include <iostream>

#include "geometric.h"
#include "tracer.h"

int main()
{
	using decimal = double;
	constexpr decimal aspect_ratio{16.0 / 9.0};

	// Image
	constexpr int image_width{1920};
	constexpr int image_height{static_cast <int> (image_width / aspect_ratio)};

	// Camera
	constexpr decimal focal_length{1.0};
	constexpr Point3<decimal> camera_origin{};

	// Viewport
	constexpr decimal viewport_width{16.0};
	constexpr decimal viewport_height{(viewport_width * image_height) / static_cast <decimal> (image_width)};

	// Viewport Vectors in Viewport Space
	constexpr Vec3<decimal> viewport_u{viewport_width, 0, 0};
	constexpr Vec3<decimal> viewport_v{0, -viewport_height, 0};
	constexpr Vec3<decimal> pixel_resoluton_u{viewport_u / image_width};
	constexpr Vec3<decimal> pixel_resoluton_v{viewport_v / image_height};

	// Viewport Origin in World Space
	Point3<decimal> viewport_center{0, 0, focal_length};
	Point3<decimal> viewport_origin{camera_origin + viewport_center - (viewport_u / 2) - (viewport_v / 2)};

	Point3<decimal>
	upper_left_viewport_pixel{viewport_origin + (pixel_resoluton_u + pixel_resoluton_v) * 0.5};

	// Render
	std::cout << "P3\n";
	std::cout << image_width << ' ' << image_height << '\n';
	std::cout << "255\n";

	trace(
		image_height,
		image_width,
		upper_left_viewport_pixel,
		pixel_resoluton_u,
		pixel_resoluton_v,
		camera_origin);

	std::clog << "\rDone.                              \n";
	std::cout << '\n';
}

