LDLIBS += -lpcap

all: main

GPT: main.cpp

clean:
	rm -f main *.o