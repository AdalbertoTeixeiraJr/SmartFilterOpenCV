#include <iostream>

// Load the socket to connect
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "gray_filter.h"
#include "edge_filter.h"
#include "server.h"
#include "connection.h"

using namespace cv;
using namespace std;



int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "Usage: <PORT>" << endl;
		exit(-1);
	}
	int port = atoi(argv[1]);
	try {
		boost::asio::io_service ioservice;
		Server server(ioservice, port);
		ioservice.run();
	} catch (exception &e) {
		cerr << "ERROR: " << e.what() << endl;
		exit(-1);
	}
	/*if (argc != 3) {
		cerr << "Usage: <PATH_TO_IMAGE> <FILTER 0=GRAYSCALE,1=EDGE,2=CARTOON,3=RETRO>" << endl;
		exit(-1);
	}
	Mat img = imread(argv[1]);
	if (!img.data) {
		cerr << "Could not read image: " << argv[1] << endl;
		exit(-1);
	}
	FilterType filterType = (FilterType)atoi(argv[2]);
	img = applyFilter(img, filterType);
	imshow("image", img);
	waitKey(0);*/
	return 0;
}
