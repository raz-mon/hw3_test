CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread

all: clean registrationClient
	g++ -o bin/BGRSclient bin/regConnectionHandler.o bin/registrationClient.o bin/regHelpers.o  bin/ServerConnection.o bin/UserConnection.o $(LDFLAGS)

registrationClient: bin/regConnectionHandler.o bin/registrationClient.o bin/regHelpers.o bin/ServerConnection.o bin/UserConnection.o

bin/regConnectionHandler.o: src/regConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/regConnectionHandler.o src/regConnectionHandler.cpp

bin/registrationClient.o: src/registrationClient.cpp
	g++ $(CFLAGS) -o bin/registrationClient.o src/registrationClient.cpp

bin/regHelpers.o: src/regHelpers.cpp
	g++ $(CFLAGS) -o bin/regHelpers.o src/regHelpers.cpp

bin/ServerConnection.o: src/ServerConnection.cpp
	g++ $(CFLAGS) -o bin/ServerConnection.o src/ServerConnection.cpp

bin/UserConnection.o: src/UserConnection.cpp
	g++ $(CFLAGS) -o bin/UserConnection.o src/UserConnection.cpp

.PHONY: clean
clean:
	rm -f bin/*
