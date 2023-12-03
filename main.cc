#include <iomanip>
#include <iostream>

#include "geometric.h"
#include "colour.h"


int main()
{
	constexpr int image_width{256};
	constexpr int image_height{256};

	std::cout << "P3\n";
	std::cout << image_width << ' ' << image_height << '\n';
	std::cout << "255\n";

	for (int j{0}; j < image_height; j += 1)
	{
		std::clog << "\rScanlines Remaining: " << (image_height - j) << ' ' << std::flush;

		for (int i{0}; i < image_width; i += 1)
		{
			auto width_factor{static_cast <double> (i) / (image_width - 1)};
			auto height_factor{static_cast <double> (j) / (image_height - 1)};

			Colour colour{0, width_factor, height_factor};
			write_colour(std::cout, colour);
		}
	}

	std::clog << "\rDone.                              \n";
	
	std::cout << '\n';
}

