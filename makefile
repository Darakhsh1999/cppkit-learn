CC = g++
CFLAGS = -O2 -march=native

.PHONY : all
all : \
	first_executable \
	second_executable \
	third_executable \


# this is a comment

# target_name : prerequisites
# 	recipe
first_executable : first_program.cpp
	g++ -o first_executable first_program.cpp

second_executable : second_program.cpp
	g++ -o second_executable first_program.cpp

# $@ = target_name , $< = first prerequisites, $^ = all prerequisites
third_exectuable : third_program.cpp
	$(CC) $(CFLAGS) -o $@ $<


.PHONY : clean
clean : 
	rm -rf \
		first_executable \
		second_program \
		third_exectuable
