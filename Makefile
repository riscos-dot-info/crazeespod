# Project: Bolobobot

VER = 0.2

CPP  = g++
CC   = gcc

OBJ  =  src/images.o  src/main.o src/engine.o src/sound.o $(RES)
LINKOBJ  =   src/images.o src/main.o  src/engine.o src/sound.o $(RES)

LIBS=`sdl-config --libs` -lSDL_image -lSDL_ttf -lSDL_gfx -lSDL_mixer
#'pkg-config --cflags librsvg-2.0' 'pkg-config --libs librsvg-2.0'

BIN  = ./CrazeeSpod
CFLAGS= -Wall  -DLGFX


RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before ./CrazeeSpod all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) -static $(LINKOBJ) -o "./CrazeeSpod" $(LIBS) -lpng -ljpeg -lfreetype -lvorbisidec -lz


src/images.o: src/images.c
	$(CC) -c src/images.c -o src/images.o $(CFLAGS)

src/main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o $(CFLAGS)
	
src/engine.o: src/engine.c
	$(CC) -c src/engine.c -o src/engine.o $(CFLAGS)

	
src/sound.o: src/sound.c
	$(CC) -c src/sound.c -o src/sound.o $(CFLAGS)

