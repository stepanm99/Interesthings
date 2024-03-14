#include "../incl/imgts.h"

void	prepare_wav_header(t_data *data)
{
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
	fwrite(&data->wav_header, sizeof(t_wav_header), 1, data->bmp_file);
	fwrite(data->bmp_data, 2, data->number_of_samples, data->bmp_file);
}
