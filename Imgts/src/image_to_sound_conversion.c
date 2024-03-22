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

void	pixel_change_average_to_sample(t_data *data)
{
	int			i;
	int			number_of_pixels;
	int16_t		average;
	int16_t		last;

	i = 0;
	average = 0;
	last = 0;
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
		data->wav_data[i] = average - last;
		last = average;
		i++;
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
