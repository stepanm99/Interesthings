#ifndef IMGTS_H
# define IMGTS_H

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

/*----    Data structures    ----*/

# pragma pack(push, 1)
typedef struct s_bmp_header{
	uint16_t type;				// Magic identifier: 0x4d42
	uint32_t size;				// File size in bytes
	uint16_t reserved1;			// Not used
	uint16_t reserved2;			// Not used
	uint32_t offset;			// Offset to image data in bytes from beginning of file
	uint32_t dib_header_size;	// DIB Header size in bytes
	int32_t  width_px;			// Width of the image
	int32_t  height_px;			// Height of image
	uint16_t num_planes;		// Number of color planes
	uint16_t bits_per_pixel;	// Bits per pixel
	uint32_t compression;		// Compression type
	uint32_t image_size_bytes;	// Image size in bytes
	int32_t  x_resolution_ppm;	// Pixels per meter
	int32_t  y_resolution_ppm;	// Pixels per meter
	uint32_t num_colors;		// Number of colors
	uint32_t important_colors;	// Important colors
} t_bmp_header;
# pragma pack(pop)

typedef struct s_wav_header{
	char chunkId[4];
	uint32_t chunkSize;
	char format[4];
	char subchunk1Id[4];
	uint32_t subchunk1Size;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
	char subchunk2Id[4];
	uint32_t subchunk2Size;
} t_wav_header;

typedef struct s_pixel {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_pixel;

typedef struct s_data{
	FILE			*bmp_file;
	FILE			*wav_file;
	unsigned char	*bmp_data;
	int16_t		*wav_data;
	t_pixel			*pixels;
	uint32_t		number_of_samples;
	t_bmp_header	bmp_header;
	t_wav_header	wav_header;
}	t_data;

/*----    File functions    ----*/

void	free_data(t_data *data);
int		open_files(t_data *data, const char **argv);
void	close_files(t_data *data);
int		read_bitmap_header(t_data *data);
int		read_bitmap_data(t_data *data);
void	prepare_wav_header(t_data *data);
void	write_to_wav_file(t_data *data);
void	data_init(t_data *data);

/*----    Bitmap functions    ----*/

void	get_pixel(t_pixel *pixel, t_pixel *pixel_data, int32_t x, int32_t y);

/*----    Bitmap to sound conversion functions    ----*/

void	pixel_average_to_sample(t_data *data);
void	pixel_change_average_to_sample(t_data *data);
void	pixel_average_zig_zag_to_sample(t_data *data);

#endif
