#ifndef _COLOUR_H_
#define _COLOUR_H_

#include "geometric.h"

using Colour = Vec3<double>;

auto write_colour(std::ostream& out, Colour pixel_colour)
{
	int red_intensity{static_cast<int> (255.999 * x(pixel_colour))};
	int green_intensity{static_cast<int> (255.999 * y(pixel_colour))};
	int blue_intensity{static_cast<int> (255.999 * z(pixel_colour))};

	out << red_intensity << ' ' << green_intensity << ' ' << blue_intensity << '\n';
}

#endif

