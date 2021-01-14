//
// Created by spl211 on 04/01/2021.
//

#ifndef SPL_HW3_SEMIUSERCONNECTION_H
#define SPL_HW3_SEMIUSERCONNECTION_H


#include "regConnectionHandler.h"
#include <iostream>
#include <mutex>
#include "regConnectionHandler.h"


class SemiUserConnection{
private:
    std::mutex & _mutex;
    ConnectionHandler& connectionHandler;
    bool &shouldTerminate;
    bool &loggedIn;
    string name;
public:
    SemiUserConnection (std::mutex& mutex, ConnectionHandler& connectionHandler,bool &shouldTerminate, bool &loggedIn, string name);
    void run();
};

#endif //SPL_HW3_SEMIUSERCONNECTION_H
