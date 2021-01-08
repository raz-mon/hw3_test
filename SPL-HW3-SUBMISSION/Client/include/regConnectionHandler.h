
#ifndef SPL_HW3_REGCONECTIONHANDLER_H
#define SPL_HW3_REGCONECTIONHANDLER_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class ConnectionHandler {
private:
    const std::string host_;
    const short port_;
    boost::asio::io_service io_service_;   // Provides core I/O functionality
    tcp::socket socket_;

public:
    ConnectionHandler(std::string host, short port);
    virtual ~ConnectionHandler();

    // Connect to the remote machine
    bool connect();

    // Read a fixed number of bytes from the server - blocking.
    // Returns false in case the connection is closed before bytesToRead bytes can be read.
    bool getBytes(char bytes[], unsigned int bytesToRead);

    // Send a fixed number of bytes from the client - blocking.
    // Returns false in case the connection is closed before all the data is sent.
    bool sendBytes(const char bytes[], int bytesToWrite);

    // Read an ascii line from the server
    // Returns false in case connection closed before a newline can be read.
    bool getLine(std::string& line);

    // Send an ascii line from the server
    // Returns false in case connection closed before all the data is sent.
    bool sendLine(std::string& line);

    // Get Ascii data from the server until the delimiter character
    // Returns false in case connection closed before null can be read.
    bool getFrameAscii(std::string& frame, char delimiter);

    // Send a message to the remote host.
    // Returns false in case connection is closed before all the data is sent.
    bool sendFrameAscii(const std::string& frame, char delimiter);

    // The same as the aboce, with no deliniter.
    bool getFrameAscii(std::string& frame);

    // Just as the former, but doesn't use a delimiter.
//    bool sendFrameAscii(const std::string& frame);

    // Close down the connection properly.
    void close();

    static std::string enc(std::string in);

    static void process(const string& in);

    static string char_disp(string basicString);

    static void shortToBytes(short nunm, char* bytesArr);
};

#endif //SPL_HW3_REGCONECTIONHANDLER_H



