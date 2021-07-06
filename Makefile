find-duplicates: find-duplicates.o
	g++ $(CFLAGS) -o find-duplicates find-duplicates.o

find-duplicates.o: find-duplicates.cpp
	g++ $(CFLAGS) -c find-duplicates.cpp

clean:
	rm -f *.o find-duplicates

