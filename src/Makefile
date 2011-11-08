TARGET = gui
OBJS = sdlw.o  TButton.o  TGui.o  TGuiElement.o  TWindow.o TText.o TPage.o TTimer.o utils.o
CPP = g++
CFLAGS = -g -Wall -Wextra -Weffc++ -std=gnu++0x -O0
CFLAGS += `sdl-config --cflags --libs` `freetype-config --cflags --libs`
CFLAGS += -I/usr/local/include/SDL -L/usr/local/lib -lSDL_ttf

clean-all:
	make clean
	make all

all:$(TARGET)

.cpp.o:
	$(CPP) -c -o $@ $< $(CFLAGS) $(SDLINC)

gui: $(OBJS)
	$(CPP) -o $@ $^ $(CFLAGS) $(SDLINC) $(SDLLIB)

clean:
	rm -rf $(TARGET) $(OBJS) *.o
