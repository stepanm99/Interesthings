#include "incl/imgts.h"
#include <bits/types/FILE.h>
#include <stdint.h>

int	main(int argc, const char **argv)
{
	t_data	data;
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
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
	fseek(data.bmp_file, (long)data.bmp_header.offset, SEEK_SET);
	if (read_bitmap_data(&data))
		return (1);
	printf("bitmap size: %u\n", data.bmp_header.size);
	printf("image size: %u\n", data.bmp_header.image_size_bytes);
	printf("offset from the beggining of the file: %u\n", data.bmp_header.offset);
	printf("x: %i\n", data.bmp_header.width_px);
	printf("y: %i\n", data.bmp_header.height_px);

	// while (x < (data.bmp_header.width_px * data.bmp_header.height_px))
	// {
	// 	printf("r: %i\tg: %i\tb: %i\n", data.pixels[x].r, data.pixels[x].g, data.pixels[x].b);
	// 	x++;
	// }
	// x = 0;
	// while (x < ((data.bmp_header.width_px * 3) * (data.bmp_header.height_px * 3)))
	// {
	// 	printf("v: %i\n", data.bmp_data[x]);
	// 	x++;
	// }
	close_files(&data);
	free_data(&data);
	return (0);
}
