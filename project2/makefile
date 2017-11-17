# Makefile for CPS222 Project 2
# There are three targets that can be made
# student (the default) compiles the student version of the program with executable
#  placed in file project2
# instructor compiles the instructor version of the program into directory instructor,
#  with executable placed in file instructor_project2, and output to test student 
# output against in proj2.out
# distribution creates the distribution to be given to the students in folder project2

student: expression.cc expression.h
	g++ -o project2.exe expression.cc project2.obj
	
instructor: instructor_expression.cc expression.h project2.o
	rm -rf ../instructor
	mkdir ../instructor
	g++ -o ../instructor/instructor_project2 instructor_expression.cc project2.o
	../instructor/instructor_project2 < proj2.in > ../instructor/proj2.out
	../instructor/instructor_project2 < proj2e.in > ../instructor/proj2e.out
	../instructor/instructor_project2 < proj2p.in > ../instructor/proj2p.out
	
distribution: expression.cc expression.h project2.cc
	echo 'Be sure this is being done on the architecture students will use in the lab'
	rm -rf ../project2
	mkdir ../project2
	g++ -c project2.cc
	cp expression.cc ../project2
	cp expression.h ../project2
	mv project2.o ../project2
	cp makefile ../project2
	cp proj2.in ../project2
	cp proj2e.in ../project2
	cp proj2p.in ../project2
	chmod -R a+rX ../project2
