#include <iostream>

#include "geometric.h"

int main()
{
	constexpr int image_width{256};
	constexpr int image_height{256};

	std::cout << "P3\n";
	std::cout << image_width << ' ' << image_height << '\n';
	std::cout << "255\n";

	for (int j{0}; j < image_height; j += 1)
	{
		//std::clog << "\rScanlines Remaining: " << (image_height - j) << ' ' << std::flush;

		//for (int i{0}; i < image_width; i += 1)
		//{
			//auto width_factor{static_cast <double> (i) / (image_width - 1)};
			//auto height_factor{static_cast <double> (j) / (image_height - 1)};

			//int red_intensity{static_cast <int> (255.999 * width_factor)};
			//int green_intensity{0};
			//int blue_intensity{static_cast <int> (255.999 * height_factor)};

			//std::cout << red_intensity << ' ' << green_intensity << ' ' << blue_intensity << '\n';
		//}
	}

	//std::clog << "\rDone.                              \n";
	
	std::cout << '\n';

	Matrix <int, 2, 2> id{1, 0, 0, 1};
	Matrix <int, 2, 2> m1;
	Matrix <int, 2, 3> m2;
	Matrix <int, 2, 2> m3{1, 4, -2, 6};

	print(id);
	print(m1);
	print(m2);
	print(m3);

	Matrix <int, 2, 2> m4{id + m3};
	print(m4);

	Matrix <int, 2, 2> m5{id - m3};
	print(m5);

	Matrix <int, 2, 2> m6{id * m3};
	print(m6);
}
