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
	close_files(&data);
	return (0);
}
