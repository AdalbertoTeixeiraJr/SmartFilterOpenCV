#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <string>



class Connection
{

public:
	Connection(boost::asio::io_service &io_service);
	void start();
	boost::asio::ip::tcp::socket& socket();
private:
	boost::asio::ip::tcp::socket	_socket;
	static const int MAX_LENGTH =4096;
	char _data[MAX_LENGTH];
	void handleWrite(const boost::system::error_code &error);
	void handleRead(const boost::system::error_code &error, size_t bytesTransferred);
	std::vector<std::string> split(size_t bytesTransferred);
};

#endif // CONNECTION_H
