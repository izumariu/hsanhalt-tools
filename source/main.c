#include <stdio.h>
#include <stdlib.h>
#include <switch.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <math.h>
#define MS_US(ms) 1000 * ms
#define TITLE_OFFSET 60
#define LECTURER_OFFSET TITLE_OFFSET+50
#define TIME_OFFSET (scr_bounds[1]/2) - ((27*10)/2)
//#define TIMETEXT_OFFSET TIME_OFFSET+305

uint8_t *fbuf;
uint32_t scr_bounds[2] = {0,0};
char *sched = 0;
long schedlen;

extern int *fontchar;
extern uint32_t hsanhalttools_wdth, hsanhalttools_hght, hsanhalttools_bg_crop_png_offset[2], hsanhalttools_bg_crop_png_colors[4];
extern uint8_t hsanhalttools_bg_crop_png[456][664], fcw;
void drawScreen();
void drawPixel(uint32_t, uint32_t, uint8_t, uint8_t, uint8_t);
void drawRect(uint32_t, uint32_t, uint32_t, uint32_t, uint8_t,
  uint8_t, uint8_t);
void drawBackground();
void drawTextAtOffset(int, int, char*, uint8_t);
void drawCenteredTextAtOffset(int, char*, uint8_t);
void findNextStart(time_t now);
int readSchedule(char*);
void scheduleError(int);
//double log_bin(double);

int main() {

  socketInitializeDefault();
  nxlinkStdio();
  gfxInitDefault();
  fbuf = gfxGetFramebuffer(&scr_bounds[0], &scr_bounds[1]);

  int schedRes = readSchedule("/hsanhalt/timetable.sched");

  if(schedRes != 0) {
    scheduleError(schedRes);
    while(appletMainLoop()) {
      hidScanInput();
      if(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break;
    }
    goto _exit;
  }

  char* remainingTime = malloc(sizeof(char)*6);

  uint32_t timeleft_i = 9000;

  while(appletMainLoop()) {

    uint32_t start = 1540188000ul;
    time_t unixTime = time(NULL);
    struct tm* timeStruct = gmtime((const time_t*) &unixTime);
    //printf("\x1b[2;1HCurrent time in Koethen is %02i:%02i:%02i | %0lu", (timeStruct->tm_hour + 2), timeStruct->tm_min, timeStruct->tm_sec, unixTime);

    time_t timeLeftUT = start - unixTime;
    struct tm* timeLeft = gmtime((const time_t*) &timeLeftUT);
    //printf("\x1b[3;1HTime left until 2018-10-22 08:00:00 -> %02i:%02i:%02i", timeLeft->tm_hour, timeLeft->tm_min, timeLeft->tm_sec);

    usleep(100); // just so we dont use 100% of the cpu lol

    hidScanInput();
    if(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break;

    sprintf(remainingTime, "%02i:%02i\0", timeleft_i / 100, timeleft_i % 100);

    drawBackground();
    drawCenteredTextAtOffset(TITLE_OFFSET, "VORLESUNG: MEDIENGESTALTUNG\0", 4); // 18 chars ideal!
    drawCenteredTextAtOffset(LECTURER_OFFSET, "PROF. DR. STEFAN SCHLECHTWEG\0", 3);
    drawCenteredTextAtOffset(TIME_OFFSET, remainingTime, 27);

    #ifdef TIMETEXT_OFFSET
    drawCenteredTextAtOffset(TIMETEXT_OFFSET, "MINUTEN VERBLEIBEN\0", 3);
    #endif

    drawScreen();
    usleep(MS_US(1000));

    if(timeleft_i == 0) timeleft_i = 9000;
    else if(timeleft_i % 100 == 0) timeleft_i -= 41;
    else timeleft_i--;

  }

  _exit:

  gfxExit();
  socketExit();

  return 0;

}

//////////////////////////////////////////////

void drawScreen() {
  gfxFlushBuffers();
  gfxSwapBuffers();
  gfxWaitForVsync();
}

void drawPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
  if(x < 0 || y < 0 || x >= 1280 || y >= 720) return;

  fbuf[(y*1280+x)*4+0] = r;
  fbuf[(y*1280+x)*4+1] = g;
  fbuf[(y*1280+x)*4+2] = b;
  fbuf[(y*1280+x)*4+3] = 0xFF;
}

void drawRect(uint32_t x, uint32_t y, uint32_t xt_x, uint32_t xt_y, uint8_t cr,
  uint8_t cg, uint8_t cb) {

  if (x+xt_x > 1280 || y+xt_y > 720) return;

  printf("Drawing rectangle at ( %4u | %4u ) with size %4u x %4u\n", x, y, xt_x, xt_y);

  for (int r = y; r <= y+xt_y; r++) {
    for (int c = x; c <= x+xt_x; c++) {
      drawPixel(c, r, cr, cg, cb);
    }
  }

}

void drawBackground() {

  drawRect(
    0,  0, 1280, 720,
    hsanhalttools_bg_crop_png_colors[0] >> 24,
    (hsanhalttools_bg_crop_png_colors[0] >> 16) % 256,
    (hsanhalttools_bg_crop_png_colors[0] >> 8) % 256
  );

  uint32_t offset_x = hsanhalttools_bg_crop_png_offset[0];
  uint32_t offset_y = hsanhalttools_bg_crop_png_offset[1];

  for(uint32_t y = 0; y < hsanhalttools_hght; y++) {
    for(uint32_t x = 0; x < hsanhalttools_wdth; x++) drawPixel(
      offset_x+x, offset_y+y,
      hsanhalttools_bg_crop_png_colors[hsanhalttools_bg_crop_png[x][y]] >> 24,
      (hsanhalttools_bg_crop_png_colors[hsanhalttools_bg_crop_png[x][y]] >> 16) % 256,
      (hsanhalttools_bg_crop_png_colors[hsanhalttools_bg_crop_png[x][y]] >> 8) % 256
    );
  }

}

void drawTextAtOffset(int x, int y, char *text, uint8_t mult) {

  int cx = x;
  int i = 0;

  while( text[i] != '\0' ) {
    allocFontChar(text[i], mult);
    for(int iy = 0; iy < 10*mult; iy++) {

      uint32_t val = 128;

      for(int i_cx = 0; i_cx < 7*mult; i_cx++) {
        if( (fontchar[iy] & val) != 0)
          drawPixel(cx+i_cx, y+iy, 0x00, 0x00, 0x00);
        if (i_cx % mult == 0) val /= 2;
      }

    }
    cx += 7 * mult + 2;
    i++;
  }

}

void drawCenteredTextAtOffset(int y, char *text, uint8_t mult) {

  uint8_t wdth = 7 * mult, sphz = 2;

  uint32_t text_width = 0;
  uint8_t i = 0;

  while(text[i] != '\0') {
    text_width += wdth + sphz;
    i++;
  }

  // because the first character doesn't have spacing in front of it:
  text_width -= sphz;

  uint32_t x_offset = (1280 / 2) - (text_width / 2);

  drawTextAtOffset(x_offset, y, text, mult);

}

void findNextStart(time_t now) {

}

int readSchedule(char* path) {

  FILE *f = fopen(path, "r");
  if(f == NULL) return 1;

  printf("fseek(f, 0, SEEK_END);\n");
  fseek(f, 0, SEEK_END);
  printf("length = ftell(f);\n");
  schedlen = ftell(f);
  printf("fseek(f, 0, SEEK_SET);\n");
  fseek(f, 0, SEEK_SET);
  printf("sched = malloc(length);\n");
  sched = malloc(schedlen);
  printf("if(sched == NULL) return 2;\n");
  if(sched == NULL) return 2;
  printf("fread(sched, 1, length, f);\n");
  fread(sched, 1, schedlen, f);
  printf("fclose(f);\n");
  fclose(f);

  return 0;
}

void scheduleError(int err) {
  drawBackground();
  char *error = malloc(sizeof(char) * 27);
  uint32_t offset = (720/2)-((2*4*10 + 1*5)/2);
  uint32_t offset2= offset + 5 + 4*10;

  switch(err) {
    case 1:
      drawCenteredTextAtOffset(offset, "ERROR1: COULD NOT FIND TIMETABLE.SCHED\0", 4);
      break;
    case 2:
      drawCenteredTextAtOffset(offset, "ERROR2: COULD NOT ALLOCATE FILESTRING\0", 4);
      break;
    default:
      sprintf(error, "ERROR%i: UNKNOWN ERROR\0", err);
      drawCenteredTextAtOffset(offset, error, 4);
      break;
  }
  drawCenteredTextAtOffset(offset2, "PRESS PLUS TO EXIT...\0", 4);
  drawScreen();
}
