#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any directories containing header files other than /usr/include
#
SOURCEDIR = src
INCLUDES = -Iinc -I/usr/include

# define any compile-time flags
CPPFLAGS = -Wall -g -pthread $(INCLUDES)  

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -pthread

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBPATH = -L/usr/lib/x86_64-linux-gnu
LIBS = -lncurses -lpthread -lstdc++


# define the C source files
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = menus

# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $(EXECUTABLE)  $^ $(LIBPATH) $(LIBS) 

clean:
	rm -f $(EXECUTABLE) $(SOURCEDIR)/*.o

