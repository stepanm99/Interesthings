#include "../incl/imgts.h"

void	print_samples(t_data *data)
{
	int	i;

	i = 0;
	while (i != data->number_of_samples)
	{
		printf(" |%i| ", data->wav_data[i]);
		i++;
	}
}

void	prepare_wav_header(t_data *data)
{
	printf("Preparing wav file header\n");
	memcpy(data->wav_header.chunkId, "RIFF", 4);
	data->wav_header.chunkSize = 36 + (sizeof(uint16_t) * data->number_of_samples);
	memcpy(data->wav_header.format, "WAVE", 4);
	memcpy(data->wav_header.subchunk1Id, "fmt ", 4);
	data->wav_header.subchunk1Size = 16;
	data->wav_header.audioFormat = 1;
	data->wav_header.numChannels = 1;
	data->wav_header.sampleRate = 44100;
	data->wav_header.byteRate = 44100 * 2;
	data->wav_header.bitsPerSample = 16;
	memcpy(data->wav_header.subchunk2Id, "data", 4);
	data->wav_header.subchunk2Size = sizeof(uint16_t) * data->number_of_samples;
}


void	write_to_wav_file(t_data *data)
{
	size_t	ret;

	ret = 0;
	printf("Writing data to wav file\n");
	print_samples(data);
	ret += fwrite(&data->wav_header, sizeof(t_wav_header), 1, data->wav_file);
	ret += fwrite(&data->bmp_data, 2 * data->number_of_samples, 1, data->wav_file);
	printf("\nWritten file size: %zu\n", ret);
}
