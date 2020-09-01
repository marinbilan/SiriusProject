# target: prerequisites ...
#     recipe

# Files
marinTatFiles = main.o \
				test.o \

# 1st target - Top of the tree
# Link all o (-c) files to binary exe
marinTar: $(marinTatFiles)
	g++ $(marinTatFiles) -o marinTar

main.o: main.cpp
	g++ -c main.cpp

test.o: test.cpp
	g++ -c test.cpp

# Clean
clean:
	rm *.o marinTar