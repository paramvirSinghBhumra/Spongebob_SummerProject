# Spongebob Project
EXE=main

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
fatal.o: fatal.c helperFunctions.h
loadtexbmp.o: loadtexbmp.c helperFunctions.h
print.o: print.c helperFunctions.h
project.o: project.c helperFunctions.h
errcheck.o: errcheck.c helperFunctions.h
object.o: object.c helperFunctions.h

#  Create archive
helperFunctions.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o 
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
main:main.o helperFunctions.a
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)
