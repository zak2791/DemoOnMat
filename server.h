#ifndef SERVER_H
#define SERVER_H

class Server
{
public:
    Server();

private:
    int port;
    void setPort(int _port){port = _port;}

};



#endif // SERVER_H
