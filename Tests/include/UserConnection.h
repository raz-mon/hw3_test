#ifndef SPL_HW3_USERCONNECTION_H
#define SPL_HW3_USERCONNECTION_H



#include <iostream>
#include <mutex>
#include "regConnectionHandler.h"

class UserConnection{
private:
    std::mutex & _mutex;
    ConnectionHandler& connectionHandler;
    bool &shouldTerminate;
    bool &loggedIn;
public:
    UserConnection (std::mutex& mutex, ConnectionHandler& connectionHandler,bool &shouldTerminate, bool &loggedIn);
    void run();
};

#endif //SPL_HW3_USERCONNECTION_H