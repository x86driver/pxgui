TARGET = gui
OBJS = sdlw.o  TButton.o  TGui.o  TGuiElement.o  TWindow.o
CPP = g++
CFLAGS = `sdl-config --cflags --libs`

all:$(TARGET)

.cpp.o:
	$(CPP) $(CFLAGS) -c -o $@ $<

gui: $(OBJS)
	$(CPP) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(TARGET) $(OBJS) *.o
