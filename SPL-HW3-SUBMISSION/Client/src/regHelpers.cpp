//
// Created by spl211 on 26/12/2020.
//
#include "../include/regConnectionHandler.h"

using namespace std;

string ConnectionHandler::enc(string in){
    uint d1 = in.find(' ');
    string command = in.substr(0,d1);
    if (command == "ADMINREG"){
        string out("");
        out.append("01");
        uint d2 = (in.substr(d1+1,in.length()-d1)).find(' ');
        string part2(in.substr(d1+1,d2));
        out.append(part2);
        out.append(1,'\0');
        out.append(in.substr(d1+d2+2, in.length()-d1-d2-2));
        out.append(1,'\0');
        return out;
    }
    else if (command == "STUDENTREG"){
        string out("");
        out.append("02");
        uint d2 = (in.substr(d1+1,in.length()-d1)).find(' ');
        string part2(in.substr(d1+1,d2));
        out.append(part2);
        out.append(1,'\0');
        out.append(in.substr(d1+d2+2, in.length()-d1-d2-2));
        out.append(1,'\0');
        return out;
    }
    else if (command == "LOGIN"){
        string out("");
        out.append("03");
        uint d2 = (in.substr(d1+1,in.length()-d1)).find(' ');
        string part2(in.substr(d1+1,d2));
        out.append(part2);
        out.append(1,'\0');
        out.append(in.substr(d1+d2+2, in.length()-d1-d2-2));
        out.append(1,'\0');
        return out;
    }
    else if(command == "LOGOUT"){
        return "04";
    }
    else if (command == "COURSEREG") {
        string out("");
        out.append("05");
        string courseNum(char_disp(in.substr(d1 + 1, in.length() - d1 - 1)));
        out.append(courseNum);
        return out;
    }
    else if (command == "KDAMCHECK"){
        string out("");
        out.append("06");
        string courseNum(char_disp(in.substr(d1 + 1, in.length() - d1 - 1)));
        out.append(courseNum);
        return out;
    }
    else if (command == "COURSESTAT"){
        string out("");
        out.append("07");
        string courseNum(char_disp(in.substr(d1 + 1, in.length() - d1 - 1)));
        out.append(courseNum);
        return out;
    }
    else if (command == "STUDENTSTAT"){
        string out("");
        out.append("08");
        string part2(in.substr(d1+1,in.length()-1));
        out.append(part2);
        out.append(1,'\0');
        return out;
    }
    else if(command == "ISREGISTERED"){
        string out;
        out.append("09");
        string courseNum(char_disp(in.substr(d1 + 1, in.length() - d1 - 1)));
        out.append(courseNum);
        return out;
    }
    else if (command == "UNREGISTER"){
        string out("");
        out.append("10");
        string courseNum(char_disp(in.substr(d1 + 1, in.length() - d1 - 1)));
        out.append(courseNum);
        return out;
    }
    else if (command == "MYCOURSES"){
        return "11";
    }
    else{
        cout << "command not known by system.." << endl;
        return "";
    }
}

void ConnectionHandler::process(const string& in){

   string out;
   int ind = in.find('\0');
   if (ind != -1){
       out = "ACK ";
       out.append(in.substr(2,2));      // Append message op-code.
       if (in.substr(0,ind).length() != 4){
           out.append("\n");
           out.append(in.substr(4));
       }
   }
   else{
       out = "ERROR " + in.substr(2);
   }
    cout << out << endl;
}

string ConnectionHandler::char_disp(string basicString) {
    // convert from string to short.
    unsigned short cNum;
    char szPort[basicString.length()];
    strcpy(szPort, basicString.c_str());
    sscanf(szPort, "%hi", &cNum);
    //convret from short to bytes
    char bytes[2];
//    bytes[0] = ((cNum >> 8) & 0xFF);
//    bytes[1] = (cNum & 0xFF);
    shortToBytes(cNum,bytes);
    //convert from bytes to string & return.
    string cNumString(bytes,2);
    return cNumString;
}

void ConnectionHandler::shortToBytes(short num, char* bytesArr){
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}










