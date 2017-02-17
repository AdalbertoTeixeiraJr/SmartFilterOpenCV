#include "edge_filter.h"

using namespace cv;


Mat EdgeFilter::filter(const Mat &input)
{
	Mat output;
	Canny(input, output, 10, 100, 3);
	return output;
}
