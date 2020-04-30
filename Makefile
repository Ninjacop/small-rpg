main:
	g++ -std=c++17 *.cpp ./state_machine/*.cpp ./characters/*.cpp ./loop_machine/*.cpp -o main

windows:
	g++ -std=c++17 *.cpp ./state_machine/*.cpp ./characters/*.cpp ./loop_machine/*.cpp -o main.exe

debug:
	g++ -ggdb -std=c++17 *.cpp ./state_machine/*.cpp -o debug

clean:
	rm -rf main debug

clean_main:
	rm -rf main