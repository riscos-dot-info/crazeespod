/*
 * Copyright 2010, Neil White. All rights reserved.
 * Distributed under the terms of the GPL V 2 License.
 *
 * Authors:
 *      Neil White <neil@cloudsprinter.com>
 */

#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
// handle if quit

int quit;

// mouse x y bbutton, clicking

int mx,my,mb,mc,clicking;

int space_bar_muther_fudge;

// screen surface everything will be drawn to

SDL_Surface *screen;

// screen size and color depth and Frames per second
#ifdef LGFX
#define SCREEN_X 640
#define SCREEN_Y 480
#define GFXX 64
#define GFXY 32
#define FONT_SIZE 36
#define FONT_SIZE_SMALL 22
#define SCREEN_FPS 30
#define GAP 2
#define POWERP  400
#define CLICKAUTO 20
#else
#define SCREEN_FPS 15
#define GFXX 32
#define GFXY 16
#define SCREEN_X 320
#define SCREEN_Y 240
#define FONT_SIZE 18
#define FONT_SIZE_SMALL 11
#define GAP 1
#define POWERP  200
#define CLICKAUTO 10
#endif
#define SCREEN_BPP 16


// hold screen center

int centerx,centery;

int clickrepeat;

// data directory

#ifdef __riscos__
#define DATA_PREFIX "/<CrazeeSpod$Dir>/"
#else
#define DATA_PREFIX "./"
#endif

// debug messages 1 on 0 off

#define DEBUG 1

// cheap and easy click auto repeat thingy

int clickrepeat;




void debugf(char msg[],float value);
void debug(char msg[],int value);

int main(int argc, char *argv[]);


void checkinput(void);

int randoon(int num);

void runmenu(void);

void rungame(void);

void losegame(void);

void getready(void);

void leveldone(void);


int mousein(int x, int y, int w, int h);


int mouseclick(int x, int y, int w, int h);

void checkinputa(void);

void checkinputo(void);

void checkinputm(void);


// static SDL_Cursor *init_system_cursor(const char *image[]);

// static const char *arrow[] = {
//   /* width height num_colors chars_per_pixel */
//   "    32    32        3            1",
//   /* colors */
//   "X c #000000",
//   ". c #ffffff",
//   "  c None",
//   /* pixels */
//   " X ",
//   "X X",
//   " X ",
//   "1,1"
// };

