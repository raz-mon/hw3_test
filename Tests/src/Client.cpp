//
// Created by spl211 on 04/01/2021.
//

#include "../include/Client.h"
#include <stdlib.h>
#include "../include/regConnectionHandler.h"
#include "../include/ServerConnection.h"
#include "../include/SemiUserConnection.h"
#include <mutex>
#include <thread>
#include <iostream>
#include <utility>

using namespace std;

Client::Client (int index, string host, short port, string name) :
        index(index), host(std::move(host)), port(port), name(std::move(name)) {
}

void Client::run(){
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return;
    }

    mutex mutex;
    bool shouldTerminate = false;
    bool loggedIn = false;
    ServerConnection SC(mutex, connectionHandler, shouldTerminate, loggedIn);
    SemiUserConnection SUC(mutex, connectionHandler, shouldTerminate, loggedIn, name);

    thread th1(&ServerConnection::run, &SC);
    thread th2(&SemiUserConnection::run, &SUC);

    th1.join();
    th2.join();
}