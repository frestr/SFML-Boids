CXX=g++
CPPFLAGS=-std=c++11 -c
LDFLAGS=-g
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system -lpthread

SRCS=$(wildcard src/*.cpp)
OBJS=$(notdir $(SRCS:.cpp=.o))

all: sfml-boids

sfml-boids: $(OBJS)
	$(CXX) -o sfml-boids $(OBJS) $(LDLIBS)

%.o: src/%.cpp
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $< 

clean:
	$(RM) $(OBJS)
