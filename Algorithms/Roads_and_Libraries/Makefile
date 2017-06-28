algo_libraries.exe: algo_libraries.o
	g++ -Wall -Werror algo_libraries.o -o algo_libraries.exe 
	./algo_libraries.exe < test.txt
	./algo_libraries.exe < input10.txt
	
algo_libraries.o: algo_libraries.cpp
	g++ -g -Wall -Werror -c algo_libraries.cpp
	
clean:
	rm *.o *.exe