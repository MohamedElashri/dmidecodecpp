# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I..

# Source files
SOURCES = example1.cpp example2.cpp example3.cpp

# Executables
EXECUTABLES = $(SOURCES:.cpp=)

# Default target: build all examples
all: $(EXECUTABLES)

# Compile each source file into an executable
%: %.cpp ../dmidecode_parser.h
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run all examples
run: $(EXECUTABLES)
	@for exe in $(EXECUTABLES); do \
		echo "Running $$exe..."; \
		./$$exe; \
		echo ""; \
	done

# Run individual examples
run_example1: example1
	./example1

run_example2: example2
	./example2

run_example3: example3
	./example3

# Clean up generated files
clean:
	rm -f $(EXECUTABLES)
