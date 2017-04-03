CC=g++
LDFLAGS= 
CPPFLAGS= -Wall -std=c++11 

SOURCEDIR=src
BUILDDIR=build

EXECUTABLE= dangerous-maze 
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

LINKS= 

all: dir $(EXECUTABLE)

dir:
	    mkdir -p $(BUILDDIR)

$(EXECUTABLE): $(OBJECTS)
	    $(CC) $(LDFLAGS) $^ $(LINKS) -o $@ 

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	    $(CC) $(CPPFLAGS) -c $< -o $@ 

clean:
	    rm -f $(BUILDDIR)/*o $(EXECUTABLE)
