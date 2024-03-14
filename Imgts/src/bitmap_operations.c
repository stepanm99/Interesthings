#include "../incl/imgts.h"

void	get_pixel(t_pixel *pixel, t_pixel *pixel_data, int32_t x, int32_t y)
{
	*pixel = pixel_data[x + (y * x)];
}
/*
t_pixel	pixel_matrix_average(int32_t x0, int32_t y0, int32_t mx, int32_t my, t_pixel *pixel_data)
{
	t_pixel	average;


}*/
