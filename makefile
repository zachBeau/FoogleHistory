
CXX = g++
CXXFLAGS = -g

# "make RELEASE=1" turns off DEBUG_LOG and assert
ifdef RELEASE
CXXFLAGS = -O2 -DNDEBUG
endif

run: foogle.exe
	./foogle.exe

foogle.exe: main.o A3List.o A3Deque.o
	$(CXX) main.o A3List.o A3Deque.o -o foogle.exe

main.o: main.cpp A3Node.h A3List.h A3Deque.h
	$(CXX) $(CXXFLAGS) -c main.cpp

A3List.o: A3List.cpp A3Node.h A3List.h A3Deque.h
	$(CXX) $(CXXFLAGS) -c A3List.cpp

A3Deque.o: A3Deque.cpp A3Node.h A3Deque.h
	$(CXX) $(CXXFLAGS) -c A3Deque.cpp

clean:
	rm -f *.o foogle.exe