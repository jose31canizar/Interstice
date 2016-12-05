# Interstice
EXE=final

# Main target
all: $(EXE)



#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
CLEAN=del *.exe *.o *.a *.txt
SDL_CFLAGS=-IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows
SDL_LDFLAGS=-lmingw32 -lSDL2main -lSDL2
else
#  OSX
ifeq "$(shell uname)" "Darwin"
#CONFF=$(shell $(sdl2-config --cflags))
#CONFL=$(shell $(sdl2-config --libs))
#SDL_CFLAGS :=`sdl2-config --cflags SDL2_ttf-config --cflags`
#SDL_LDFLAGS :=`sdl2-config --libs SDL2_ttf-config --libs`
# -I/usr/include/SDL2 -D_THREAD_SAFE
#
#CFLG=-O3 -Wall -Wno-deprecated-declarations -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -F/Library/Frameworks -framework OpenGL
CFLG=-O3 -Wall -Wno-deprecated-declarations -I SDL2.framework/Headers -F/Library/Frameworks -framework OpenGL -I /Library/Frameworks/Headers

SDL_CFLAGS=-I/usr/local/include -L/usr/local/lib
SDL_LDFLAGS=-lSDL2
#  Linux/Unix/Solaris
else
CFLG=-Wall -lSDL2 -lGLU -lGL -lm -lglut -I/usr/local/include -L/usr/local/lib
SDL_CFLAGS= `sdl2-config --cflags`
SDL_LDFLAGS= `sdl2-config --libs`
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a *.txt
endif

# Dependencies
errcheck.o: errcheck.c CSCIx229.h
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
printsdl.o: printsdl.c CSCIx229.h
project.o: project.c CSCIx229.h
character.o: objects/character.c objects/character.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
bezier.o: objects/bezier.c objects/bezier.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
floors.o: objects/floors.c objects/floors.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
parts.o: objects/parts.c objects/parts.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
jars.o: objects/jars.c objects/jars.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
balusters.o: objects/balusters.c objects/balusters.h objects/bezier.h objects/parts.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
columns.o: objects/columns.c objects/columns.h objects/parts.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
randomizer.o: utility/randomizer.c utility/randomizer.h utility/balusters.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
save_progress.o: utility/save_progress.c utility/save_progress.h utility/randomizer.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h
collision.o: utility/collision.c utility/collision.h utility/randomizer.h
		gcc -c $< $(CFLG)-o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS) ../setup/GL.h


#Create Archive
CSCIx229.a: fatal.o loadtexbmp.o print.o project.o errcheck.o object.o
	ar -rcs $@ $^
#
main.o: main.c CSCIx229.h

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
# -lSDL -lSDL_mixer -lGLU -lGL -lm
final: main.o CSCIx229.a objects/character.o objects/floors.o objects/parts.o objects/jars.o objects/bezier.o objects/balusters.o objects/columns.o utility/randomizer.o utility/save_progress.o utility/collision.o
	gcc main.c objects/character.c objects/floors.c objects/parts.c objects/jars.c objects/bezier.c objects/balusters.c objects/columns.c utility/randomizer.c utility/save_progress.c utility/collision.c CSCIx229.a $(CFLG) -o $@ $(SDL_CFLAGS) $(SDL_LDFLAGS)

#  Clean
clean:
	$(CLEAN)
