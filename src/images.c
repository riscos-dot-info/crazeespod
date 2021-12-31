/*
 * Copyright 2010, Neil White. All rights reserved.
 * Distributed under the terms of the GPL V 2 License.
 *
 * Authors:
 *      Neil White <neil@cloudsprinter.com>
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>





#include "main.h"

#include "images.h"




// safe for any endian
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 rmask = 0xff000000, gmask = 0x00ff0000, bmask = 0x0000ff00, amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff, gmask = 0x0000ff00, bmask = 0x00ff0000, amask = 0xff000000;
#endif

void imageplot(SDL_Surface *image, int x, int y)
{
    SDL_Rect pos;

    pos.x = x - (image -> w / 2);
    pos.y = y - (image -> h / 2);

    SDL_BlitSurface(image, NULL, screen, &pos);


}

void plotimage(SDL_Surface *image, int x, int y)
{
    SDL_Rect pos;

    pos.x = x;
    pos.y = y;

    SDL_BlitSurface(image, NULL, screen, &pos);


}




SDL_Surface *getimage(int a, int b, const char *name)

{
    SDL_Surface *surface;

    char path[256];
    char msg[256];
    strcpy(path, DATA_PREFIX);
   #ifdef LGFX
        strcat(path, "lgfx/");
	#else
	 strcat(path, "gfx/");
	#endif

        strcat(path, name);
        strcat(path, ".png");
    
    surface = IMG_Load(path);
    if (surface == NULL)
    {
         strcpy(msg, path);
        strcat(msg, " Not Loaded");
        debug(msg,0);
    }
    else
    {
       SDL_Surface *image = surface;
      if(a==-1){
	
	 surface = SDL_DisplayFormat(image);
      }
      else {
        surface = SDL_DisplayFormatAlpha(image);
      }
        SDL_FreeSurface(image);

         strcpy(msg, path);
        strcat(msg, " Loaded");
        debug(msg,0);
    }

    return surface;
}

void loadimages(void)
{
	background = getimage (-1,-1,"bg");
	
	butdef[0].bor=getimage(-1,-1,"but1/border");
	butdef[0].borh=getimage(-1,-1,"but1/borderh");
		butdef[0].bors=getimage(-1,-1,"but1/borders");
	butdef[0].borm=getimage(-1,1,"but1/borderm");
	butdef[0].face=getimage(-1,1,"but1/face");

	butdef[0].faceh=getimage(-1,1,"but1/faceh");
	butdef[0].faces=getimage(-1,1,"but1/faces");
	
	
	wall[0] =getimage(200,-1,"o");
			wall[1] =getimage(200,0,"x");
			wall[2] =getimage(200,0,"l1");
			wall[3] =getimage(200,0,"l2");
			wall[4] =getimage(200,0,"l3");
			wall[5] =getimage(200,0,"l4");
			wall[6] =getimage(200,0,"t1");
			wall[7] =getimage(200,0,"t2");
			wall[8] =getimage(200,0,"t3");
			wall[9] =getimage(200,0,"t4");
			wall[10] =getimage(200,0,"sx");
			wall[11] =getimage(200,0,"sy");
			wall[12] =getimage(200,0,"e1");
			wall[13] =getimage(200,0,"e2");
			wall[14] =getimage(200,0,"e3");
			wall[15] =getimage(200,0,"e4");
			wall[16] =getimage(200,0,"xx");
			wall[17] =getimage(200,0,"yy");

			blib =	getimage(180,0,"blib");
			pp =getimage(180,0,"pp");

			pole =getimage(200,0,"pole");

			floorb =getimage(200,0,"floor");

			eyes[1] =getimage(100,0,"eyes1");
			eyes[2] =getimage(100,0,"eyes2");
			eyes[3] =getimage(100,0,"eyes3");
			eyes[4] =getimage(100,0,"eyes4");
			spodc[1] =getimage(220,0,"spod1");
			spodc[2] =getimage(220,0,"spod2");
			spodc[3] =getimage(220,0,"spod3");
			spodc[4] =getimage(220,0,"spod4");
			spodo[1] =getimage(220,0,"spodo1");
			spodo[2] =getimage(220,0,"spodo2");
			spodo[3] =getimage(220,0,"spodo3");
			spodo[4] =getimage(220,0,"spodo4");

			spodd[5] =getimage(150,0,"spodd5");

			spodd[1] =getimage(150,0,"spodd1");
			spodd[2] =getimage(150,0,"spodd2");
			spodd[3] =getimage(150,0,"spodd3");
			spodd[4] =getimage(150,0,"spodd4");

			gghostb =getimage(170,0,"gghost");

			tghostb =getimage(150,0,"tghost");
			sghostb =getimage(150,0,"sghost");
			lghostb =getimage(150,0,"lghost");
			rghostb =getimage(150,0,"rghost");

			aghostb =getimage(150,0,"aghost");
			dghostb =getimage(150,0,"dghost");

	
}


void getfonts(void)
{
    int i;
    char path[256];
    SDL_Color text_color;
    char *font_file;
    char letter[2];


    font1_surf = (SDL_Surface **) malloc(sizeof (SDL_Surface *) * 126);
	  font2_surf = (SDL_Surface **) malloc(sizeof (SDL_Surface *) * 126);
  font1b_surf = (SDL_Surface **) malloc(sizeof (SDL_Surface *) * 126);
	  font2b_surf = (SDL_Surface **) malloc(sizeof (SDL_Surface *) * 126);
    if (TTF_Init())
    {
        printf("TTF_Init error: %s", TTF_GetError());
        exit(-1);
    }

    strcpy(path, DATA_PREFIX);
       #ifdef LGFX
        strcat(path, "lgfx/font.ttf");
	#else
	 strcat(path, "gfx/font.ttf");
	#endif

  
    font_file = path;
     font1 = TTF_OpenFont(font_file, FONT_SIZE);

    text_color.r = 0xff;
    text_color.g = 0xff;
    text_color.b = 0xff;

    for (i = 32; i < 126; i++)
    {
        letter[0] = i;
        letter[1] = '\0';
        font1b_surf[i] = TTF_RenderText_Blended(font1, letter, text_color);
        SDL_SetColorKey(font1b_surf[i], SDL_SRCCOLORKEY, SDL_MapRGB(font1b_surf[i]->format, 0, 0, 0));
        //SDL_SetAlpha(font1_surf[i], SDL_SRCALPHA, 108);
    }
    TTF_CloseFont(font1);
    
    font1 = TTF_OpenFont(font_file, FONT_SIZE);

    text_color.r = 0xee;
    text_color.g = 0x00;
    text_color.b = 0x00;

    for (i = 32; i < 126; i++)
    {
        letter[0] = i;
        letter[1] = '\0';
        font1_surf[i] = TTF_RenderText_Blended(font1, letter, text_color);
        SDL_SetColorKey(font1_surf[i], SDL_SRCCOLORKEY, SDL_MapRGB(font1_surf[i]->format, 0, 0, 0));
        SDL_SetAlpha(font1_surf[i], SDL_SRCALPHA, 90);
    }
    TTF_CloseFont(font1);

	 font1 = TTF_OpenFont(font_file, FONT_SIZE_SMALL);

    text_color.r = 0xff;
    text_color.g = 0xff;
    text_color.b = 0xff;

    for (i = 32; i < 126; i++)
    {
        letter[0] = i;
        letter[1] = '\0';
        font2b_surf[i] = TTF_RenderText_Blended(font1, letter, text_color);
        SDL_SetColorKey(font2b_surf[i], SDL_SRCCOLORKEY, SDL_MapRGB(font2b_surf[i]->format, 0, 0, 0));
        //SDL_SetAlpha(font1_surf[i], SDL_SRCALPHA, 108);
    }
    TTF_CloseFont(font1);
    
     font1 = TTF_OpenFont(font_file, FONT_SIZE_SMALL);

    text_color.r = 0xee;
    text_color.g = 0x00;
    text_color.b = 0x00;

    for (i = 32; i < 126; i++)
    {
        letter[0] = i;
        letter[1] = '\0';
        font2_surf[i] = TTF_RenderText_Blended(font1, letter, text_color);
        SDL_SetColorKey(font2_surf[i], SDL_SRCCOLORKEY, SDL_MapRGB(font2_surf[i]->format, 0, 0, 0));
        SDL_SetAlpha(font2_surf[i], SDL_SRCALPHA, 90);
    }
    TTF_CloseFont(font1);
	
    TTF_Quit();

}

void plotfont(char strinplot[], int x, int y, SDL_Surface *surface)
{
    int i, j, str;
    j = strlen(strinplot);
    SDL_Rect tpos;
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    for (i = 0; i < j; i++)
    {
        str = strinplot[i];
        tpos.w = font1b_surf[ str ]->w;
        tpos.h = font1b_surf[ str ]->h;
	tpos.x=pos.x-3+randoon(6);
	tpos.y=pos.y-3+randoon(6);
        SDL_BlitSurface(font1b_surf[ str ], NULL, surface, &tpos);
        pos.x += font1b_surf[ str ]->w;
    }
     pos.x = x;
    pos.y = y;
    for (i = 0; i < j; i++)
    {
        str = strinplot[i];
        tpos.w = font1_surf[ str ]->w;
        tpos.h = font1_surf[ str ]->h;
        tpos.x=pos.x-3+randoon(6);
	tpos.y=pos.y-3+randoon(6);
        SDL_BlitSurface(font1_surf[ str ], NULL, surface, &tpos);
        pos.x += font1_surf[ str ]->w;
    }
}


void plotfontsmall(char strinplot[], int x, int y, SDL_Surface *surface)
{
    int i, j, str;
    j = strlen(strinplot);
    SDL_Rect tpos;
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
        for (i = 0; i < j; i++)
    {
        str = strinplot[i];
        tpos.w = font2b_surf[ str ]->w;
        tpos.h = font2b_surf[ str ]->h;
	tpos.x=pos.x-2+randoon(4);
	tpos.y=pos.y-2+randoon(4);
        SDL_BlitSurface(font2b_surf[ str ], NULL, surface, &tpos);
        pos.x += font2b_surf[ str ]->w;
    }
     pos.x = x;
    pos.y = y;
    for (i = 0; i < j; i++)
    {
        str = strinplot[i];
        pos.w = font2_surf[ str ]->w;
        pos.h = font2_surf[ str ]->h;
         tpos.x=pos.x-2+randoon(4);
	tpos.y=pos.y-2+randoon(4);
        SDL_BlitSurface(font2_surf[ str ], NULL, surface, &tpos);
        pos.x += font2_surf[ str ]->w;
    }
}		

int textlength(char stringplot[])
{
 int i, j, length=0,str;
    j = strlen(stringplot);

    for (i = 0; i < j; i++)
    {
		str = stringplot[i];
        length += font1_surf[ str ]->w;
    }
	return length;
}		

int textlengthsmall(char stringplot[])
{
 int i, j, length=0,str;
    j = strlen(stringplot);

    for (i = 0; i < j; i++)
    {
		str = stringplot[i];
        length += font2_surf[ str ]->w;
    }
	return length;
}	
	


void plotfontfixed(char strinplot[], int x, int y, SDL_Surface *surface, int gap)
{
    int i, j, str;
    j = strlen(strinplot);
    SDL_Rect pos;

    pos.x = x;
    pos.y = y;
    for (i = 0; i < j; i++)
    {
        str = strinplot[i];
        if (str == 49)
        {
            pos.x += 5;
        }
        SDL_BlitSurface(font1_surf[ str ], NULL, surface, &pos);
        if (str == 49)
        {
            pos.x -= 5;
        }
        pos.x += gap;
    }
}

void closefonts(void)
{



    free(font1_surf);


}

SDL_Surface *makesurf(int x, int y, int bpp)
{
    SDL_Surface *surface;
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, x, y, bpp, rmask, gmask, bmask, amask);
    return surface;
}

void drawbackground(void)
{
	int x,y;
	for (x=0 ;  x<SCREEN_X+background->w ; x+=background->w  )
	{
		for (y=0 ; y<SCREEN_Y+background->h ; y+=background->h  )
		{
			plotimage(background,x,y);
		}
	}
}

void definebuttons(void) {
    int i;
    butdef[0].corner = 5;
    butdef[0].line = 2;
    
        // corner sizes w h
        butdef[0].tr.w = butdef[0].corner;
        butdef[0].tr.h = butdef[0].corner;
        butdef[0].tl.w = butdef[0].corner;
        butdef[0].tl.h = butdef[0].corner;
        butdef[0].br.w = butdef[0].corner;
        butdef[0].br.h = butdef[0].corner;
        butdef[0].bl.w = butdef[0].corner;
        butdef[0].bl.h = butdef[0].corner;

        //corner w and h's in button.png

        butdef[0].tl.x = 0;
        butdef[0].tl.y = 0;

        butdef[0].tr.x = butdef[0].bor->w - butdef[0].corner;
        butdef[0].tr.y = 0;

        butdef[0].bl.x = 0;
        butdef[0].bl.y = butdef[0].bor->h - butdef[0].corner;

        butdef[0].br.x = butdef[0].bor->w - butdef[0].corner;
        butdef[0].br.y = butdef[0].bor->h - butdef[0].corner;

        // lines bits horiz verts

        butdef[0].ht.w = butdef[0].line;
        butdef[0].ht.h = butdef[0].corner;

        butdef[0].hb.w = butdef[0].line;
        butdef[0].hb.h = butdef[0].corner;

        butdef[0].vl.w = butdef[0].corner;
        butdef[0].vl.h = butdef[0].line;

        butdef[0].vr.w = butdef[0].corner;
        butdef[0].vr.h = butdef[0].line;

        // lines x and ys in button.png

        butdef[0].ht.x = butdef[0].corner;
        butdef[0].ht.y = 0;

        butdef[0].hb.x = butdef[0].corner;
        butdef[0].hb.y = butdef[0].bor->h - butdef[0].corner;

        butdef[0].vl.x = 0;
        butdef[0].vl.y = butdef[0].corner;

        butdef[0].vr.x = butdef[0].bor->w - butdef[0].corner;
        butdef[0].vr.y = butdef[0].corner;
   
multibutton[0].w = 180*GAP;
    multibutton[0].h = 40*GAP;
	 multibutton[0].x = ( SCREEN_X/2 ) - (multibutton[0].w/2);
    multibutton[0].y = 50*GAP;


    multibutton[0].t = 0;
	    multibutton[0].on = 0;
	    multibutton[0].opts = 3;
    multibutton[0].text[0] = "Keys - E D O K";
	 multibutton[0].value[0] = 0;
	   multibutton[0].text[1] = "Arrow Keys";
		 multibutton[0].value[1] = 1;
		 multibutton[0].text[2] = "Mouse";
	 multibutton[0].value[2] = 2;
     multibutton[0].arrows=true;
	
    // multi button to hold sound
   multibutton[1].w = 180*GAP;
    multibutton[1].h = 40*GAP;
	 multibutton[1].x = ( SCREEN_X/2 ) - (multibutton[1].w/2);
    multibutton[1].y = 100*GAP;
    multibutton[1].t = 0;
	    multibutton[1].on = 2;
	    multibutton[1].opts = 3;
    multibutton[1].text[0] = "Sound Off";
	 multibutton[1].value[0] = 0;
	   multibutton[1].text[1] = "Sound Medium";
		 multibutton[1].value[1] = 64;
		 multibutton[1].text[2] = "Sound Loud";
	 multibutton[1].value[2] = 128;
        multibutton[1].arrows=true;
	
	
	    // first three buttons for menu along te top
	      button[0].w = 80*GAP;
	       button[0].h = 40*GAP;
    button[0].x = SCREEN_X - button[0].w - (10*GAP);;
    button[0].y = SCREEN_Y-button[0].h-(10*GAP);
  
   button[0].on=false;
    button[0].t = 0;
    button[0].textoff = "Start";
	 button[0].texton = "YEA!";
   
	
	
	
	
	
}


void drawmultibutton( int butnum) {
   
    ButtonStyle style;
  
    int highlight,indent;
  
    // rect for where position screen we are plotting
    SDL_Rect pos;

	// handle if we are putting clicker buts at each end
	// this goes here at the start or the buttons move when the 
	// button does it's highlight indent thing
if ( multibutton[butnum].arrows ){
//plot the arrows

	   // left side button
    pos.x = multibutton[butnum].x - 22 ;
    pos.y = multibutton[butnum].y - 10 + (multibutton[butnum].h / 2);
    pos.w = 20;
    pos.h = 20;


	
    if (mouseclick(pos.x, pos.y, pos.w, pos.h) == 1  && clickrepeat < 0 ) {
		clickrepeat=CLICKAUTO;
        multibutton[butnum].on -= 1;
		if ( multibutton[butnum].on<0 )  multibutton[butnum].on=multibutton[butnum].opts-1;
		
			
        SDL_BlitSurface(clickleft[1], NULL, screen, &pos);
    } else {
		clickrepeat-=1;
		if (mb==0) { clickrepeat=-1; }
        SDL_BlitSurface(clickleft[0], NULL, screen, &pos);
    }
    //right side button
    pos.x = multibutton[butnum].x + multibutton[butnum].w + 2;
    if (mouseclick(pos.x, pos.y, pos.w, pos.h) == 1 && clickrepeat < 0 ) {
			clickrepeat=CLICKAUTO;
         multibutton[butnum].on += 1;
		if ( multibutton[butnum].on>multibutton[butnum].opts-1 ) multibutton[butnum].on=0;
        SDL_BlitSurface(clickright[1], NULL, screen, &pos);
    } else {
			clickrepeat-=1;
		if (mb==0) { clickrepeat=-1; }
        SDL_BlitSurface(clickright[0], NULL, screen, &pos);
    }

}
 
    style = butdef[multibutton[butnum].t];


    if (mousein(multibutton[butnum].x, multibutton[butnum].y, multibutton[butnum].w, multibutton[butnum].h) == 1) {
    
		highlight=1;
		indent=1;

     
        //else if (mc==0 ) mc=1;
    } else {
       highlight=0;
		;
          
        }

// go draw the button base

	drawbuttonbase(multibutton[butnum].x ,multibutton[butnum].y, multibutton[butnum].w,multibutton[butnum].h,
	               multibutton[butnum].t , highlight ,  indent);

    // add the text, type 1 has small fonts type 0 larger fonts
    int textl;
    if ( multibutton[butnum].t == 1) {
      textl = textlengthsmall( multibutton[butnum].text[ multibutton[butnum].on]);
			  plotfontsmall( multibutton[butnum].text[ multibutton[butnum].on],  multibutton[butnum].x +
	( multibutton[butnum].w / 2)-(textl / 2),  multibutton[butnum].y + 
			                ( multibutton[butnum].h / 2)-(FONT_SIZE_SMALL / 2), screen); 
    }
    if (multibutton[butnum].t == 0) {
      
			textl = textlength( multibutton[butnum].text[ multibutton[butnum].on]);
		plotfont( multibutton[butnum].text[ multibutton[butnum].on],  multibutton[butnum].x + 
	( multibutton[butnum].w / 2)-(textl / 2),  multibutton[butnum].y + 
		         ( multibutton[butnum].h / 2)-(FONT_SIZE / 2), screen);
	
    }


// handle clicking our mutli button
		if ( clickrepeat<0 ){

	
	if (mouseclick( multibutton[butnum].x,  multibutton[butnum].y,  multibutton[butnum].w,  multibutton[butnum].h) == 1) { 
		multibutton[butnum].on+=1;
		if ( multibutton[butnum].on>multibutton[butnum].opts-1 ) multibutton[butnum].on=0;clickrepeat=CLICKAUTO;
	}
				}
		else { clickrepeat-=1;
		if (mb==0) { clickrepeat=-1; }
		}




	
    

}




void drawbutton(int butnum) {


	// 0=normal 1=highlighted 2 =selected
	int highlight;
	// 0=not 1 = indented
	int indent;


    if (mousein(button[butnum].x, button[butnum].y, button[butnum].w, button[butnum].h) == 1) {
        if (button[butnum].on) {
			highlight=1;
			indent=1;
        } else {
             highlight=2;
			indent=0;
        }

		if ( clickrepeat<0 ){
        if (mb == 1) { button[butnum].on = !button[butnum].on;clickrepeat=CLICKAUTO;}
		}
		else { clickrepeat-=1;
		if (mb==0) { clickrepeat=-1; }
		}
       
    } else {
        if (button[butnum].on) {
			  highlight=2;
			indent=1;
        } else {
			 highlight=0;
			indent=0;
          
        }

    }
	// go draw the button base

	drawbuttonbase(button[butnum].x ,button[butnum].y, button[butnum].w,button[butnum].h,
	               button[butnum].t , highlight ,  indent);
   
    // add the text, type 1 has small fonts type 0 larger fonts
    int textl;
    if (button[butnum].t == 1) {
        if ( button[butnum].on ) { textl = textlengthsmall(button[butnum].texton); 
        plotfontsmall(button[butnum].texton, button[butnum].x + (button[butnum].w / 2)-(textl / 2), button[butnum].y + (button[butnum].h / 2)-(FONT_SIZE_SMALL / 2), screen); }
		else { textl = textlengthsmall(button[butnum].textoff);
			  plotfontsmall(button[butnum].textoff, button[butnum].x + (button[butnum].w / 2)-(textl / 2), button[butnum].y + (button[butnum].h / 2)-(FONT_SIZE_SMALL / 2), screen); }
    }
    if (button[butnum].t == 0) {
        if ( button[butnum].on ) {
			textl = textlength(button[butnum].texton);plotfont(button[butnum].texton, button[butnum].x + (button[butnum].w / 2)-(textl / 2), button[butnum].y + (button[butnum].h / 2)-(FONT_SIZE / 2), screen);}
		else { textl = textlength(button[butnum].textoff);
			plotfont(button[butnum].textoff, button[butnum].x + (button[butnum].w / 2)-(textl / 2), button[butnum].y + (button[butnum].h / 2)-(FONT_SIZE / 2), screen); }
        
    }

  

}


void drawbuttonbase(int x, int y, int w, int h, int t, int highlight , int indent)
{
    SDL_Surface *face;
    SDL_Surface *bor;
    ButtonStyle style = butdef[t];;

    
	 //loop increment holder
    int i;
    // rect for where position screen we are plotting
    SDL_Rect pos, clip, butt;
	butt.x=x;
	butt.y=y;
	butt.w=w;
	butt.h=h;

	// decide how the buton looks
	if (highlight==0)
	{
	  face = SDL_DisplayFormat(style.face);
            bor = SDL_DisplayFormat(style.bor);
	}
	if (highlight==1)
	{
	  face = SDL_DisplayFormat(style.faces);
            bor = SDL_DisplayFormat(style.bors);
	}
	if (highlight==2)
	{
	  face = SDL_DisplayFormat(style.faceh);
            bor = SDL_DisplayFormat(style.borh);
	}

	if (indent==1){
            butt.x += 2;
            butt.w -= 4;
            butt.y += 2;
            butt.h -= 4;
	}
    // plot face
    pos.w = face->w;
    pos.h = face->h;
    pos.x = butt.x;
    pos.y = butt.y;
    clip.x = 0;
    clip.y = 0;
    clip.w = face->w;
    clip.h = face->h;
    do {
        if (pos.y + pos.h > butt.y + butt.h) clip.h = butt.y + butt.h - pos.y;
        do {
            if (pos.x + pos.w > butt.x + butt.w) clip.w = butt.x + butt.w - pos.x;

            SDL_BlitSurface(face, &clip, screen, &pos);
            pos.x += face->w;

        } while (pos.x < butt.x + butt.w);
        pos.y += face->h;
        clip.w = face->w;
        pos.x = butt.x;
    } while (pos.y < butt.y + butt.h);


    // do horizontals
    // top line
    pos.w = style.ht.w;
    pos.h = style.ht.h;
    pos.y = butt.y;

    for (i = butt.x + style.corner; i < butt.x + butt.w - style.corner; i += style.ht.w) {
        pos.x = i;
        SDL_BlitSurface(bor, &style.ht, screen, &pos);
    }
    // bottom line
    pos.w = style.hb.w;
    pos.h = style.hb.h;
    pos.y = butt.y + butt.h - style.hb.h;
    for (i = butt.x + style.corner; i < butt.x + butt.w - style.corner; i += style.hb.w) {
        pos.x = i;
        SDL_BlitSurface(bor, &style.hb, screen, &pos);
    }
    // vertical lines
    // left side
    pos.w = style.vl.w;
    pos.h = style.vl.h;
    pos.x = butt.x;

    for (i = butt.y + style.corner; i < butt.y + butt.h - style.corner; i += style.vl.h) {
        pos.y = i;
        SDL_BlitSurface(bor, &style.vl, screen, &pos);
    }
    // right side
    pos.w = style.vr.w;
    pos.h = style.vr.h;
    pos.x = butt.x + butt.w - style.vr.w;

    for (i = butt.y + style.corner; i < butt.y + butt.h - style.corner; i += style.vr.h) {
        pos.y = i;
        SDL_BlitSurface(bor, &style.vr, screen, &pos);
    }

    // plot on the corners


    // top left
    pos.w = style.tl.w;
    pos.h = style.tl.h;
    pos.x = butt.x;
    pos.y = butt.y;

    SDL_BlitSurface(bor, &style.tl, screen, &pos);


    // top right
    pos.w = style.tr.w;
    pos.h = style.tr.h;
    pos.x = butt.x + butt.w - style.tr.w;
    pos.y = butt.y;

    SDL_BlitSurface(bor, &style.tr,screen, &pos);

    // bottom left

    pos.w = style.bl.w;
    pos.h = style.bl.h;
    pos.x = butt.x;
    pos.y = butt.y + butt.h - style.bl.h;

    SDL_BlitSurface(bor, &style.bl, screen, &pos);



    // bottom right

    pos.w = style.br.w;
    pos.h = style.br.h;
    pos.x = butt.x + butt.w - style.br.w;
    pos.y = butt.y + butt.h - style.br.h;

    SDL_BlitSurface(bor, &style.br, screen, &pos);
  //end of drawbut func free surfaces
    SDL_FreeSurface(bor);
    SDL_FreeSurface(face);

}
