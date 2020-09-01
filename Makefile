# target: prerequisites ...
#     recipe

# Files
marinTatFiles = main.o \
				test.o \

# 1st target - Top of the tree
# Link all o (-c) files to binary exe
# marinTar: $(marinTatFiles)
#	g++ $(marinTatFiles) -o marinTar

# main.o: main.cpp
#	g++ -c main.cpp

# test.o: test.cpp
#	g++ -c test.cpp

# ---- ----
allDirs = -I sw/Reactor/if \
		  -I sw/Reactor/inc

allPreReq = main.o \
		    EventHandler.o \


myTarget: $(allPreReq)
	g++ $(allPreReq) -o projectX

main.o: sw/main.cpp
	g++ -c $(allDirs) sw/main.cpp

EventHandler.o: sw/Reactor/src/EventHandler.cpp
	g++ -c $(allDirs) sw/Reactor/src/EventHandler.cpp

# Clean
clean:
#	rm *.o marinTar projectX
	rm *.o projectX