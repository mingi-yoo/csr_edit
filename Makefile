all: edit.cpp
	g++ -o csr edit.cpp

clean:
	rm -r -f csr
