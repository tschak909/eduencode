/* Test Harness */
 
#include "eduencode.h"
#include <stdio.h>
 
int main(int argc, char* argv[])
{
  FILE* fp = edu_open_file("test_eduencode.wav");
 
  edu_write_string(fp,"------------------------------\r\r");
  edu_write_string(fp,"This is an example tape being\r");
  edu_write_string(fp,"Written by the ");
  edu_write_hilight_string(fp," eduencode \r");
  edu_write_string(fp,"library; Released as free\r");
  edu_write_string(fp,"software under the protections\r");
  edu_write_string(fp,"of v3 of the");
  edu_write_hilight_string(fp," GNU Public License ");
  edu_write_string(fp,"\r\r");
  edu_write_hilight_color(fp,HILIGHT_DARK_RED);
  edu_write_pause(fp,600);
  edu_write_hilight_color(fp,HILIGHT_RED);
  edu_write_pause(fp,600);
  edu_write_hilight_color(fp,HILIGHT_BROWN);
  edu_write_pause(fp,600);
  edu_write_hilight_color(fp,HILIGHT_GREEN);
  edu_write_pause(fp,600);
  edu_write_pause(fp,6000);
 
  edu_write_colors(fp,BACKGROUND_GREEN,BORDER_GREEN,HILIGHT_RED);
 
  edu_write_clear(fp);
 
  edu_write_string(fp,"This code can be used to both\r");
  edu_write_string(fp,"create new Atari Educational\r");
  edu_write_string(fp,"System tapes,");
  edu_write_pause(fp,400);
  edu_write_string(fp,"as well as\r");
  edu_write_string(fp,"Provide a historical study of\r");
  edu_write_string(fp,"The tape format, ");
  edu_write_pause(fp,350);
  edu_write_string(fp,"which, ");
  edu_write_pause(fp,150);
  edu_write_string(fp,"along\r");
  edu_write_string(fp,"with the documentation of the\r");
  edu_write_string(fp,"Master Cartridge, and its \r");
  edu_write_string(fp,"disassembly,");
  edu_write_pause(fp,450);
  edu_write_string(fp," serve as a \r");
  edu_write_string(fp,"complete curated exhibit of\r");
  edu_write_string(fp,"this form of computer based\r");
  edu_write_string(fp,"education.\r");
  edu_write_pause(fp,6000);
 
  edu_write_colors(fp,BACKGROUND_BROWN,BORDER_BROWN,HILIGHT_MAGENTA);
  edu_write_clear(fp);
 
  edu_write_hilight_string(fp," eduencode ");
  edu_write_string(fp," outputs a\r");
  edu_write_string(fp,"standard WAV file, which can be\r");
  edu_write_string(fp,"read by a variety of audio pro-\r");
  edu_write_string(fp,"grams to be able to be written\r");
  edu_write_string(fp,"to a cassette tape, and certain\r");
  edu_write_string(fp,"emulators, such as Altirra, can\r");
  edu_write_string(fp,"play these tapes, in emulation.\r");
  edu_write_pause(fp,8000);
 
  edu_write_colors(fp,BACKGROUND_BROWN,BORDER_BROWN,HILIGHT_GREEN);
  edu_write_clear(fp);
 
  edu_write_string(fp,"This tape was written using the ");
  edu_write_hilight_string(fp," eduencode ");
  edu_write_string(fp," library\r");
  edu_write_string(fp," functions, such as:\r\r");
  edu_write_hilight_string(fp,"-------------------------------\r");
  edu_write_hilight_string(fp,"| edu_write_string(fp,'Hi');  |\r");
  edu_write_hilight_string(fp,"| edu_write_pause(fp,5000);   |\r");
  edu_write_hilight_string(fp,"| edu_write_correct_answer... |\r");
  edu_write_hilight_string(fp,"| ...                         |\r");
  edu_write_hilight_string(fp,"-------------------------------\r");  
  edu_write_pause(fp,7000);
 
  edu_write_colors(fp,BACKGROUND_BLUE,BORDER_GREEN,HILIGHT_RED);
  edu_write_clear(fp);
 
  edu_write_string(fp,"What license is ");
  edu_write_hilight_string(fp," eduencode ");
  edu_write_string(fp,"\rlicensed");
  edu_write_string(fp," under?");
  edu_write_correct_answer(fp,ANSWER_3);
  edu_write_string(fp,"\r\r");
  edu_write_string(fp,"  GPL         GPL          GPL\r");
  edu_write_string(fp,"  v.1         v.2          v.3\r");
  edu_write_wait_for_answer(fp);
  edu_write_colors(fp,BACKGROUND_GREEN,BORDER_GREEN,HILIGHT_RED);
  edu_write_string(fp,"------------------------------\r\r");
  edu_write_string(fp,"  Yes, that's correct.");
  edu_write_pause(fp,3000);
 
  edu_write_clear(fp);
 
  edu_write_string(fp,"Thank you for testing this. The\r");
  edu_write_string(fp,"author also wishes to thank\r");
  edu_write_string(fp,"AtariAge, and the Atari\r");
  edu_write_string(fp,"Community for their\r");
  edu_write_string(fp,"encouragement and support on\r"); 
  edu_write_string(fp,"this project.\r\r\r");
 
  edu_write_pause(fp,5000);
 
  edu_write_string(fp,"       end of tape.");
 
  edu_close_file(fp);
  return 0;
}
