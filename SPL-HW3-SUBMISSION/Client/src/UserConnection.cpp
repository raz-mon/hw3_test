#include "../include/UserConnection.h"
#include "../include/regConnectionHandler.h"
#include <thread>
#include <mutex>
#include <iostream>

UserConnection::UserConnection (std::mutex& mutex, ConnectionHandler& connectionHandler, bool &shouldTerminate, bool &loggedIn) :
        _mutex(mutex), connectionHandler(connectionHandler), shouldTerminate(shouldTerminate), loggedIn(loggedIn) {}

void UserConnection::run() {
    while (!shouldTerminate){
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        string encodedLine = ConnectionHandler::enc(line);
        if (encodedLine.empty())
            continue;

        if (!connectionHandler.sendLine(encodedLine)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        if(loggedIn && encodedLine == "04"){
            lock_guard<mutex> lock(_mutex);
            break;
        }
    }
}