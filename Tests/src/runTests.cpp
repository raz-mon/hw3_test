//
// Created by spl211 on 04/01/2021.
//

#include "../include/runTests.h"
#include <stdlib.h>
#include "../include/regConnectionHandler.h"
#include "../include/ServerConnection.h"
#include "../include/SemiUserConnection.h"
#include "../include/Client.h"
#include "../../include/UserConnection.h"
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

    Client C1(1, host, port, "A1");
    Client C2(2, host, port, "A2");
    Client C3(3, host, port, "A3");
    Client C4(4, host, port, "A4");
    Client C5(5, host, port, "A5");
    Client C6(6, host, port, "A6");
    Client C7(7, host, port, "A7");
    Client C8(8, host, port, "A8");
    Client C9(9, host, port, "A9");
    //Client C10(10, host, port, "A10");
    Client C11(11, host, port, "A11");
    Client C12(12, host, port, "A12");
    Client C13(13, host, port, "A13");
    Client C14(14, host, port, "A14");
    Client C15(15, host, port, "A15");
    Client C16(16, host, port, "A16");
    Client C17(17, host, port, "A17");
    Client C18(18, host, port, "A18");
    Client C19(19, host, port, "A19");
    //Client C20(20, host, port, "A20");
    Client C21(21, host, port, "A21");
    Client C22(22, host, port, "A22");
    Client C23(23, host, port, "A23");
    Client C24(24, host, port, "A24");
    Client C25(25, host, port, "A25");
    Client C26(26, host, port, "A26");
    Client C27(27, host, port, "A27");
    Client C28(28, host, port, "A28");
    Client C29(29, host, port, "A29");
    //Client C30(30, host, port, "A30");
    Client C31(31, host, port, "A31");
    Client C32(32, host, port, "A32");
    Client C33(33, host, port, "A33");
    Client C34(34, host, port, "A34");
    Client C35(35, host, port, "A35");
    Client C36(36, host, port, "A36");
    Client C37(37, host, port, "A37");
    Client C38(38, host, port, "A38");
    Client C39(39, host, port, "A39");
    //Client C40(40, host, port, "A40");

    thread th1(&Client::run, &C1);
    thread th2(&Client::run, &C2);
    thread th3(&Client::run, &C3);
    thread th4(&Client::run, &C4);
    thread th5(&Client::run, &C5);
    thread th6(&Client::run, &C6);
    thread th7(&Client::run, &C7);
    thread th8(&Client::run, &C8);
    thread th9(&Client::run, &C9);
    //thread th10(&Client::run, &C10);
    thread th11(&Client::run, &C11);
    thread th12(&Client::run, &C12);
    thread th13(&Client::run, &C13);
    thread th14(&Client::run, &C14);
    thread th15(&Client::run, &C15);
    thread th16(&Client::run, &C16);
    thread th17(&Client::run, &C17);
    thread th18(&Client::run, &C18);
    thread th19(&Client::run, &C19);
    //thread th20(&Client::run, &C20);
    thread th21(&Client::run, &C21);
    thread th22(&Client::run, &C22);
    thread th23(&Client::run, &C23);
    thread th24(&Client::run, &C24);
    thread th25(&Client::run, &C25);
    thread th26(&Client::run, &C26);
    thread th27(&Client::run, &C27);
    thread th28(&Client::run, &C28);
    thread th29(&Client::run, &C29);
    //thread th30(&Client::run, &C30);
    thread th31(&Client::run, &C31);
    thread th32(&Client::run, &C32);
    thread th33(&Client::run, &C33);
    thread th34(&Client::run, &C34);
    thread th35(&Client::run, &C35);
    thread th36(&Client::run, &C36);
    thread th37(&Client::run, &C37);
    thread th38(&Client::run, &C38);
    thread th39(&Client::run, &C39);
    //thread th40(&Client::run, &C40);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
    //th10.join();
    th11.join();
    th12.join();
    th13.join();
    th14.join();
    th15.join();
    th16.join();
    th17.join();
    th18.join();
    th19.join();
    //th20.join();
    th21.join();
    th22.join();
    th23.join();
    th24.join();
    th25.join();
    th26.join();
    th27.join();
    th28.join();
    th29.join();
    //th30.join();
    th31.join();
    th32.join();
    th33.join();
    th34.join();
    th35.join();
    th36.join();
    th37.join();
    th38.join();
    th39.join();
    //th40.join();

    /*
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

    thread thADMIN1(&ServerConnection::run, &SC);
    thread thADMIN2(&UserConnection::run, &UC);

    th1.join();
    th2.join();
    */

    return 0;
}