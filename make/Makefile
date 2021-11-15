# INFO:
# /home/marin/dev/projectSirius

CXXFLAGS = -g -no-pie -std=c++17


# ---- Dirs ----
allDirs = -I ../sw/ActiveObject/if \
          -I ../sw/ActiveObject/inc \
          -I ../sw/Common/if \
		  -I ../sw/Common/inc \
		  -I ../sw/Mayers/if \
		  -I ../sw/Mayers/inc \
		  -I ../sw/Reactor/if \
		  -I ../sw/Reactor/inc \
		  -I ../sw/Services/if \
		  -I ../sw/Services/inc \

allPreReq = main.o \
            ActivationQueue.o \
			Scheduler.o \
			Servant.o \
			Proxy.o \
			ActObjMethods.o \
			CmdPrompt.o \
			Database.o \
			Log.o \
		    EventHandler.o \
			LoggingAcceptor.o \
		    Control.o \
			Service0.o \
			ThreadManager.o \

# target: prerequisites ...
#     recipe
Sirius: $(allPreReq)
	g++ -pthread $(CXXFLAGS) $(allPreReq) -o projectSirius

main.o: ../sw/main.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/main.cpp

# Active Object
ActivationQueue.o: ../sw/ActiveObject/src/ActivationQueue.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/ActiveObject/src/ActivationQueue.cpp
Scheduler.o: ../sw/ActiveObject/src/Scheduler.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/ActiveObject/src/Scheduler.cpp
Servant.o: ../sw/ActiveObject/src/Servant.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/ActiveObject/src/Servant.cpp
Proxy.o: ../sw/ActiveObject/src/Proxy.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/ActiveObject/src/Proxy.cpp
ActObjMethods.o: ../sw/ActiveObject/src/ActObjMethods.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/ActiveObject/src/ActObjMethods.cpp

# Common
CmdPrompt.o: ../sw/Common/src/CmdPrompt.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Common/src/CmdPrompt.cpp
Database.o: ../sw/Common/src/Database.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Common/src/Database.cpp
Log.o: ../sw/Common/src/Log.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Common/src/Log.cpp

# Mayers

# Reactor
EventHandler.o: ../sw/Reactor/src/EventHandler.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Reactor/src/EventHandler.cpp
LoggingAcceptor.o: ../sw/Reactor/src/LoggingAcceptor.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Reactor/src/LoggingAcceptor.cpp

# Services
Control.o: ../sw/Services/src/Control.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Services/src/Control.cpp
Service0.o: ../sw/Services/src/Service0.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Services/src/Service0.cpp
ThreadManager.o: ../sw/Services/src/ThreadManager.cpp
	g++ -c $(CXXFLAGS) $(allDirs) ../sw/Services/src/ThreadManager.cpp


# ---------
# UNIT TEST
# ---------

# < ---- BUILD INFO---->
# Build: make unitTest        // all - build test_sources 
# Execute: ./gmockTest

# Location of: libgmock.a and libgmock_main.a 
mockLibs = ../libs/GTestLibs

# google mock dirs
googleMockTest = -I ../libs/GTestLibs/googletest/googlemock/include \
				 -I ../libs/GTestLibs/googletest/googletest/include \

# test dirs
test_dirs = -I ../sw/UnitTest \

# position: libs/GTestLibs (cp libs in local lib folder)
# $ cp libgmock.a /usr/local/lib/
# $ cp libgmock_main.a /usr/local/lib/
gmock = -lgmock
gmock_main = -lgmock_main

# test sources
test_sources = ../sw/Mayers/src/Mayers.cpp \
			   ../sw/Mayers/src/MayersCh4.cpp \
			   ../sw/Mayers/src/Widget.cpp \
               ../sw/UnitTest/testMayers.cpp \
               ../sw/UnitTest/testMayersCh4.cpp \
               ../sw/UnitTest/testWidget.cpp \
               ../sw/Common/src/Database.cpp \

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
