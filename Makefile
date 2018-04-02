### Creates the .so library. Name: rational.so

# Compilers and flags
CCC = g++-7  #g++ 7+ version
CXX = g++-7
BASICOPTS = -g -Wall -Werror -std=c++14 -fPIC
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN = 


# Target directory
TARGETDIR_rational.so=GNU-amd64-Linux


all: $(TARGETDIR_rational.so)/rational.so

## Target: rational.so
CCFLAGS_rational.so = 
OBJS_rational.so =  \
	$(TARGETDIR_rational.so)/main.o \
	$(TARGETDIR_rational.so)/tests.o \
	$(TARGETDIR_rational.so)/utils.o \
	$(TARGETDIR_rational.so)/rational.o


SHAREDLIB_FLAGS_rational.so = -shared 
$(TARGETDIR_rational.so)/rational.so: $(TARGETDIR_rational.so) $(OBJS_rational.so) 
	$(CXX) $(CXXFLAGS) $(CCFLAGS_rational.so) $(CPPFLAGS_rational.so) -o $@ $(OBJS_rational.so) $(SHAREDLIB_FLAGS_rational.so) $(LDLIBS_rational.so)

# Source files .o
$(TARGETDIR_rational.so)/main.o: $(TARGETDIR_rational.so) main.cpp
	$(CXX) $(CXXFLAGS) -c $(CCFLAGS_rational.so) $(CPPFLAGS_rational.so) -o $@ main.cpp

$(TARGETDIR_rational.so)/tests.o: $(TARGETDIR_rational.so) tests.cpp
	$(CXX) $(CXXFLAGS) -c $(CCFLAGS_rational.so) $(CPPFLAGS_rational.so) -o $@ tests.cpp

$(TARGETDIR_rational.so)/utils.o: $(TARGETDIR_rational.so) utils.cpp
	$(CXX) $(CXXFLAGS) -c $(CCFLAGS_rational.so) $(CPPFLAGS_rational.so) -o $@ utils.cpp

$(TARGETDIR_rational.so)/rational.o: $(TARGETDIR_rational.so) rational.cpp
	$(CXX) $(CXXFLAGS) -c $(CCFLAGS_rational.so) $(CPPFLAGS_rational.so) -o $@ rational.cpp


clean:
	rm -f \
		$(TARGETDIR_rational.so)/rational.so \
		$(TARGETDIR_rational.so)/main.o \
		$(TARGETDIR_rational.so)/tests.o \
		$(TARGETDIR_rational.so)/utils.o \
		$(TARGETDIR_rational.so)/rational.o
	$(CCADMIN)
	rm -f -r $(TARGETDIR_rational.so)


# Create target dorectory, if necessary
$(TARGETDIR_rational.so):
	mkdir -p $(TARGETDIR_rational.so)

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

