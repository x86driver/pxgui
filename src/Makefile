TARGET = gui
OBJS = sdlw.o  TButton.o  TGui.o  TGuiElement.o  TWindow.o TText.o font_8x8.o utils.o
CPP = g++
CFLAGS = -g -Wall -Wextra
CFLAGS += `sdl-config --cflags --libs` `freetype-config --cflags --libs`

all:$(TARGET)

.cpp.o:
	$(CPP) -c -o $@ $< $(CFLAGS) $(SDLINC)

gui: $(OBJS)
	$(CPP) -o $@ $^ $(CFLAGS) $(SDLINC) $(SDLLIB)

clean:
	rm -rf $(TARGET) $(OBJS) *.o
