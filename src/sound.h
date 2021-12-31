/*
 * Copyright 2010, Neil White. All rights reserved.
 * Distributed under the terms of the GPL V 2 License.
 *
 * Authors:
 *      Neil White <neil@cloudsprinter.com>
 */


#include <SDL/SDL_mixer.h>

Mix_Chunk *bg_sound,*blib_sound,*die_sound,*ghost_sound,*powerp_sound;


void setvolume(int vol);

int sound_on;

void initandloadsounds();

void play_sound(int sound);


