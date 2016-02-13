CPPFLAGS=-std=c++11 -c
LDFLAGS=-g
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system

SRCS=main.cpp vector2.cpp boid.cpp boidmanager.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: sfml-boids

sfml-boids: $(OBJS)
	$(CXX) -o sfml-boids $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $< 

clean:
	$(RM) $(OBJS)
