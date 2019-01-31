#Makefile for building the guessing game
CC = 'g++'
FLAGS= -c -std=c++17
LINKFLAGS =''
LINKMSG = 'Linking object files...'
COMPILEMSG = 'Compiling $^...'

all: organizer

#splash_screen: splash_screen.cpp
#	@echo $(COMPILEMSG) 
#	@$(CC) splash_screen.cpp $(LINKFLAGS) -o game 

organizer: utilities controller main book course
	@echo $(LINKMSG) 
	@$(CC) utilities.o controller.o main.o course.o book.o -o textbook_organizer 

utilities: utilities.cpp
	@echo $(COMPILEMSG)
	@$(CC) $(FLAGS) utilities.cpp 
controller: controller.cpp
	@echo $(COMPILEMSG)
	@$(CC) $(FLAGS) controller.cpp 

book: book.cpp
	@echo $(COMPILEMSG)
	@$(CC) $(FLAGS) book.cpp 
course: course.cpp
	@echo $(COMPILEMSG)
	@$(CC) $(FLAGS) course.cpp 

main: main.cpp
	@echo $(COMPILEMSG)
	@$(CC) $(FLAGS) main.cpp 
clean:
	@echo "Cleaning files..."
	-@rm *.o textbook_organizer 2> /dev/null
