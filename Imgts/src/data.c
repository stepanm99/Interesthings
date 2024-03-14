#include "../incl/imgts.h"

void	data_init(t_data *data)
{
	data->bmp_data = NULL;
	data->bmp_file = NULL;
	data->wav_data = NULL;
	data->wav_file = NULL;
	data->pixels = NULL;
}

void	free_data(t_data *data)
{
	if (data->bmp_data)
		free(data->bmp_data);
	if (data->wav_data)
		free(data->wav_data);
	if (data->pixels)
		free(data->pixels);
}

int	open_files(t_data *data, const char **argv)
{
	printf("Opening/creating files\n");
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
	printf("Reading bitmap header\n");;
	if (!fread(&data->bmp_header, sizeof(t_bmp_header), 1, data->bmp_file))
	{
		printf("Error while reading BMP header!\n");
		return (1);
	}
	if (data->bmp_header.height_px < 0)
		data->bmp_header.height_px *= (-1);
	if (data->bmp_header.width_px < 0)
		data->bmp_header.width_px *= (-1);
	return (0);
}

int	read_bitmap_data(t_data *data)
{
	int32_t	x;
	int32_t	y;
	int32_t	row;
	int32_t	padding;

	x = 0;
	y = 0;
	row = (data->bmp_header.width_px * 3 + 3) & ~3;
	padding = row - (data->bmp_header.width_px * 3);

	printf("Reading bitmap data\n");
	data->bmp_data = malloc(row * data->bmp_header.height_px);
	if (!data->bmp_data)
	{
		printf("Error while allocating memory for bmp_data!\n");
		return (-1);
	}
	data->pixels = malloc(sizeof(t_pixel) * (data->bmp_header.width_px * data->bmp_header.height_px));
	if (!data->pixels)
	{
		printf("Error while allocating memory for pixels!\n");
		return (-1);
	}

	fseek(data->bmp_file, data->bmp_header.offset, SEEK_SET);

	while (y < data->bmp_header.height_px)
	{
		while (x < data->bmp_header.width_px)
		{
			fread(&data->bmp_data[(y * row) + (x * 3)], 3, 1, data->bmp_file);
			x++;
		}
		fseek(data->bmp_file, padding, SEEK_CUR);
		x = 0;
		y++;
	}

	x = 0;
	y = 0;

	while (x < (data->bmp_header.width_px * data->bmp_header.height_px * 3))
	{
		data->pixels[y].b = data->bmp_data[x];
		data->pixels[y].g = data->bmp_data[x + 1];
		data->pixels[y].r = data->bmp_data[x + 2];
		y++;
		x += 3;
	}

	free(data->bmp_data);
	data->bmp_data = NULL;

	return (0);
}


/*
int	read_bitmap_data(t_data *data)
{
	int32_t			i;
	int32_t			j;
	int32_t			k;
	int32_t			x;
	int32_t			y;
	int32_t			padded_row;
	unsigned char	*temp;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	k = 0;
	padded_row = (data->bmp_header.width_px * 3 + 3) & (~3);
	printf("Padded row: %i\n", padded_row);

	data->bmp_data = malloc(data->bmp_header.size - sizeof(t_bmp_header));
	if (!data->bmp_data)
	{
		printf("BMP data allocation error!\n");
		return (1);
	}

	if (!fread(data->bmp_data, (data->bmp_header.size - sizeof(t_bmp_header)), 1, data->bmp_file))
	{
		printf("Error while reading BMP data!\n");
		return (1);
	}

	data->pixels = malloc(sizeof(t_pixel) * (data->bmp_header.width_px * data->bmp_header.height_px));
	if (!data->pixels)
	{
		printf("Pixels allocation error!\n");
		return (1);
	}

	temp = malloc(padded_row + 1);
	if (!temp)
	{
		printf("Temp allocation error!\n");
		return (1);
	}

	while (i != padded_row * (y + 1))
	{
		temp[j] = data->bmp_data[i];
		i++;
		j++;
	}
	j = 0;
	while (x != (data->bmp_header.width_px * 3) && (x + 3) >= (data->bmp_header.width_px * 3))
	{
		data->pixels[k].b = temp[x];
		data->pixels[k].g = temp[x + 1];
		data->pixels[k].r = temp[x + 2];
		x += 3;
		k++;
	}
	x = 0;
	y++;

	while (y != data->bmp_header.height_px)
	{
		while (i != padded_row * (y + 1))
		{
			temp[j] = data->bmp_data[i];
			i++;
			j++;
		}
		j = 0;
		while (x != (data->bmp_header.width_px * 3) && (x + 3) >= (data->bmp_header.width_px * 3))
		{
			data->pixels[k].b = temp[x];
			data->pixels[k].g = temp[x + 1];
			data->pixels[k].r = temp[x + 2];
			printf("r: %i\n", temp[x+2]);
			x += 3;
			k++;
		}
		x = 0;
		y++;
	}
	free(temp);
	return (0);
}
*/
