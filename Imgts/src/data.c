#include "../incl/imgts.h"

void	free_data(t_data *data)
{
	if (data->bmp)
		free(data->bmp);
	if (data->wav)
		free(data->wav);
}

int	open_files(t_data *data, const char **argv)
{
	data->bmp_file = fopen(argv[1], "rb");
	if (!data->bmp_file)
	{
		printf("Error opening image file!\n");
		return (1);
	}
	else
		printf("Image successfully opened!\n");
	data->wav_file = fopen(argv[2], "wb");
	if (!data->wav_file)
	{
		printf("Error creating sound file!\n");
		return (1);
	}
	return (0);
}

void	close_files(t_data *data)
{
	if (data->bmp_file)
		fclose(data->bmp_file);
	if (data->wav_file)
		fclose(data->wav_file);
}

int	read_bitmap_header(t_data *data)
{
	if (!fread(&data->bmp_header, sizeof(t_bmp_header), 1, data->bmp_file))
	{
		printf("Error while reading BMP header!\n");
		return (1);
	}
	return (0);
}

int	read_bitmap_data(t_data *data)
{
	data->bmp = malloc(data->bmp_header.size - sizeof(t_bmp_header));
	if (!data->bmp)
	{
		printf("Data allocation error!\n");
		return (1);
	}
	if (!fread(data->bmp, (data->bmp_header.size - sizeof(t_bmp_header)), 1, data->bmp_file))
	{
		printf("Error while reading BMP data!\n");
		return (1);
	}
	return (0);
}
