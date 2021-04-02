
#Definitions

CXX=g++
CXXFLAGS=-g -Wall -std=c++11
CCLINK=g++
LIBS=
OBJS=main.o func.o polynom.o compfunc.o
RM=rm -f
TARGET = Polynomer

$(TARGET) : $(OBJS)
	  $(CCLINK) -o $(TARGET) $(OBJS) $(LIBS)

#Dependencies

main.o: main.cpp func.h polynom.h compfunc.h
compfunc.o: compfunc.cpp compfunc.h func.h
func.o: func.cpp func.h
polynom.o: polynom.cpp polynom.h func.h


#Clean

clean:
	  $(RM) game *.o *.bak *~ "#"* core
