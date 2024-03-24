#include "../incl/imgts.h"
#include <stdint.h>



void	pixel_average_to_sample(t_data *data)
{
	int			i;
	int			number_of_pixels;
	int16_t		average;

	i = 0;
	average = 0;
	printf("Performing pixel average to sample operation\n");
	number_of_pixels = data->bmp_header.width_px * data->bmp_header.height_px;
	data->number_of_samples = number_of_pixels;
	data->wav_data = malloc(sizeof(uint16_t) * number_of_pixels);
	if (!data->wav_data)
	{
		printf("Error while allocating memory for wav data!\n");
		free_data(data);
	}
	while (i != number_of_pixels)
	{
		average = data->pixels[i].r + data->pixels[i].g + data->pixels[i].b;
		average /= 3;
		average = average * (65535 / 256);
		average -= 32767;
		data->wav_data[i] = average;
		i++;
	}
}

void	pixel_average_zig_zag_to_sample(t_data *data)
{
	int		x;
	int		y;
	int		x_max;
	int		y_max;
	int		i;
	int		number_of_pixels;
	char	back;
	int16_t	average;
	t_pixel	pixel;

	x = 0;
	y = 0;
	x_max = data->bmp_header.width_px;
	y_max = data->bmp_header.height_px;
	i = 0;
	back = 0;
	number_of_pixels = x_max * y_max;
	data->number_of_samples = number_of_pixels;
	data->wav_data = malloc(sizeof(int16_t) *number_of_pixels);
	if (!data->wav_data)
	{
		printf("Error while allocating memory for wav data!\n");
		free_data(data);
	}
	while (i != number_of_pixels)
	{
		pixel = data->pixels[(y * y_max) + x];
		average = pixel.r + pixel.g + pixel.b;
		average *= (65535 / 766);
		average -= 32767;
		data->wav_data[i] = average;
		i++;
		if (x == 0)
			back = 0;
		if (!back)
			x++;
		if (back)
			x--;
		if (x == x_max)
		{
			back = 1;
			y++;
		}
	}
}

void	pixel_change_average_to_sample(t_data *data)
{
	int			i;
	int			number_of_pixels;
	int16_t		average;
	int16_t		last;

	i = 0;
	average = 0;
	last = 0;
	printf("Performing pixel change average to sample operation\n");
	number_of_pixels = data->bmp_header.width_px * data->bmp_header.height_px;
	data->number_of_samples = number_of_pixels;
	data->wav_data = malloc(sizeof(uint16_t) * number_of_pixels);
	if (!data->wav_data)
	{
		printf("Error while allocating memory for wav data!\n");
		free_data(data);
	}
	while (i != number_of_pixels)
	{
		average = data->pixels[i].r + data->pixels[i].g + data->pixels[i].b;
		average /= 3;
		average = average * (65535 / 256);
		average -= 32767;
		data->wav_data[i] = average - last;
		last = average;
		i++;
	}
}

/*----    Image spectrum scan    ----*/

void	get_lines(t_data *data, t_pixel **interpolines, int y_max, int column)
{
	int	i;

	i = 0;
	while (i != y_max)
	{
		interpolines[0][i] = data->pixels[(i * y_max) + column];
		interpolines[1][i] = data->pixels[((i + 1) * y_max) + column];
		i++;
	}
}

void	pixel_line_spectrum_scan(t_data *data)
{
	int		x;
	int		y;
	int		x_max;
	int		y_max;
	int		i;
	int		number_of_samples;
	int		samples_per_line;
	char	back;
	int16_t	average;
	t_pixel	pixel;
	t_pixel	interpolines[2][data->bmp_header.height_px];

	x = 0;
	y = 0;
	x_max = data->bmp_header.width_px;
	y_max = data->bmp_header.height_px;
	i = 0;
	back = 0;
	samples_per_line = 100;
	number_of_samples = x_max * samples_per_line;
	data->wav_data = malloc(sizeof(int16_t) * number_of_samples);
	if (!data->wav_data)
	{
		printf("Error while allocating memory for wav data!\n");
		free_data(data);
	}
}
// first iteration of this function
// void	pixel_average_to_sample(t_data *data)
// {
// 	int			i;
// 	int			number_of_pixels;
// 	uint16_t	average;
//
// 	i = 0;
// 	average = 0;
// 	printf("Performing pixel average to sample operation\n");
// 	number_of_pixels = data->bmp_header.width_px * data->bmp_header.height_px;
// 	data->number_of_samples = number_of_pixels;
// 	data->wav_data = malloc(sizeof(uint16_t) * number_of_pixels);
// 	if (!data->wav_data)
// 	{
// 		printf("Error while allocating memory for wav data!\n");
// 		free_data(data);
// 	}
// 	while (i != number_of_pixels)
// 	{
// 		average = data->pixels[i].r + data->pixels[i].g + data->pixels[i].b;
// 		average /= 3;
// 		average = average * (65535 / 255);
// 		data->wav_data[i] = average;
// 		i++;
// 	}
// }
