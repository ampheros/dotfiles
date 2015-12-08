pong:	pong.o as1.o gradeHelper.o
	g++ -o pong as1.o pong.o gradeHelper.o -l ncurses

pong.o:	pong.cpp
	g++ -c pong.cpp

as1.o:	as1.cpp
	g++ -c as1.cpp

soln1.o:	soln1.cpp
	g++ -c soln1.cpp

gradeHelper.o:	gradeHelper.cpp
	g++ -c gradeHelper.cpp

gradeHelperSoln.o:	gradeHelperSoln.cpp
	g++ -c gradeHelperSoln.cpp

soln: 	pong.o soln1.o gradeHelper.o
	g++ -o pongSoln pong.o soln1.o gradeHelper.o -l ncurses

student: pong.o as1.o gradeHelperSoln.o
	g++ -o spong pong.o as1.o gradeHelperSoln.o -l ncurses

clean: 
	rm *.o

