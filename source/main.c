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
void findNextStart();
int readSchedule(char*);
void scheduleError(int);
void showTimeUntilNextLecture();
int lectureRunning = 0;

struct __lecture_struct__ {
  char title[42];
  char lecturer[54];
  uint32_t start;
  uint32_t end;
};

struct __lecture_struct__ nextLecture;

int main() {

  socketInitializeDefault();
  nxlinkStdio();
  gfxInitDefault();
  fbuf = gfxGetFramebuffer(&scr_bounds[0], &scr_bounds[1]);

  nextLecture.start = 0;
  nextLecture.end = 0;

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

  while(appletMainLoop()) {

    findNextStart();

    if(nextLecture.end == 0) {

      showTimeUntilNextLecture();
      goto _end_of_mainloop_;

    }

    time_t now = time(NULL);
    time_t timeLeftUT = difftime(nextLecture.end, now);

    struct tm* timeLeft = gmtime((const time_t*) &timeLeftUT);

    sprintf(remainingTime, "%02i:%02i\0", (timeLeft->tm_hour * 60 + timeLeft->tm_min), timeLeft->tm_sec);

    drawBackground();
    drawCenteredTextAtOffset(TITLE_OFFSET, nextLecture.title, 4); // 42 chars max
    drawCenteredTextAtOffset(LECTURER_OFFSET, nextLecture.lecturer, 3); // 54 chars max
    drawCenteredTextAtOffset(TIME_OFFSET, remainingTime, 27);

    #ifdef TIMETEXT_OFFSET
    drawCenteredTextAtOffset(TIMETEXT_OFFSET, "MINUTEN VERBLEIBEN\0", 3);
    #endif

    drawScreen();

    _end_of_mainloop_:

    hidScanInput();
    if(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break;
    usleep(MS_US(100)); // just so we dont use 100% of the cpu lol

  }

  _exit:

  gfxExit();
  socketExit();

  return 0;

}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


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

  //printf("Drawing rectangle at ( %4u | %4u ) with size %4u x %4u\n", x, y, xt_x, xt_y);

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

void findNextStart() {

  struct __lecture_struct__ selectedLecture;

  unsigned short chunk_size = 112;

  time_t now = time(NULL);
  //printf("SCHEDLEN %% chunk_size = %li\n", schedlen % chunk_size);

  if((difftime(nextLecture.start, now) <= 0 && difftime(nextLecture.end, now) > 0)) return;
  printf("No lecture currently running(or not detected).\n");

  if(schedlen % chunk_size != 0) {
    nextLecture.start = 0;
    nextLecture.end = 0;
    return;
  }

  /*
    lectures are chunks of {chunk_size}(112) bytes:
    8 bytes for start and end (both unix time)
    + 42 bytes for lecture name (padded with zerobytes)
    + 54 bytes for lecturer name (padded with zerobytes)
    + 8 bytes for room name (padded with zerobytes(if neccessary))
  */

  uint32_t offset = 0;
  uint8_t lectureFound = 0;

  do {

    selectedLecture.start = (sched[offset + 0] << 24)
      + (sched[offset + 1] << 16)
      + (sched[offset + 2] << 8)
      + (sched[offset + 3]);
    selectedLecture.end = (sched[offset + 4] << 24)
      + (sched[offset + 5] << 16)
      + (sched[offset + 6] << 8)
      + (sched[offset + 7]);

    for(int i = 0; i < 42; i++) selectedLecture.title[i] = sched[offset+8+i];
    for(int i = 0; i < 54; i++) selectedLecture.lecturer[i] = sched[offset+50+i];

    printf(
      "Found lecture by '%s': '%s' at timestamp %u | DIFFTIME: %i\n",
      selectedLecture.lecturer,
      selectedLecture.title,
      selectedLecture.start,
      (int)difftime(selectedLecture.start, now)
    );

    if(difftime(selectedLecture.start, now) <= 0 && difftime(selectedLecture.end, now) > 0) {
      lectureFound = 1;
      break;
    }

    offset += 112;

  } while((schedlen - 1 > offset) && !(difftime(selectedLecture.start, now) <= 0 && difftime(selectedLecture.end, now) > 0));

  if(lectureFound == 1) {
    for(int i = 0; i < 42; i++) nextLecture.title[i] = selectedLecture.title[i];
    for(int i = 0; i < 54; i++) nextLecture.lecturer[i] = selectedLecture.lecturer[i];
    nextLecture.start = selectedLecture.start;
    nextLecture.end = selectedLecture.end;
    printf(
      "NEXT Lecture by '%s': '%s' at timestamp %u < %lu < %u\n",
      nextLecture.lecturer,
      nextLecture.title,
      nextLecture.start,
      now,
      nextLecture.end
    );
  } else {
    nextLecture.start = 0;
    nextLecture.end = 0;
  }

}

int readSchedule(char* path) {

  FILE *f = fopen(path, "r");
  if(f == NULL) return 1;

  fseek(f, 0, SEEK_END);
  schedlen = ftell(f);
  fseek(f, 0, SEEK_SET);
  sched = malloc(schedlen);
  if(sched == NULL) return 2;
  fread(sched, 1, schedlen, f);
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

void showTimeUntilNextLecture() {

  uint32_t offset = 50;

  drawBackground();
  drawCenteredTextAtOffset(offset, "NO LECTURE CURRENTLY RUNNING\0", 4);
  drawCenteredTextAtOffset(offset + 4*10+5, "NEXT LECTURE:\0", 3);

  if(nextLecture.start == 0) drawCenteredTextAtOffset(offset + 4*10+5 + 3*10+5, "NO LECTURES LEFT.\0", 3);
  else {
    drawCenteredTextAtOffset(offset + 4*10+5 + 3*10+5, nextLecture.title, 3);
    drawCenteredTextAtOffset(offset + 4*10+5 + 3*10+5 + 3*10+5, nextLecture.lecturer, 3);
  }

  drawScreen();
}
