SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
EXES = $(patsubst %.cc, %.out, $(wildcard *.cc))
EXE_OBJS = $(patsubst %.cc, %.o, $(wildcard *.cc))
DEPENDS = $(patsubst %.cc, %.d, $(wildcard *.cc))
DEPENDS += $(patsubst %.cpp, %.d, $(wildcard *.cpp))

CXX = g++
CFLAGS = -g -Wall -O0 -pedantic
LFLAGS =

.SUFFIXES : .cpp .o .cc .d

all : $(EXES)

$(EXES) :
#all : $(DEPENDS)


clean :
	rm -f $(OBJS) $(EXES) $(EXE_OBJS) $(DEPENDS)

#ifneq ($(MAKECMDGOALS), clean)
-include $(DEPENDS)
#endif

.cpp.d :
	$(CXX) -MM -MG "$<" | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@' > $@	

.cc.d : 
	$(CXX) -MM -MG "$<" | sed -e 's@^\(.*\)\.o:@\1.d \1.o:@' > $@	

.cpp.o :
	$(CXX) $(CFLAGS) -c -o $@ $<

.cc.o :
	$(CXX) $(CFLAGS) -c -o $@ $<

%.out : %.o $(OBJS)
	$(CXX) $(CFLAGS) $(LFLAGS) -o $@ $^
