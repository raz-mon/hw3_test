//
// Created by spl211 on 25/12/2020.
//
#include <stdlib.h>
#include "../include/regConnectionHandler.h"
#include "../include/ServerConnection.h"
#include "../include/UserConnection.h"
#include <mutex>
#include <thread>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }

    mutex mutex;
    bool shouldTerminate = false;
    bool loggedIn = false;
    ServerConnection SC(mutex, connectionHandler, shouldTerminate, loggedIn);
    UserConnection UC(mutex, connectionHandler, shouldTerminate, loggedIn);

    thread th1(&ServerConnection::run, &SC);
    thread th2(&UserConnection::run, &UC);

    th1.join();
    th2.join();

    return 0;
}
