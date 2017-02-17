#include "connection.h"

#include <string>
#include <iostream> 
#include <vector>
#include <sstream>

#include "gray_filter.h"
#include "edge_filter.h"

using namespace boost::asio::ip;
using namespace std;
using namespace cv;

enum FilterType
{
	GRAYSCALE=0, EDGE=1
};

Mat applyFilter(const Mat& input, FilterType type)
{
	AbstractFilter *filter;
	Mat output;
	switch (type)
	{
	case EDGE:
		filter = new EdgeFilter;
		break;
	default:
		filter = new GrayScaleFilter;
		break;
	}
	output = filter->filter(input);
	delete filter;
	return output;
}


Connection::Connection(boost::asio::io_service &io_service) : _socket(io_service)
{

}

tcp::socket& Connection::socket()
{
	return _socket;
}

void Connection::start()
{

			_socket.async_read_some(boost::asio::buffer(_data, MAX_LENGTH), 
			boost::bind(&Connection::handleRead, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
}

void Connection::handleWrite(const boost::system::error_code &error)
{
	cout << "Escreveu com sucesso" << endl;
	delete this;
}

vector<string> Connection::split(size_t bytesTransferred) {
		stringstream ss;
		for (size_t i = 0; i < bytesTransferred; i++) {
			ss << _data[i];
		}
		vector<string> tokens;
		string token;
		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}
		return tokens;
}

void Connection::handleRead(const boost::system::error_code &error, size_t bytesTransferred) {
		if (error) {
			delete this;
		} else {
			cout << "Read: " << _data << endl;
			vector<string> tokens = split(bytesTransferred);
			if (tokens.size() != 3) {
				_data[0] = 0;
			} else {
				try {
					string inputFilename = tokens[0];
					string outputFilename = tokens[1];
					FilterType filterType = (FilterType)atoi(tokens[2].c_str());
					Mat img = imread(inputFilename);
					if (!img.data) {
						cerr << "Could not read image: " << inputFilename << endl;
						_data[0] = 0;
					} else {
						img = applyFilter(img, filterType);
						imwrite(outputFilename, img);
						_data[0] = 1;	
					}
				} catch (...) {
					_data[0] = 0;
				}
			}
			_data[1] = 0;
			/*boost::asio::async_write(_socket, 
				boost::asio::buffer(_data, bytesTransferred),
				boost::bind(&Connection::handleWrite, this,
					boost::asio::placeholders::error));*/
			_socket.async_write_some(boost::asio::buffer(_data, 2),
				boost::bind(&Connection::handleWrite, this,
					boost::asio::placeholders::error));
	}
}
