#include "incl/imgts.h"
#include <bits/types/FILE.h>
#include <stdint.h>

void	print_pixels(t_data *data)
{
	int32_t	x;
	int32_t	y;
	t_pixel	pixel;

	x = 0;
	y = 0;
	while (1)
	{
		while (1)
		{
			get_pixel(&pixel, data->pixels, x, y);
			printf("%i\t%i\t%i", pixel.r, pixel.g, pixel.b);
			x++;
			if (x != data->bmp_header.width_px)
			{
				printf("\t|\t");
			}
			else
			{
				printf("\n");
				break ;
			}
		}
		x = 0;
		y++;
		if (y == data->bmp_header.height_px)
			break ;
	}
}

int	main(int argc, const char **argv)
{
	t_data	data;
	// int32_t	x;
	// int32_t	y;
 //
	// x = 0;
	// y = 0;
	data_init(&data);
	printf("argc: %i\n", argc);
	if (argc != 3)
	{
		printf("Wrong arguments!\n./imgts input.bmp output.wav\n");
		return (1);
	}
	if (open_files(&data, argv))
		return (1);
	if (read_bitmap_header(&data))
		return (1);
	if (read_bitmap_data(&data))
		return (1);
	printf("bitmap size: %u\n", data.bmp_header.size);
	printf("image size: %u\n", data.bmp_header.image_size_bytes);
	printf("offset from the beggining of the file: %u\n", data.bmp_header.offset);
	printf("x: %i\n", data.bmp_header.width_px);
	printf("y: %i\n", data.bmp_header.height_px);

	// while (x < (data.bmp_header.width_px * data.bmp_header.height_px))
	// {
	// 	printf("pixel nr: %i\tr: %i\tg: %i\tb: %i\n", x, data.pixels[x].r, data.pixels[x].g, data.pixels[x].b);
	// 	x++;
	// }
	// x = 0;
	// print_pixels(&data);
	// while (x < ((data.bmp_header.width_px * 3) * (data.bmp_header.height_px * 3)))
	// {
	// 	printf("v: %i\n", data.bmp_data[x]);
	// 	x++;
	// }

	pixel_average_to_sample(&data);
	prepare_wav_header(&data);
	write_to_wav_file(&data);
	close_files(&data);
	free_data(&data);
	return (0);
}
