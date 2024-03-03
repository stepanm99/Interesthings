#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define PI 3.14159265358979323846

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
} WavHeader;

void writeWavHeader(FILE* file, int sampleRate, int bitsPerSample, int numChannels, int dataSize) {
    WavHeader header;

    // Prepare the WAV header
    memcpy(header.chunkId, "RIFF", 4);
    header.chunkSize = dataSize + sizeof(WavHeader) - 8;
    memcpy(header.format, "WAVE", 4);
    memcpy(header.subchunk1Id, "fmt ", 4);
    header.subchunk1Size = 16;
    header.audioFormat = 1;
    header.numChannels = numChannels;
    header.sampleRate = sampleRate;
    header.byteRate = sampleRate * numChannels * bitsPerSample / 8;
    header.blockAlign = numChannels * bitsPerSample / 8;
    header.bitsPerSample = bitsPerSample;
    memcpy(header.subchunk2Id, "data", 4);
    header.subchunk2Size = dataSize;

    // Write the header to the file
    fwrite(&header, sizeof(header), 1, file);
}

int main() {
    FILE *file = fopen("sine_wave_480Hz.wav", "wb");
    if (!file) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    // Parameters
    int frequency = 480;  // Frequency in Hz
    int duration = 120;      // Duration of the sound in seconds
    int volume = 32767;    // Amplitude

    // Sampling parameters
    int sampleRate = 44100;  // Number of samples per second
    int numChannels = 1;
    int bitsPerSample = 16;
    int numSamples = duration * sampleRate;

    // Calculate the sine wave
    double timeStep = 1.0 / sampleRate;
    for (int i = 0; i < numSamples; ++i) {
        double t = i * timeStep;
        int16_t sample = volume * sin(2 * PI * frequency * t);

        // Write the sample to the file
        fwrite(&sample, sizeof(sample), 1, file);
    }

    // Calculate data size and update header
    int dataSize = numSamples * sizeof(int16_t);
    writeWavHeader(file, sampleRate, bitsPerSample, numChannels, dataSize);

    fclose(file);

    printf("Sine wave file generated!\n");

    return 0;
}
