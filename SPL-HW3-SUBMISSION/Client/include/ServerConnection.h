#ifndef SPL_HW3_SERVERCONNECTION_H
#define SPL_HW3_SERVERCONNECTION_H


#include <iostream>
#include <mutex>
#include "regConnectionHandler.h"

class ServerConnection{
private:
    std::mutex & _mutex;
    ConnectionHandler& connectionHandler;
    bool &shouldTerminate;
    bool &loggedIn;
public:
    ServerConnection (std::mutex& mutex, ConnectionHandler& connectionHandler,bool& shouldTerminate, bool &loggedIn);
    void run();
    short op(string in);
};

#endif //SPL_HW3_SERVERCONNECTION_H