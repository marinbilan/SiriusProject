CXXFLAGS = -g -no-pie -std=c++14

# Files
marinTatFiles = main.o \
				test.o \

# ---- ----
allDirs = -I sw/Reactor/if \
		  -I sw/Reactor/inc

allPreReq = main.o \
		    EventHandler.o \

# target: prerequisites ...
#     recipe
myTarget: $(allPreReq)
	g++ $(allPreReq) -o projectX

main.o: sw/main.cpp
	g++ -c $(allDirs) sw/main.cpp

EventHandler.o: sw/Reactor/src/EventHandler.cpp
	g++ -c $(allDirs) sw/Reactor/src/EventHandler.cpp

# ---------
# UNIT TEST
# ---------

# < ---- BUILD INFO---->
# Build: make unitTest        // all - build test_sources 
# Execute: ./gmockTest

# Location of: libgmock.a and libgmock_main.a 
mockLibs = libs/GTestLibs

# google mock dirs
googleMockTest = -I libs/GTestLibs/googletest/googlemock/include \
				 -I libs/GTestLibs/googletest/googletest/include \

# test dirs
test_dirs = -I sw/UnitTest \

# position: libs/GTestLibs (cp libs in local lib folder)
# $ cp libgmock.a /usr/local/lib/
# $ cp libgmock_main.a /usr/local/lib/
gmock = -lgmock
gmock_main = -lgmock_main

# test sources
test_sources = sw/Reactor/src/EventHandler.cpp \
               sw/UnitTest/testEventHandler.cpp \

unitTest:
	g++ $(CXXFLAGS) \
	-L $(mockLibs) \
	$(allDirs) \
	$(googleMockTest) \
	$(test_dirs) \
	$(gmock) \
	$(gmock_main) \
	$(test_sources) \
	-pthread  \
	-o gmockTest \

# Clean
clean:
	rm *.o marinTar projectX gmockTest