TARGET = gui
OBJS = sdlw.o  TButton.o  TGui.o  TGuiElement.o  TWindow.o TText.o font_8x8.o utils.o
CPP = g++
#CPP = droid-g++
CFLAGS = `sdl-config --cflags --libs` -g
#CFLAGS = -fno-exceptions -lc -lstdc++ -nostdlib
#SDLINC = -I/home/shane/pro/libsdl/SDL-1.2.14/include
#SDLLIB = -L/home/shane/pro/libsdl/SDL-1.2.14 -lSDL

all:$(TARGET)

.cpp.o:
	$(CPP) -c -o $@ $< $(CFLAGS) $(SDLINC)

gui: $(OBJS)
	$(CPP) -o $@ $^ $(CFLAGS) $(SDLINC) $(SDLLIB)

clean:
	rm -rf $(TARGET) $(OBJS) *.o
