//
// Created by spl211 on 04/01/2021.
//

#ifndef SPL_HW3_CLIENT_H
#define SPL_HW3_CLIENT_H

#include <string>
#include "../../include/ServerConnection.h"
#include "SemiUserConnection.h"

using namespace std;

class Client{
private:
    int index;
    string host;
    short port;
    string name;

public:
    Client (int index, string host, short port, string name);
    void run();
};


#endif //SPL_HW3_CLIENT_H
