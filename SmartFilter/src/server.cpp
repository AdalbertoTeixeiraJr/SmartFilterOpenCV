#include "server.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio::ip;


Server::Server(boost::asio::io_service &io_service, int port): _acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
	startAccept();
}

void Server::startAccept()
{
	Connection *connection = new Connection(_acceptor.get_io_service());
	_acceptor.async_accept(connection->socket(),boost::bind(&Server::handleAccept, this, connection, boost::asio::placeholders::error));
}

void Server::handleAccept(Connection *connection, const boost::system::error_code &error) {
	if (error) {
		delete connection;
	} else {
		connection->start();
	}
	startAccept();
}
