TARGET = stl
CFLAGS = -Wall -Wextra -Weffc++ -g -std=gnu++0x

all:$(TARGET)

stl:stl.cpp
	g++ $(CFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET)
