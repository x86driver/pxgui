TARGET = gui
OBJS = sdlw.o  TButton.o  TGui.o  TGuiElement.o  TWindow.o TText.o TPage.o TTimer.o TScreen.o TCanvas.o utils.o RGBPage.o GeneralInfo.o
CPP = g++
CFLAGS = -g -Wall -Wextra -std=gnu++0x
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
