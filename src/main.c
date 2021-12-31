/*
 * Copyright 2010, Neil White. All rights reserved.
 * Distributed under the terms of the GPL V 2 License.
 *
 * Authors:
 *      Neil White <neil@cloudsprinter.com>
 */

// include neccecary standard libraries

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// include SDL libraries

#include <SDL/SDL.h>

#include <SDL/SDL_mixer.h>


#include <SDL/SDL_framerate.h>

FPSmanager fpsm;

// include local headers

#include "main.h"
#include "images.h"
#include "engine.h"
#include "sound.h"


#ifdef GP2X
#define DATA_PREFIX "./"
#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_X               (14)
#define GP2X_BUTTON_Y               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)
#endif
// low graphics?

int lg;

// main function to initialise SDL

int main(int argc, char *argv[])
{
  

// 	init_system_cursor(arrow);
int j;
int full_screen = 0;
char path[256];
strcpy(path, DATA_PREFIX);
    #ifdef LGFX
        strcat(path, "lgfx/");
	#else
	 strcat(path, "gfx/");
	#endif
        strcat(path, "gumboil.png");
	 char buffer[100];


	FILE *in = fopen(path, "rt");
  if ( in  == NULL ) { highscore=100; }
  else { 
    fgets(buffer, 100, in);
	  
	sscanf(buffer,"%d",&highscore);
	  fclose(in);
  }

	
	
 gamestate=STATE_MENU;
	for (j = 1; j < argc; j++)
	{
		if (strcmp(argv[j],"-f") == 0 || strcmp(argv[j], "-fullscreen") == 0)
            { full_screen = SDL_FULLSCREEN|SDL_DOUBLEBUF;} else
	      if (strcmp(argv[j],"-lg") == 0 || strcmp(argv[j], "-lowgraphics") == 0) lg=1;
	}
	
	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		return EXIT_FAILURE;
	}
	atexit(SDL_Quit);
    /* create screen surface */
		#ifdef GP2X
	if ( (screen=SDL_SetVideoMode(SCREEN_X,SCREEN_Y,16, SDL_HWSURFACE|SDL_HWPALETTE|SDL_FULLSCREEN|SDL_DOUBLEBUF)) == NULL )
	{
		fprintf(stderr, "Couldn't set  video mode: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	#else
		if ( (screen=SDL_SetVideoMode(SCREEN_X,SCREEN_Y,16, SDL_HWSURFACE|SDL_HWPALETTE|full_screen)) == NULL )
	{
		fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	SDL_WM_SetCaption("Crazee Spod!",0);
	#endif

	printf("Modo de video puesto Amigo!");

#ifdef GP2X
    SDL_Joystick* joystick = SDL_JoystickOpen(0);
#endif
	debug("SDL init OK",0);
	initvars();
// load images (duh)
initandloadsounds();
	loadimages();
	definebuttons();
	// get fonts
	getfonts();

	// initiate SDL_gfx framerate controls
	SDL_ShowCursor(1);
	 SDL_initFramerate(&fpsm);
     SDL_setFramerate(&fpsm,SCREEN_FPS);


centerx=SCREEN_X/2;
centery=SCREEN_Y/2;
// enter main loop
   
	do
	{
		
	if( gamestate!=STATE_MENU )
	{
	  if (multibutton[0].on==0) {checkinputo();}
	  if (multibutton[0].on==2){ checkinputm();}
	  if (multibutton[0].on==1) {checkinputa();}
	}
	  
	  
		if (gamestate==STATE_RUNNING) { rungame(); }
		if (gamestate==STATE_LOSE) { losegame(); } 
		if (gamestate==STATE_READY) { getready(); }
		if (gamestate==STATE_WIN) { leveldone(); } 
		if (gamestate==STATE_MENU ) { checkinput();;runmenu(); }
		
		
		
		
 SDL_Flip(screen);
		SDL_framerateDelay(&fpsm);
	}
		while (quit==0);
	#ifdef GP2X
SDL_JoystickClose(joystick);
    chdir("/usr/gp2x");
execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
Mix_CloseAudio();
		return EXIT_SUCCESS;
}

void rungame(void){
  char text[50];
  int textl;
  dosghosts();
			dotghosts();
			dolghosts();
			dorghosts();
			
			dokeys();
			dospod();
			if (spod.ded == false) checkbite();
			if ( spod.ded==true && spod.oy<-200 ) {      lives--;gamestate=STATE_LOSE;}
			if (blobs==0 ) { level++ ; gamestate=STATE_WIN;
            if ( level>1 && level%3==0 ) { lives++; }
            
             }
			doFloor();
		doDraw();
		   sprintf(text,"LiVes %d",lives);
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X-textl-(10*GAP),10*GAP,screen);
   sprintf(text,"LeVeL %d",level);
  textl=textlengthsmall(text);
  plotfontsmall(text,10*GAP,10*GAP,screen);
  
  sprintf(text,"%d",score);
  textl=textlength(text);
  plotfont(text,(SCREEN_X/2)-(textl/2),10*GAP,screen);
		
}


void getready(void)
{
  char text[50];
  int textl;
  static int sillywait=0;
  doFloor();
  
      sprintf(text,"LEveL %d Get ReaDee!",level);
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,100*GAP,screen);
 
 sillywait++;
 
 
    if ( sillywait>2*SCREEN_FPS ) {
play_sound(5);
      gamestate=STATE_RUNNING;
    
    sillywait=0;
    }
  
}

void leveldone(void)
{
  char text[50];
  int textl;
  doFloor();
  if ( level>1 && level%3==0 ){
        strcpy(text,"ExTra LiFe! YeA!");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,50*GAP,screen);
       
       
       }
      strcpy(text,"HeAdButt Your ComPOOtA");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,180*GAP,screen);
  
  strcpy(text,"LeveL CompleEt!");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,100*GAP,screen);
  
   sprintf(text,"LeVel %d NeXt!",level);
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,130*GAP,screen);
  
    if ( space_bar_muther_fudge==1 || mb==1 ) {
getlevel();
getplots();
      gamestate=STATE_READY;
    
   
    }
 
  
  
}

void losegame(void)
{
  char text[50];
  int textl;
  doFloor();
  
      strcpy(text,"HeAdButt Your ComPOOtA");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,180*GAP,screen);
  
  
  if (lives>=0 )
  {
  strcpy(text,"No WaY LifE LosT!");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,100*GAP,screen);
  
   sprintf(text,"%d LiVes LefT",lives);
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,130*GAP,screen);
  
    if ( space_bar_muther_fudge==1 || mb==1 ) {
 spod.ded=false;
      gamestate=STATE_RUNNING;
      spod.x=spodx;spod.y=spody;spod.d=1;getghosts();spod.ox=0;spod.oy=0;
    offx=(SCREEN_X/2)-secx[spod.x][spod.y]-(GFXX/2);
       offy=(SCREEN_Y/2)-secy[spod.x][spod.y]-GFXY;
    
       
    }
    
    
  }
  
 if (lives<0)
  {
  strcpy(text,"GamE Over Man!");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,100*GAP,screen);
  
 if (score>highscore)
 {
   strcpy(text,"WhoA you Got da HiGhScore!");
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,130*GAP,screen);
  sprintf(text,"!*   %d   *!",score);
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,152*GAP,screen);
 }
  
    if ( space_bar_muther_fudge==1 || mb==1 ) {
       if (score>highscore) { highscore=score;
       char path[256];
strcpy(path, DATA_PREFIX);
     #ifdef LGFX
        strcat(path, "lgfx/");
	#else
	 strcat(path, "gfx/");
	#endif
        strcat(path, "gumboil.png");
	 char buffer[100];


	FILE *out = fopen(path, "wt");
 sprintf(buffer,"%d",score);
    fputs(buffer,  out);
	  fclose(out);
	
       }
    space_bar_muther_fudge=0; mb=0;spod.ox=0;spod.oy=0;
      gamestate=STATE_MENU;SDL_ShowCursor(1);
      
    }
    
    
  }
  
  
}

void runmenu(void)
{
  char text[50];
  int textl;
  doFloor();
  
  strcpy(text,"CraZee Spod!");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,6*GAP,screen);
  
   strcpy(text,"An SDL computer game");
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,24*GAP,screen);
  /*
    strcpy(text,"ConTroLls");
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,46*GAP,screen);
  
   strcpy(text,"CliCk tHe mouSe whEre you Want to gO");
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,66*GAP,screen);
  
    strcpy(text,"Or - Use the ArooW KEyz (ruBBish)");
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,82*GAP,screen);
  
   strcpy(text,"Or - Use the keYs E D O and K (best)");
  textl=textlengthsmall(text);
  plotfontsmall(text,SCREEN_X/2-textl/2,98*GAP,screen);
  */
      strcpy(text,"HiGh ScoRe");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,150*GAP,screen);
  
   sprintf(text,"%d",highscore);
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,175*GAP,screen);
  /*
    strcpy(text,"HeAdButt Your ComPOOtA");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,180*GAP,screen);
  
  strcpy(text,"ToO STaRt!");
  textl=textlength(text);
  plotfont(text,SCREEN_X/2-textl/2,200*GAP,screen);
  */
  
    drawmultibutton(1);
  
  drawmultibutton(0);
  
  drawbutton(0);
  
  if ( space_bar_muther_fudge==1 || button[0].on==true ) {
   if ( multibutton[0].on==0 || multibutton[0].on==1 ) { SDL_ShowCursor(0); }
     setvolume(multibutton[1].value[multibutton[1].on]);
    score=0;lives=3;level=1;
 button[0].on=false;
      getlevel();mb=0;
     getplots(); gamestate=STATE_READY;}
  
  
}



void initvars(void){

  int stime;
  long ltime;

  /* get the current calendar time */
  ltime = time(NULL);
  stime = (unsigned) ltime/2;
  srand(stime);
	

}


// a function to handle debuging messages

void debug(char msg[],int value)
{
	if (DEBUG==1){
	fprintf(stdout, "MSG: %s %d\n", msg , value);
	}
}

// add input handling here save another set of c h files

void checkinput(void)
{
	SDL_Event event;

	      
	 while (SDL_PollEvent(&event) != 0)
	{
	  SDL_GetMouseState(&mx,&my);
	      if(SDL_GetMouseState(&mx,&my)&SDL_BUTTON(1)){mb=1;mc=0;}else{mb=0;mc=1;}
		switch(event.type)
		{
		  #ifdef GP2X
		case SDL_JOYBUTTONDOWN:
			switch(event.jbutton.button)
			{
			case GP2X_BUTTON_SELECT: quit = 1; break;
			case GP2X_BUTTON_START: space_bar_muther_fudge = 1; break;
	
			case GP2X_BUTTON_LEFT: dl_down = 1; break;
			case GP2X_BUTTON_UP: ul_down = 1; break;
			case GP2X_BUTTON_RIGHT: ur_down = 1; break;
			case GP2X_BUTTON_DOWN: dr_down = 1; break;
              
			default: /* Stops gcc warning */ break;
			}
			break;

		case SDL_JOYBUTTONUP:
			switch(event.jbutton.button)
			{
			  case GP2X_BUTTON_START: space_bar_muther_fudge = 0; break;
			case GP2X_BUTTON_LEFT: dl_down = 0; break;
			case GP2X_BUTTON_UP: ul_down = 0; break;
			case GP2X_BUTTON_RIGHT: ur_down = 0; break;
			case GP2X_BUTTON_DOWN: dr_down = 0; break;
                
			default: /* Stops gcc warning */ break;
			}
			break;
			#else
				case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE: quit = 1; break;
			
			case SDLK_SPACE : space_bar_muther_fudge =1 ; break;
			case SDLK_e: ul_down = 1; break;
			case SDLK_o: ur_down = 1; break;
			case SDLK_d: dr_down = 1; break;
			case SDLK_k: dl_down = 1; break;
                    
			default: /* Stops gcc warning */ break;
			}
			break;

		case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
			case SDLK_e: ul_down = 0; break;
			case SDLK_o: ur_down = 0; break;
			case SDLK_d: dr_down = 0; break;
			case SDLK_k: dl_down = 0; break;
                          case SDLK_SPACE : space_bar_muther_fudge =0 ; break;
			default: /* Stops gcc warning */ break;
			}
			break;
			#endif

		case SDL_QUIT:
			quit = 1;
			break;
		}
	}
	
	;
}


void checkinputo(void)
{
	SDL_Event event;

	      
	 while (SDL_PollEvent(&event) != 0)
	{
	 
	//  SDL_GetMouseState(&mx,&my);
	    //  if(SDL_GetMouseState(&mx,&my)&SDL_BUTTON(1)){mb=1;mc=0;}else{mb=0;mc=1;}
		switch(event.type)
		{
		
				case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE: quit = 1; break;
			
			case SDLK_SPACE : space_bar_muther_fudge =1 ; break;
			case SDLK_e: ul_down = 1; break;
			case SDLK_o: ur_down = 1; break;
			case SDLK_d: dr_down = 1; break;
			case SDLK_k: dl_down = 1; break;
                    
			default: /* Stops gcc warning */ break;
			}
			break;

		case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
			case SDLK_e: ul_down = 0; break;
			case SDLK_o: ur_down = 0; break;
			case SDLK_d: dr_down = 0; break;
			case SDLK_k: dl_down = 0; break;
                          case SDLK_SPACE : space_bar_muther_fudge =0 ; break;
			default: /* Stops gcc warning */ break;
			}
			break;


		case SDL_QUIT:
			quit = 1;
			break;
		}
	}
	
	;
}


void checkinputm(void)
{
	SDL_Event event;

	      
	 while (SDL_PollEvent(&event) != 0)
	{
	   SDL_GetMouseState(&mx,&my);
	       if(SDL_GetMouseState(&mx,&my)&SDL_BUTTON(1)){mb=1;mc=0;}else{mb=0;mc=1;}
		switch(event.type)
		{
		  
				case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE: quit = 1; break;
			
			case SDLK_SPACE : space_bar_muther_fudge =1 ; break;
		
			default: /* Stops gcc warning */ break;
			}
			break;

		case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
			
                          case SDLK_SPACE : space_bar_muther_fudge =0 ; break;
			default: /* Stops gcc warning */ break;
			}
			break;
			

		case SDL_QUIT:
			quit = 1;
			break;
		}
	}
	
	;
}

void checkinputa(void)
{
	SDL_Event event;

	      
	 while (SDL_PollEvent(&event) != 0)
	{
	 // SDL_GetMouseState(&mx,&my);
	    //  if(SDL_GetMouseState(&mx,&my)&SDL_BUTTON(1)){mb=1;mc=0;}else{mb=0;mc=1;}
		switch(event.type)
		{
		 
				case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_ESCAPE: quit = 1; break;
			
			case SDLK_SPACE : space_bar_muther_fudge =1 ; break;
			case SDLK_UP: ul_down = 1; break;
			case SDLK_RIGHT: ur_down = 1; break;
			case SDLK_DOWN: dr_down = 1; break;
			case SDLK_LEFT: dl_down = 1; break;
                    
			default: /* Stops gcc warning */ break;
			}
			break;

		case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
			case SDLK_UP: ul_down = 0; break;
			case SDLK_RIGHT: ur_down = 0; break;
			case SDLK_DOWN: dr_down = 0; break;
			case SDLK_LEFT: dl_down = 0; break;
                          case SDLK_SPACE : space_bar_muther_fudge =0 ; break;
			default: /* Stops gcc warning */ break;
			}
			break;
		

		case SDL_QUIT:
			quit = 1;
			break;
		}
	}
	
	;
}



int randoon(int num)
{
  	/* Seeded random number generator */
	
	return (rand()%num);
}



int mousein(int x, int y, int w, int h) {
    if (mx > x && mx < x + w && my > y && my < y + h) return 1;
    return 0;
}

// function to find if mouse is inside a rectangle and being clicked

int mouseclick(int x, int y, int w, int h) {
    if (mx > x && mx < x + w && my > y && my < y + h && mb == 1) return 1;
    return 0;
}



