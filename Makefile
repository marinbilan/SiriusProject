CXXFLAGS = -g -no-pie -std=c++14


# ---- Dirs ----
allDirs = -I sw/Common/if \
		  -I sw/Common/inc \
		  -I sw/Mayers/if \
		  -I sw/Mayers/inc \
		  -I sw/Reactor/if \
		  -I sw/Reactor/inc \
		  -I sw/Services/if \
		  -I sw/Services/inc \

allPreReq = main.o \
			CmdPrompt.o \
			Database.o \
		    EventHandler.o \
			LoggingAcceptor.o \
		    Control.o \

# target: prerequisites ...
#     recipe
Sirius: $(allPreReq)
	g++ $(allPreReq) -o projectSirius

main.o: sw/main.cpp
	g++ -c $(allDirs) sw/main.cpp
# Common
CmdPrompt.o: sw/Common/src/CmdPrompt.cpp
	g++ -c $(allDirs) sw/Common/src/CmdPrompt.cpp

Database.o: sw/Common/src/Database.cpp
	g++ -c $(allDirs) sw/Common/src/Database.cpp
# Mayers

# Reactor
EventHandler.o: sw/Reactor/src/EventHandler.cpp
	g++ -c $(allDirs) sw/Reactor/src/EventHandler.cpp
LoggingAcceptor.o: sw/Reactor/src/LoggingAcceptor.cpp
	g++ -c $(allDirs) sw/Reactor/src/LoggingAcceptor.cpp

# Services
Control.o: sw/Services/src/Control.cpp
	g++ -c $(allDirs) sw/Services/src/Control.cpp





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
test_sources = sw/Mayers/src/Mayers.cpp \
               sw/UnitTest/testMayers.cpp \

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
	rm *.o projectSirius gmockTest