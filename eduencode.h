/* eduencode.c - Routines to create Atari Educational System tapes */
/* Author: Thomas Cherryhomes <thom.cherryhomes@gmail.com>         */
 
#include <stdio.h>
 
enum BackgroundColorEnum { BACKGROUND_DARK_RED=0x19, BACKGROUND_MAGENTA=0x1A, BACKGROUND_RED=0x1b, BACKGROUND_BROWN=0x1c, BACKGROUND_GREEN=0x1d, BACKGROUND_BLUE=0x1e };
typedef enum BackgroundColorEnum BackgroundColor;
 
enum BorderColorEnum { BORDER_DARK_RED=0x11, BORDER_MAGENTA=0x12, BORDER_RED=0x13, BORDER_BROWN=0x14, BORDER_GREEN=0x15, BORDER_BLUE=0x16 };
typedef enum BorderColorEnum BorderColor;
 
enum HilightColorEnum { HILIGHT_DARK_RED=0x99, HILIGHT_MAGENTA=0x9A, HILIGHT_RED=0x9B, HILIGHT_BROWN=0x9C, HILIGHT_GREEN=0x9d, HILIGHT_BLUE=0x9E };
typedef enum HilightColorEnum HilightColor;
 
enum CorrectAnswerEnum { ANSWER_1=0x08, ANSWER_2=0x09, ANSWER_3=0x0A };
typedef enum CorrectAnswerEnum CorrectAnswer;
 
FILE *edu_open_file(const char* filename);
int edu_close_file(FILE* fp);
int edu_write_byte(FILE* fp, unsigned char b);
int edu_write_string(FILE* fp, const char* text);
int edu_write_hilight_string(FILE* fp, const char* text);
int edu_write_pause(FILE* fp, int ms);
int edu_write_clear(FILE* fp);
int edu_write_hilight_blink_off(FILE* fp);
int edu_write_hilight_blink_on(FILE *fp);
int edu_write_background_color(FILE *fp, BackgroundColor backgroundColor);
int edu_write_border_color(FILE *fp, BorderColor borderColor);
int edu_write_hilight_color(FILE *fp, HilightColor hilightColor);
int edu_write_colors(FILE *fp, BackgroundColor backgroundColor, BorderColor borderColor, HilightColor hilightColor);
int edu_write_correct_answer(FILE *fp, CorrectAnswer answer);
int edu_write_wait_for_answer(FILE *fp);
