/*
 * Copyright 2010, Neil White. All rights reserved.
 * Distributed under the terms of the GPL V 2 License.
 *
 * Authors:
 *      Neil White <neil@cloudsprinter.com>
 */

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdbool.h>

// surface to hold fonts

SDL_Surface **font1_surf;
SDL_Surface **font1b_surf;

SDL_Surface **font2_surf;
SDL_Surface **font2b_surf;

// ttf font holder

TTF_Font *font1;

// backround surface image

SDL_Surface *background;

SDL_Surface *wall[19];

SDL_Surface *eyes[5];
SDL_Surface *spodc[5];
SDL_Surface *spodo[5];
SDL_Surface *spodd[6];
SDL_Surface *blib, *pp, *pole, *floorb , *logo;

SDL_Surface *tghostb, *sghostb, *lghostb, *rghostb, *gghostb, *aghostb, *dghostb;

SDL_Surface *clickleft[2];
SDL_Surface *clickright[2];


#define CLCIKAUTO 20

void loadimages(void);

void imageplot(SDL_Surface *image, int x, int y);


void plotimage(SDL_Surface *image, int x, int y);


SDL_Surface *getimage(int a, int b, const char *name);


void getfonts(void);


void plotfont(char strinplot[], int x, int y, SDL_Surface *surface);

void plotfontsmall(char strinplot[], int x, int y, SDL_Surface *surface);


void plotfontfixed(char strinplot[], int x, int y, SDL_Surface *surface, int gap);


void closefonts(void);


SDL_Surface *makesurf(int x, int y, int bpp);

int textlength(char stringplot[]);

int textlengthsmall(char stringplot[]);


void drawbackground(void);



typedef struct {
	
	SDL_Surface *bor;// border image featuring corners and edge
	SDL_Surface *borh;// highligted border
	SDL_Surface *bors;// selected border
	SDL_Surface *borm ;// border image mask featuring corners and edge
	SDL_Surface *face;// face of the button
	SDL_Surface *faceh; // highlighted face of the button
		SDL_Surface *faces; // selected face of the button
	int corner;// corner size ( in border.png )
	int line; // line size ( in border.png )

	// rects for the corenrs and edges
	// top right
	SDL_Rect tr;
	// top left
	SDL_Rect tl;
	// bottom right
	SDL_Rect br;
	// bottom left
	SDL_Rect bl;
	// vertical left
	SDL_Rect vl;
	// vertical right
	SDL_Rect vr;
	// horizontal top
	SDL_Rect ht;
	// horizontal bottom
	SDL_Rect hb;

	// boolean for if button is on or not, how ironic

	//bool on;

} ButtonStyle;

ButtonStyle butdef[1];


typedef struct {
	int x; // x pos
	int y; // y pos
	int w; // width
	int h; // height
	int t; // type of button ( style )
	int on; // selected item
	int opts ; // ammount of avaliable options
	int value[10] ; // value asscociated with each option
	char *text[10]; // text asscociate with each option
	bool arrows; //decide if we want arrows outside the button ;eft and right

} MultiButton;

MultiButton multibutton[2];

// buttons
typedef struct {
	int x; // x pos
	int y; // y pos
	int w; // width
	int h; // height
	int t; // type of button ( style )
	bool on; // button selected
	char *texton; // text in button
	char *textoff; // text in button
} Button;

Button button[3];


void drawbuttonbase(int x, int y, int w, int h, int t, int highlight , int indent);


void drawbutton(int butnum);


  void drawmultibutton( int butnum);
  
  
  void definebuttons(void) ;
  
  
  
  