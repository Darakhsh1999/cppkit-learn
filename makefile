CC = g++
CFLAGS = -O2 -march=native -I/usr/include/eigen3

# Dummy variables that combines all targets
.PHONY : all
all : \
	data_loading_example \
	timer_example \
	eigen_example \


# target_name : prerequisites
# 	recipe

# $@ = target_name , $< = first prerequisites, $^ = all prerequisites

data_loading_example : examples/data_loading_example.cpp csv_reader.cpp
	$(CC) $(CFLAGS) -o $@ $^

timer_example : examples/timer_example.cpp timer.cpp
	$(CC) $(CFLAGS) -o $@ $^

eigen_example : examples/eigen_example.cpp
	$(CC) $(CFLAGS) -o $@ $<


.PHONY : clean
clean : 
	rm -rf \
		data_loading_example \
		timer_example \
		eigen_example \
