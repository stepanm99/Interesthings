#include "../incl/imgts.h"
#include <stdint.h>

void	get_pixel(t_pixel *pixel, t_pixel *pixel_data, int32_t x, int32_t y)
{
	*pixel = pixel_data[x + (y * x)];
}
