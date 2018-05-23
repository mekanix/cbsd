CXXFLAGS += -I/usr/local/include -std=c++11
CXXFILES != ls -1 *.cxx
LDFLAGS += -pthread
OBJECTS = $(CXXFILES:.cxx=.o)
PROGRAM = sock

.if !defined(V)
.SILENT:
.endif

.MAIN: all

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	echo "Generating sock"
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(PROGRAM)

.cxx.o:
	echo "Compiling $< ..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	echo "Removing $(OBJECTS) and $(PROGRAM)"
	rm -rf $(OBJECTS) $(PROGRAM)

.include <bsd.prog.mk>
