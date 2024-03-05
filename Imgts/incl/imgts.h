#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

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

typedef struct {
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

typedef struct s_data{
	FILE			*bmp_file;
	FILE			*wav_file;
	void			*bmp;
	void			*wav;
	t_bmp_header	bmp_header;
	t_wav_header	wav_header;
}	t_data;

/*----    File operations    ----*/

int		open_files(t_data *data, const char **argv);
void	close_files(t_data *data);
