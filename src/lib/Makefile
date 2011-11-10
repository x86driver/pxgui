TARGET = functor stl

CFLAGS = -Wall -Wextra -Weffc++ -g -std=gnu++0x

all:$(TARGET)

functor:functor.cpp functor.h
	g++ $(CFLAGS) -o $@ $<

stl:stl.cpp dstl.h
	g++ $(CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET) *.o
