#include "Point.h"
#include <vector>
#include <fstream>

const int num_points = 7;
const std::string file_name = "mydata.txt";

void input_points(std::vector<Point>&);
void export_points(const std::vector<Point>&);
void import_points(std::vector<Point>&);
void print_points(const std::vector<Point>&, const std::vector<Point>&);
void compare_points(const std::vector<Point>&, const std::vector<Point>&);

int main() {
	std::vector<Point> original_points;
	std::vector<Point> processed_points;

	std::cout << "Enter " << num_points << " (x, y) pairs:\n";
	try {
		input_points(original_points);
		export_points(original_points);
		import_points(processed_points);
		print_points(original_points, processed_points);
		compare_points(original_points, processed_points);
	}
	catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << ".\n";
	}
	catch (...) {
		std::cerr << "Unexpected error.\n";
	}

}

void input_points(std::vector<Point>& original_points) {
	for (Point point; original_points.size() < num_points && std::cin >> point;)
		original_points.push_back(point);
}

void export_points(const std::vector<Point> & original_points) {
	std::ofstream ofs{ file_name };

	for (Point point : original_points)
		ofs << point << '\n';
}


void import_points(std::vector<Point> & processed_points) {
	std::ifstream ifs{ file_name };

	for (Point point; processed_points.size() < num_points && ifs >> point;)
		processed_points.push_back(point);
}

void print_points(const std::vector<Point> & original_points,
	const std::vector<Point> & processed_points) {
	std::cout << "\nOriginal points:\n";
	for (Point point : original_points)
		std::cout << point << '\n';

	std::cout << "\nProcessed points:\n";
	for (Point point : processed_points)
		std::cout << point << '\n';
}

void compare_points(const std::vector<Point> & original_points,
	const std::vector<Point> & processed_points) {
	if (original_points.size() != processed_points.size())
		throw std::exception("compare_points() - unequal vector sizes");
	for (int i = 0; i < original_points.size(); ++i)
		if (original_points[i] != processed_points[i])
			throw std::exception("compare_points() - unequal vector contents");

	std::cout << "\nThe vectors are the same.\n";
}