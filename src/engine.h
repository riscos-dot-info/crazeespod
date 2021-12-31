
/*
 * Copyright 2010, Neil White. All rights reserved.
 * Distributed under the terms of the GPL V 2 License.
 *
 * Authors:
 *      Neil White <neil@cloudsprinter.com>
 */

#include <stdbool.h>


#define STATE_LOSE  1
#define STATE_MENU  2
#define STATE_READY  3
#define STATE_RUNNING  4
#define STATE_WIN 5
#define STATE_GAMEOVER  6

int highscore,score,lives,spodx,spody;
 int stupidmouth;

	 int  lives, level , powerpill , powernoise, offx, offy;
	 
	 int lx, ly , lc,  inc,
				crap, ek, gcount , blobs, boost, boosting;

		
typedef struct {
	int x;
	int y;
	int d;
	int nd;
	int s;
	int os;
	int ox;
	int oy;
	int m;
	bool ded;

	bool open;
} CrazeeSpod ;

CrazeeSpod spod;

typedef struct  {
	int x;
	int y;
	int ld;
	int d;
	int p;
	int ox;
	int oy;
	int m;
	int a;
	int s;
	int os;

} Ghost;

 int secx[99][99] ;
 int secy[99][99] ;
 int squaren[99][99] ;
 
 int sghost, tghost, lghost, rghost, levx, levy;
 
 Ghost sghosts[50] ;

 Ghost tghosts[50] ;

Ghost lghosts[50] ;

 Ghost rghosts[50] ;

 void newGhost(Ghost *ghost  , int sx, int sy, int sa, int sd, int sp, int sm, int ss,
			int sox, int soy);
			
			void powerp(Ghost *ghost) ;

void getlevel(void) ;


void getplots(void);

void dokeys(void);

void dospod(void);

bool hitme(int gx, int gy, int px, int py);

void checkbite(void);

void doDraw(void);

void dorghosts(void);

void dolghosts(void);

void dotghosts(void);

void dosghosts(void); 


 void doFloor(void) ;
 
 void getghosts(void );
 
 
int gamestate;



bool ul_down,dl_down,ur_down,dr_down;





