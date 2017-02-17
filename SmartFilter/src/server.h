#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "connection.h"

class Server
{
public:
	Server(boost::asio::io_service &ioservice, int port); // call OS
private:	
	boost::asio::ip::tcp::acceptor _acceptor; // open Socket
	void handleAccept(Connection *connection, const boost::system::error_code &error);
	void startAccept();
};

#endif // SERVER_H
