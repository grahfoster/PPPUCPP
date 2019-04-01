#include "../../../../std_lib_facilities.h"

int area(int length, int width);
//int framed_area(int length, int width);
//int f(int x, int y, int z);

int main() {
	//int s1 = area(7;
	//int s2 = area(7)
	//Int s3 = area(7);
	//int s4 = area('7);

	///

	//int x0 = arena(7);
	//int x1 = area(7);
	//int x2 = area("seven", 2);
	//string x3 = area(1, 2);

	///

	//int x = 0, y = 0, z = 0;
	//cout << "Enter three integer values: ";
	//while (cin >> x >> y >> z)
	//	f(x, y, z);

	///

	//error("error");

	///

	//vector<double> temps;
	//double temp = 0;
	//double sum = 0;
	//double high_temp = 0;
	//double low_temp = 0;
	//// temperatures
	//while (cin >> temp)	// read and put into temps
	//	temps.push_back(temp);
	//for (int i = 0; i < temps.size(); ++i)
	//{
	//	if (temps[i] > high_temp) high_temp = temps[i];
	//	if (temps[i] < low_temp) low_temp = temps[i];
	//	sum += temps[i]; // compute sum
	//	cout << "High temperature: " << high_temp << endl;	// find high
	//	cout << "Low temperature: " << low_temp << endl;	// find low
	//	cout << "Average temperature: " << sum / temps.size() << endl;
	//}

	///

	//const double max_temp = -228.6;	// 100 degrees below the lowest ever recorded temperature on earth
	//const double min_temp = 234.1;	// 100 degrees above the highest ever recorded temperature on earth

	//double temp = 0;
	//double sum = 0;
	//double high_temp = min_temp;
	//double low_temp = max_temp;
	//int no_of_temps = 0;

	//while (cin >> temp) {	// read temp
	//	++no_of_temps;	// count temperatures
	//	sum += temp;	// compute sum
	//	if (temp > high_temp) high_temp = temp;	// find high
	//	if (temp < low_temp) low_temp = temp;	// find low
	//}

	//cout << " High temperature: " << high_temp << endl;
	//cout << " Low temperature: " << low_temp << endl;
	//cout << "Average temperature: " << sum / no_of_temps << endl;

	///

	int length = 0, width = 0;
	try {
		while (cin >> length >> width)
			cout << area(length, width) << '\n';
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
}

int area(int length, int width) {
	// calculate area of a rectangle;
	// pre-conditions: length and width are positive
	// post-condition: returns a positive value that is the area
	if (length <= 0 || width <= 0)
		error("area() pre-condition");
	int a = length * width;
	if (a <= 0)
		error("area() post-condition");
	return a;
}

//int framed_area(int x, int y) {
//	const int frame_size = 2;
//	if (x - frame_size <= 0 || y - frame_size <= 0)
//		error("non-positive area() argument called by framed_area()");
//	return area(x - frame_size, y - frame_size);
//}

//int f(int x, int y, int z) {
//	int area1 = area(x, y);
//	int area2 = framed_area(x, z);
//	int area3 = framed_area(y, z);
//	double ratio = double(area1) / area3;
//	cout << "area1: " << area1 << "\n"
//		<< "area2: " << area2 << "\n"
//		<< "area3: " << area3 << "\n"
//		<< "ratio: " << ratio << "\n";
//	return 0;
//}