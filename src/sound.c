/*
 * Copyright 2010, Neil White. All rights reserved.
 * Distributed under the terms of the GPL V 2 License.
 *
 * Authors:
 *      Neil White <neil@cloudsprinter.com>
 */


#include <SDL/SDL_mixer.h>
#include "sound.h"
#include "main.h"


void initandloadsounds()
{


 #ifdef NOSOUND
  #else

  if ( Mix_OpenAudio(44100, AUDIO_S16, 2, 4096) < 0 )
  {  /* Cant open sound so just run in quiet mode */ sound_on=0;}
  else
  {

    char path[256];
    
    strcpy(path,DATA_PREFIX);
    strcat(path,"sfx/bg.ogg");

    bg_sound = Mix_LoadWAV_RW(SDL_RWFromFile(path, "rb"), 1);
    strcpy(path,DATA_PREFIX);
    strcat(path,"sfx/blib.ogg");
    blib_sound = Mix_LoadWAV_RW(SDL_RWFromFile(path, "rb"), 1);
     strcpy(path,DATA_PREFIX);
     strcat(path,"sfx/die.ogg");
    die_sound = Mix_LoadWAV_RW(SDL_RWFromFile(path, "rb"), 1);
     strcpy(path,DATA_PREFIX);
     strcat(path,"sfx/ghost.ogg");
    ghost_sound = Mix_LoadWAV_RW(SDL_RWFromFile(path, "rb"), 1);
   strcpy(path,DATA_PREFIX);
     strcat(path,"sfx/powerp.ogg");
    powerp_sound = Mix_LoadWAV_RW(SDL_RWFromFile(path, "rb"), 1);
    sound_on=1;

  }
  
#endif
}

void setvolume(int vol)
{
  Mix_VolumeChunk(blib_sound,vol);
  Mix_VolumeChunk(powerp_sound,vol);
   Mix_VolumeChunk(ghost_sound,vol);
     Mix_VolumeChunk(die_sound,vol);
       Mix_VolumeChunk(bg_sound,vol);
}


void play_sound(int sound)
{
     //sound_on=0;
 
  #ifdef NOSOUND
  #else
   if ( sound==1  ) Mix_PlayChannel(-1 ,blib_sound,0) ;
     if ( sound==2  ) Mix_PlayChannel(-1 ,die_sound,0) ;
          if ( sound==3  ) Mix_PlayChannel(-1 ,ghost_sound,0) ;
             if ( sound==4  ) Mix_PlayChannel(-1 ,powerp_sound,0) ;
               if ( sound==5  ) Mix_PlayChannel(-1 ,bg_sound,0) ;
  #endif
}

