IDIR = include
CFLAGS = -I $(IDIR)
LIBS = -L lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2
ODIR = .
SRCDIR = src

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = texture.o tile.o board.o game.o
OBJ = $(patsubst %,$(SRCDIR)/%,$(_OBJ))

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	g++ -c -o $@ $< $(CFLAGS) $(LIBS)

all: main

main: $(OBJ)
	g++ src/main.cpp -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	del main.exe
	del src\*.o

etags: 
	find . -type f -iname "*.[ch]"  xargs etags --append  