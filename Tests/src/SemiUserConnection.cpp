//
// Created by spl211 on 04/01/2021.
//

#include "../include/SemiUserConnection.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <utility>

#include <random>

SemiUserConnection::SemiUserConnection (std::mutex& mutex, ConnectionHandler& connectionHandler,bool &shouldTerminate, bool &loggedIn, string name) :
        _mutex(mutex), connectionHandler(connectionHandler), shouldTerminate(shouldTerminate), loggedIn(loggedIn), name(std::move(name)) {}

void SemiUserConnection::run() {
    //Registaring to system
    string line("STUDENTREG " + name + " " + name);
    string encodedLine = ConnectionHandler::enc(line);
    if (encodedLine.empty())
        return;
    cout << "Client "+ name + ": " + line << endl;
    if (!connectionHandler.sendLine(encodedLine)) {
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }

    //Loging to system
    line = "LOGIN " + name + " " + name;
    encodedLine = ConnectionHandler::enc(line);
    if (encodedLine.empty())
        return;
    cout << "Client "+ name + ": " + line << endl;
    if (!connectionHandler.sendLine(encodedLine)) {
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }

    //generating random numbers for Course Reg
    //random_device rd;
    //mt19937 mt(rd());
    //uniform_real_distribution<double> dist(1.0, 45.0);      //generating numbers between 1 to 45
    for(int i = 1; i <= 45; i++){
        line = "KDAMCHECK " + to_string(i);
        encodedLine = ConnectionHandler::enc(line);
        if (encodedLine.empty())
            return;
        cout << "Client "+ name + ": " + line << endl;
        if (!connectionHandler.sendLine(encodedLine)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            return;
        }

        line = "ISREGISTERED " + to_string(i);
        encodedLine = ConnectionHandler::enc(line);
        if (encodedLine.empty())
            return;
        cout << "Client "+ name + ": " + line << endl;
        if (!connectionHandler.sendLine(encodedLine)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            return;
        }


        //int courseNum = dist(mt);
        line = "COURSEREG " + to_string(i);
        encodedLine = ConnectionHandler::enc(line);
        if (encodedLine.empty())
            return;
        cout << "Client "+ name + ": " + line << endl;
        if (!connectionHandler.sendLine(encodedLine)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            return;
        }


        line = "ISREGISTERED " + to_string(i);
        encodedLine = ConnectionHandler::enc(line);
        if (encodedLine.empty())
            return;
        cout << "Client "+ name + ": " + line << endl;
        if (!connectionHandler.sendLine(encodedLine)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            return;
        }

        /*
        if(i > 5){
            line = "UNREGISTER " + to_string(i - 5);
            encodedLine = ConnectionHandler::enc(line);
            if (encodedLine.empty())
                return;
            cout << "Client "+ name + ": " + line << endl;
            if (!connectionHandler.sendLine(encodedLine)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                return;
            }
        }
         */

        line = "MYCOURSES";
        encodedLine = ConnectionHandler::enc(line);
        if (encodedLine.empty())
            return;
        cout << "Client "+ name + ": " + line << endl;
        if (!connectionHandler.sendLine(encodedLine)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            return;
        }
    }

    //LOGOUT from client
    line = "LOGOUT";
    encodedLine = ConnectionHandler::enc(line);
    if (encodedLine.empty())
        return;
    cout << "Client "+ name + ": " + line << endl;
    if (!connectionHandler.sendLine(encodedLine)) {
        std::cout << "Disconnected. Exiting...\n" << std::endl;
        return;
    }

    if(loggedIn && encodedLine == "04"){
        lock_guard<mutex> lock(_mutex);
        return;
    }
}
