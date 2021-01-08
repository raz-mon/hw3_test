#include "../include/ServerConnection.h"
#include "../include/regConnectionHandler.h"
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

ServerConnection::ServerConnection (std::mutex& mutex, ConnectionHandler& connectionHandler, bool &shouldTerminate, bool &loggedIn) :
        _mutex(mutex), connectionHandler(connectionHandler), shouldTerminate(shouldTerminate), loggedIn(loggedIn) {
}

void ServerConnection::run(){
    lock_guard<mutex> lock(_mutex);
    while (!shouldTerminate) {
        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine(answer)) {
            cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
//        int len;
//        len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
//       answer.resize(len-1);
        ConnectionHandler::process(answer);
        if (op(answer) == 3)
            loggedIn = true;
        if(op(answer) == 4){
            shouldTerminate = true;
            break;
        }
    }
}

short ServerConnection::op(string in){
    if(in.substr(0,2) == "13")
        return 0;
    string tmp = in.substr(2);
    unsigned short op;
    char szPort[tmp.length()];
    strcpy(szPort, tmp.c_str());
    sscanf(szPort, "%hi", &op);
    return op;
}