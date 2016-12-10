/* eduencode.c - Routines to create Atari Educational System tapes */
/* Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>         */
 
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
#include "eduencode.h"
 
#define FALSE 0
#define TRUE 1
#define SAMPLE_RATE 44100            /* Output Sample Rate */
#define HZ_MARK 5327                 /* Mark Frequency */
#define HZ_SPACE 3995                /* Space Frequency */
#define SECS_LEADER 4                /* Leader time in seconds */
#define NUM_CHANNELS 1               /* output channels - 1 */
#define BUFFER_SIZE 74               /* buffer size for a single 600 baud bit transition. */
#define AMPLITUDE 16384              /* amplitude for samples, right now at half volume. */
#define LEFT_CHANNEL 0               /* Lower 16 bits = Left Channel */
#define RIGHT_CHANNEL 16             /* Upper 16 bits = right channel */
#define BYTES_PER_SAMPLE 4           /* 16-bit samples, 2 channels */
#define BITS_PER_SAMPLE 16           /* Therefore 32 bits per total sample */
#define BYTE_RATE 176400             /* how many bytes per second, data rate */
#define HEADER_LENGTH 36             /* The RIFF WAVE file header is 36 bytes total */

/* globals */
int32_t edu_data_len = 0;
float phase=0;

int edu_write_leader(FILE* fp)
{
  int i;
  float amplitude = AMPLITUDE;
  float freq_hz = HZ_MARK;
  float phase=0;
  int buffer_size = SAMPLE_RATE * NUM_CHANNELS * SECS_LEADER;
  float freq_radians_per_sample = freq_hz*2*M_PI/SAMPLE_RATE;
  int32_t buffer[buffer_size];
 
  for (i=0;i<buffer_size;i++)
    {
      if (phase > M_PI)
phase = (phase - (2*M_PI));
      phase += freq_radians_per_sample;
      buffer[i] = (int32_t)(amplitude*sin(phase)) << RIGHT_CHANNEL; /* << 16 ensures right channel. */
    }
 
  if (fwrite(&buffer,sizeof(int32_t),buffer_size,fp) != buffer_size)
    {
      return FALSE;
    }
 
  edu_data_len=edu_data_len+(sizeof(int32_t)*buffer_size);
 
  return TRUE;
}
 
int edu_write_wav_header(FILE* fp, int32_t len)
{
  int32_t total_len = HEADER_LENGTH+len;
  int32_t subchunk_size = 16;
  int16_t format = 1;
  int16_t num_channels = 2;
  int32_t sample_rate = SAMPLE_RATE;
  int32_t byte_rate = BYTE_RATE;
  int16_t bytes_per_sample = BYTES_PER_SAMPLE;
  int16_t bits_per_sample = BITS_PER_SAMPLE;
 
  fwrite("RIFF",1,4,fp);
  fwrite(&total_len,sizeof(int32_t),1,fp); // Write total length
  fwrite("WAVE",1,4,fp); // Write WAVE subpart
  fwrite("fmt ",1,4,fp); // write fmt subpart
  fwrite(&subchunk_size,sizeof(int32_t),1,fp); // subchunk size is 16.
  fwrite(&format,sizeof(int16_t),1,fp); // PCM is format 1
  fwrite(&num_channels,sizeof(int16_t),1,fp); // num channels = 2
  fwrite(&sample_rate,sizeof(int32_t),1,fp); // 44100hz sample rate
  fwrite(&byte_rate,sizeof(int32_t),1,fp); // byte rate is 176400
  fwrite(&bytes_per_sample,sizeof(int16_t),1,fp); // 2 bytes per sample
  fwrite(&bits_per_sample,sizeof(int16_t),1,fp); // 32 bits per sample.
  fwrite("data",1,4,fp); // data chunk
  fwrite(&len,sizeof(int32_t),1,fp); // data length
  return TRUE; // FIXME TODO: Come back here and do some fucking error handling.
}
 
FILE *edu_open_file(const char* filename)
{
  FILE* fp;
  fp = fopen(filename,"wb");
 
  edu_data_len=0;
  if (edu_write_wav_header(fp,0) == FALSE)
    return NULL;
 
  if (edu_write_leader(fp) == FALSE)
    return NULL;
 
  return fp;
}
 
int edu_close_file(FILE* fp)
{
  fseek(fp,0,SEEK_SET);
  edu_write_wav_header(fp,edu_data_len); // Update header now that we have total length.
  fseek(fp,0,SEEK_END);
  fclose(fp);
  return TRUE;
}
 
int edu_write_baud(FILE* fp, float freq_hz)
{
  int i;
  float amplitude = AMPLITUDE;
  int buffer_size = BUFFER_SIZE;
  float freq_radians_per_sample = freq_hz*2*M_PI/SAMPLE_RATE;
  int32_t buffer[buffer_size];
 
  for (i=0;i<buffer_size;i++)
    {
      if (phase > M_PI)
phase = (phase - (2*M_PI));
      phase += freq_radians_per_sample;
      buffer[i] = (int32_t)(amplitude*sin(phase)) << RIGHT_CHANNEL; /* << 16 ensures right channel. */
    }
 
  if (fwrite(&buffer,sizeof(int32_t),buffer_size,fp) != buffer_size)
    {
      return FALSE;
    }
 
  edu_data_len=edu_data_len+(sizeof(int32_t)*buffer_size);
 
  return TRUE;  
}
 
int edu_write_mark(FILE* fp)
{
  return edu_write_baud(fp,HZ_MARK);
}
 
int edu_write_space(FILE* fp)
{
  return edu_write_baud(fp,HZ_SPACE);
}
 
int edu_write_start_bit(FILE* fp)
{
  return edu_write_space(fp);
}
 
int edu_write_stop_bit(FILE* fp)
{
  return edu_write_mark(fp);
}
 
int edu_write_byte(FILE* fp, unsigned char b)
{
  int i=0;
  if (edu_write_start_bit(fp) == FALSE)
    return FALSE;
 
  b = b ^ 0xFF; // XOR the byte with $FF, invert all bits as specified.
  
  for (i=0; i<8; i++)
    {
      if (b & (1<<i))
{
  if (edu_write_mark(fp) == FALSE)
    return FALSE;
}
      else
{
  if (edu_write_space(fp) == FALSE)
    return FALSE;
}
    }
 
  if (edu_write_stop_bit(fp) == FALSE)
    return FALSE;
 
  return TRUE;
}
 
int edu_write_string(FILE* fp, const char* text)
{
  int buffer_size = strlen(text);
  int i=0;
 
  for (i=0; i<buffer_size; i++)
    {
      if (edu_write_byte(fp,text[i]) == FALSE)
return FALSE;
      if (edu_write_byte(fp,0) == FALSE)
return FALSE;
    }
  return TRUE;
}
 
int edu_write_hilight_string(FILE* fp, const char* text)
{
  int buffer_size = strlen(text);
  int i=0;
 
  for (i=0; i<buffer_size; i++)
    {
      if (edu_write_byte(fp,(text[i] | 0x80)) == FALSE)
return FALSE;
      if (edu_write_byte(fp,0) == FALSE)
return FALSE;
    }
  
  return TRUE;  
}
 
int edu_write_pause(FILE* fp, int ms)
{
  int num_of_nulls = ms * .06;
  int i=0;
 
  for (i=0; i<num_of_nulls;i++)
    {
      if (edu_write_byte(fp,0) == FALSE)
{
  return FALSE;
}
    }
  return TRUE;
}
 
int edu_write_clear(FILE* fp)
{
  return edu_write_byte(fp,0x03);
}
 
int edu_write_hilight_blink_off(FILE* fp)
{
  return edu_write_byte(fp,0x02);
}
 
int edu_write_hilight_blink_on(FILE *fp)
{
  return edu_write_byte(fp,0x05);
}
 
int edu_write_background_color(FILE *fp, BackgroundColor backgroundColor)
{
  return edu_write_byte(fp,backgroundColor);
}
 
int edu_write_border_color(FILE *fp, BorderColor borderColor)
{
  return edu_write_byte(fp,borderColor);
}
 
int edu_write_hilight_color(FILE *fp, HilightColor hilightColor)
{
  return edu_write_byte(fp,hilightColor);
}
 
int edu_write_colors(FILE *fp, BackgroundColor backgroundColor, BorderColor borderColor, HilightColor hilightColor)
{
  edu_write_background_color(fp,backgroundColor);
  edu_write_border_color(fp,borderColor);
  edu_write_hilight_color(fp,hilightColor);
  return TRUE;
}
 
int edu_write_correct_answer(FILE *fp, CorrectAnswer answer)
{
  return edu_write_byte(fp,answer);
}
 
int edu_write_wait_for_answer(FILE *fp)
{
  return edu_write_byte(fp,0x84);
}

