CPPFLAGS = -std=c++11 -O3 -Wall -fPIC
INC = -I/usr/local/include
all:
	bash make_header_dict.sh
	g++ $(INC) $(CPPFLAGS) -o mkname main.cpp
