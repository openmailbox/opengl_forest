OBJS = main.cpp tree.o
LIBS = -lGL -lGLU -lglut 
CC = g++ 
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

FPSTest : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o FPSTest

tree.o : tree.h tree.cpp
	$(CC) $(CFLAGS) tree.cpp $(LIBS)

clean:
	\rm *.o FPSTest
