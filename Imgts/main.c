#include "incl/imgts.h"
#include <bits/types/FILE.h>

int	main(int argc, const char **argv)
{
	t_data	data;

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
	printf("bitmap size: %u\n", data.bmp_header.size);
	printf("x: %i\n", data.bmp_header.width_px);
	printf("y: %i\n", data.bmp_header.height_px);
	close_files(&data);
	return (0);
}
