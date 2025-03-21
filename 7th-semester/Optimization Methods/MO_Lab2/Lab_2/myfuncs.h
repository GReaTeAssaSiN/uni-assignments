#ifndef MYFUNCS_H_
#define MYFUNCS_H_ 

#include <vector>
#include <fstream>

//Структура для хранения координат вершины.
struct Point {
    double x1{}, x2{};
    Point(double _x1 = 0, double _x2 = 0) : x1(_x1), x2(_x2) {}
};

/*ОБЩИЙ ВЫВОД*/
void perform_search_first(std::ofstream& results_file, const double& epsilon, double t);
void perform_search_second(std::ofstream& results_file, const double& epsilon, const double& alpha, const double& beta, const double& gamma);
void printTableHeader(std::ofstream& output_file);
static void printTableRow(std::ofstream& output_file, const std::string& pointName, const Point& p, const double& fValue);
double F(const Point& p);

/*ПОИСК ПО МЕТОДУ ПРАВИЛЬНОГО СИМПЛЕКСА*/
static void printTableAdditionalRow(std::ofstream& output_file, const int& step, const double& t);
static void printResults(std::ofstream& output_file, const std::vector<Point>& simplex, const std::vector<double>& fValues, const double& t);
static Point caculate_point_by_X0(const Point& X0, const double& d1, const double& d2, const int& number);
static void sortVertices(std::vector<Point>& simplex, std::vector<double>& fValues);
static Point centroid_n(const std::vector<Point>& simplex);
static Point centroid_n_1(const std::vector<Point>& simplex);
static Point reflect(const Point& centroid, const Point& worst);

void search_by_correct_simplex(std::ofstream& file, const double& epsilon, double& t);

/*ПОИСК ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ*/
static void printTableAdditionalRow(std::ofstream& output_file, const int& step);
static void printResults(std::ofstream& output_file, const std::vector<Point>& simplex, const std::vector<double>& fValues);
static void printCurrentPoints(std::ofstream& output_file, const std::vector<Point>& points, const std::vector<double>& fValues);
static int search_point_max_value(const std::vector<double>& fValues);
static int search_point_min_value(const std::vector<double>& fValues);
static Point centroid_h(const std::vector<Point>& points, const int& h);
static Point reflection(const Point& n_plus_2, const Point& xh, const double& alpha);
static Point stretching(const Point& n_plus_3, const Point& n_plus_2, const double& gamma);
static Point compression(const Point& xh, const Point& n_plus_2, const double& beta);
static std::vector<Point> reduction(const std::vector<Point>& points, const Point& xL);
static bool check_finished(const std::vector<Point>& points, const std::vector<double>& fValues, const double& f_n_plus_2, const double& epsilon);
void search_by_deformable_polyhedron(std::ofstream& file, const double& epsilon, const double& alpha, const double& beta, const double& gamma);

#endif /* MYFUNCS_H_ */