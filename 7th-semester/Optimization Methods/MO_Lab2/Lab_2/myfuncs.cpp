#include "myfuncs.h"
#include "constants.h"
#include <math.h>
#include <iomanip>
#include <string>
#include <iostream>

/*����� �����*/
//������� ��� ���������� ������ �� ����������� ��������� � ��������� �����������.
void perform_search_first(std::ofstream& results_file, const double& epsilon, double t) {
    for (int i{}; i < 99; ++i) {
        results_file << "=";
    }
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "t = " << t << "." << std::endl;
    search_by_correct_simplex(results_file, epsilon, t);
}
//������� ��� ���������� ������ �� �������������� �������������.
void perform_search_second(std::ofstream& results_file, const double& epsilon, const double& alpha, const double& beta, const double& gamma) {
    for (int i{}; i < 99; ++i) {
        results_file << "=";
    }
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "alpha = " << alpha << ", beta = " << beta << ", gamma = " << gamma << "." << std::endl;
    search_by_deformable_polyhedron(results_file, epsilon, alpha, beta, gamma);
}
//������ � ���� ��������� �������.
void printTableHeader(std::ofstream& output_file) {
    output_file << std::setw(10) << "��������"
        << std::setw(10) << "�����"
        << std::setw(15) << "x1"
        << std::setw(15) << "x2"
        << std::setw(15) << "F(X)"
        << std::endl;
}
//������ � ���� ������ �������.
static void printTableRow(std::ofstream& output_file, const std::string& pointName, const Point& p, const double& fValue) {
    output_file << std::setw(20) << pointName
        << std::setw(15) << p.x1
        << std::setw(15) << p.x2
        << std::setw(15) << fValue
        << std::endl;
}
//���������� �������� �������� ������� F(X)=5*x1^2 + 5*x2^2 + 8*x1*x2.
double F(const Point& p) {
    return 5 * pow(p.x1, 2) + 5 * pow(p.x2, 2) + 8 * p.x1 * p.x2;
}

/*����� �� ����������� ���������*/
//������ � ���� �������������� ������ ������.
static void printTableAdditionalRow(std::ofstream& output_file, const int& step, const double& t) {
    output_file << std::setw(10) << step
        << std::setw(65) << "t = " << t
        << std::endl;
}
//������ � ���� �����������.
static void printResults(std::ofstream& output_file, const std::vector<Point>& simplex, const std::vector<double>& fValues, const double& t) {
    output_file << std::endl << "�������� ��������:" << std::endl;
    for (size_t i = 0; i < simplex.size(); ++i) {
        printTableRow(output_file, "X" + std::to_string(i), simplex[i], fValues[i]);
    }
    Point x_middle = Point((simplex[0].x1 + simplex[1].x1 + simplex[2].x1) / 3, (simplex[0].x2 + simplex[1].x2 + simplex[2].x2) / 3);
    output_file << std::setw(10) << ""
        << std::setw(10) << "X��."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << F(x_middle)
        << std::setw(10) << "t = " << t
        << std::endl;
}
//���������� ������ ���������� ��������� �� ������� X0.
static Point caculate_point_by_X0(const Point& X0, const double& d1, const double& d2, const int& number) {
    double x1{}, x2{};
    (number == 1) ? (x1 += X0.x1 + d1) : (x1 += X0.x1 + d2);
    (number == 2) ? (x2 += X0.x2 + d1) : (x2 += X0.x2 + d2);
    return Point(x1, x2);
}
//���������� ������ � ������� F(X0)<=F(X1)<=...<=F(XN).
static void sortVertices(std::vector<Point>& simplex, std::vector<double>& fValues) {
    for (size_t i = 0; i < simplex.size() - 1; ++i) {
        for (size_t j = i + 1; j < simplex.size(); ++j) {
            if (fValues[j] <= fValues[i]) {
                std::swap(simplex[i], simplex[j]);
                std::swap(fValues[i], fValues[j]);
            }
        }
    }
}
//����� ������ ������� Xc ������ X0,X1,...,X(N-1).
static Point centroid_n(const std::vector<Point>& simplex) {
    Point c{};
    for (size_t i = 0; i < simplex.size() - 1; ++i) {
        c.x1 += simplex[i].x1;
        c.x2 += simplex[i].x2;
    }
    c.x1 /= (simplex.size() - 1);
    c.x2 /= (simplex.size() - 1);
    return c;
}
//����� ������ ������� Xc ������ X0,X1,...,X(N-2),XN.
static Point centroid_n_1(const std::vector<Point>& simplex) {
    Point c{};
    for (size_t i = 0; i < simplex.size(); ++i) {
        if (i != simplex.size() - 2) {
            c.x1 += simplex[i].x1;
            c.x2 += simplex[i].x2;
        }
    }
    c.x1 /= (simplex.size() - 1);
    c.x2 /= (simplex.size() - 1);
    return c;
}
//��������� ������� X.
static Point reflect(const Point& centroid, const Point& worst) {
    return Point(2 * centroid.x1 - worst.x1, 2 * centroid.x2 - worst.x2);
}
//������� ������� ������ �� ����������� ���������.
void search_by_correct_simplex(std::ofstream& file, const double& epsilon, double& t) {
    //��� 0.
    double d1{ t / (n * sqrt(2)) * (sqrt(n + 1) + n - 1) }; //d1 ��� ���������� ��������� ��������� ������.
    double d2{ t / (n * sqrt(2)) * (sqrt(n + 1) - 1) }; //d2 ��� ���������� ��������� ��������� ������.
    Point X0 = Point(0, 0); // ������� ����� X0.
    std::vector<Point> simplex = { // ���������� ���������� ���������.
        X0,                                   // X0
        caculate_point_by_X0(X0, d1, d2, 1),  // X1
        caculate_point_by_X0(X0, d1, d2, 2)   // X2
    };
    std::vector<double> fValues(n + 1); // ��� �������� �������� ������� F(X) � ������ X0, X1, X2.
    int step = 0; // ���� ����� ��������.
    printTableHeader(file); //����� ��������� ������� � ����.
    
    //������� ����.
    while (true) {
        // ��� 1.
        for (size_t i = 0; i < simplex.size(); ++i) {
            fValues[i] = F(simplex[i]);
        }
        
        // ��� 2.
        sortVertices(simplex, fValues);
        // ����� ������ � ������� �������� � t.
        printTableAdditionalRow(file, step, t);
        // ����� ������� ������.
        for (size_t i = 0; i < simplex.size(); ++i) {
            printTableRow(file, "X" + std::to_string(i), simplex[i], fValues[i]);
        }

        // ��� 3.
        double sum = 0;
        for (size_t j = 0; j < fValues.size(); ++j) {
            sum += pow(fValues[j] - fValues[0], 2);
        }
        double accuracy = sum / (simplex.size() - 1);
        if (accuracy < epsilon) {
            std::cout << "�������� ������ �� ����������� ��������� ����������. ���������� �������� � ���� */results_first.txt." << std::endl;
            break;
        }

        // ��� 4.
        Point c = centroid_n(simplex);
        Point xr = reflect(c, simplex.back());
        double fXr = F(xr);

        if (fXr < fValues.back()) {
            simplex.back() = xr;
            step++;
            continue;
        }

        // ��� 5.
        c = centroid_n_1(simplex);
        xr = reflect(c, simplex[simplex.size() - 2]);
        fXr = F(xr);

        if (fXr < fValues[fValues.size() - 2]) {
            simplex.back() = xr;
            step++;
            continue;
        }

        // ��� 6.
        t = t / 2;
        for (int i{ 1 }; i < simplex.size(); ++i) {
            simplex[i].x1 = (simplex[i].x1 + simplex[0].x1) / 2;
            simplex[i].x2 = (simplex[i].x2 + simplex[0].x2) / 2;
        }

        step++;
    }

    // ��� 7.
    printResults(file, simplex, fValues, t);
}

/*����� �� �������������� �������������*/
//������ � ���� �������������� ������ ������.
static void printTableAdditionalRow(std::ofstream& output_file, const int& step) {
    output_file << std::setw(10) << step
        << std::endl;
}
//������� � ���� ������� ������.
static void printCurrentPoints(std::ofstream& output_file, const std::vector<Point>& points, const std::vector<double>& fValues) {
    for (size_t i = 0; i < points.size(); ++i) {
        printTableRow(output_file, "X" + std::to_string(i), points[i], fValues[i]);
    }
}
//������ � ���� �����������.
static void printResults(std::ofstream& output_file, const std::vector<Point>& simplex, const std::vector<double>& fValues) {
    output_file << std::endl << "�������� ��������:" << std::endl;
    for (size_t i = 0; i < simplex.size(); ++i) {
        printTableRow(output_file, "X" + std::to_string(i), simplex[i], fValues[i]);
    }
    Point x_middle = Point((simplex[0].x1 + simplex[1].x1 + simplex[2].x1) / 3, (simplex[0].x2 + simplex[1].x2 + simplex[2].x2) / 3);
    output_file << std::setw(10) << ""
        << std::setw(10) << "X��."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << F(x_middle)
        << std::endl;
}
// ����� ������ ������� Xh, �������� ������� � ������� ������������.
static int search_point_max_value(const std::vector<double>& fValues) {
    int h{};
    for (size_t i = 1; i < fValues.size(); ++i) {
        if (fValues[i] > fValues[h]) {
            h = i;
        }
    }
    return h;
}
// ����� ������ ������� XL, �������� ������� � ������� �����������.
static int search_point_min_value(const std::vector<double>& fValues) {
    int L{};
    for (size_t i = 1; i < fValues.size(); ++i) {
        if (fValues[i] < fValues[L]) {
            L = i;
        }
    }
    return L;
}
// ����� ������� X(n+2) ���� ������, �������� Xh.
static Point centroid_h(const std::vector<Point>& points, const int& h) {
    Point n_plus_2{};
    for (size_t i = 0; i < points.size(); ++i) {
        if (i != h) {
            n_plus_2.x1 += points[i].x1;
            n_plus_2.x2 += points[i].x2;
        }
    }
    n_plus_2.x1 /= (points.size() - 1);
    n_plus_2.x2 /= (points.size() - 1);
    return n_plus_2;
}
// ��������� ������� Xh ����� ����� ������� X(n+2).
static Point reflection(const Point& n_plus_2, const Point& xh, const double& alpha) {
    Point n_plus_3{};
    n_plus_3.x1 = n_plus_2.x1 + alpha * (n_plus_2.x1 - xh.x1);
    n_plus_3.x2 = n_plus_2.x2 + alpha * (n_plus_2.x2 - xh.x2);
    return n_plus_3;
}
// ���������� ������� X(n+3)-X(n+2).
static Point stretching(const Point& n_plus_3, const Point& n_plus_2, const double& gamma) {
    Point n_plus_4{};
    n_plus_4.x1 = n_plus_2.x1 + gamma * (n_plus_3.x1 - n_plus_2.x1);
    n_plus_4.x2 = n_plus_2.x2 + gamma * (n_plus_3.x2 - n_plus_2.x2);
    return n_plus_4;
}
// ������ ������� Xh-X(n+2).
static Point compression(const Point& xh, const Point& n_plus_2, const double& beta) {
    Point n_plus_5{};
    n_plus_5.x1 = n_plus_2.x1 + beta * (xh.x1 - n_plus_2.x1);
    n_plus_5.x2 = n_plus_2.x2 + beta * (xh.x2 - n_plus_2.x2);
    return n_plus_5;
}
// �������� �������� Xj-XL � 2 ����.
static std::vector<Point> reduction(const std::vector<Point>& points, const Point& xL) {
    std::vector<Point> red_points(n+1);
    for (size_t j{}; j < points.size(); ++j) {
        red_points[j].x1 = xL.x1 + (points[j].x1 - xL.x1) / 2;
        red_points[j].x2 = xL.x2 + (points[j].x2 - xL.x2) / 2;
    }
    return red_points;
}
// �������� �������� ��������� ������.
static bool check_finished(const std::vector<Point>& points, const std::vector<double>& fValues, const double& f_n_plus_2, const double& epsilon) {
    double sum = 0;
    for (size_t j = 0; j < fValues.size(); ++j) {
        sum += pow(fValues[j] - f_n_plus_2, 2);
    }
    long double accuracy = sqrt(sum / points.size());
    if (accuracy <= epsilon) {
        std::cout << "�������� ������ �� �������������� ������������� ����������. ���������� �������� � ���� */results_second.txt." << std::endl;
        return true;
    }
    return false;
}
//������� ������� ������ �� �������������� �������������.
void search_by_deformable_polyhedron(std::ofstream& file, const double& epsilon, const double& alpha, const double& beta, const double& gamma) {
    //������������ ������������ � �������� ����.
    Point X1 = Point(-1, 4);
    Point X2 = Point(-1, 8);
    Point X3 = Point(-3, 6);
    //��� �������� ����������� ������ X1, X2, X3.
    std::vector<Point> points = {
        X1, // X1
        X2, // X2
        X3, // X3
    };
    std::vector<double> fValues(n+1); // ��� �������� �������� ������� F(X) � �������� X1, X2, X3.
    //���������� �������� ������� � �������� X1, X2, X3.
    for (size_t i = 0; i < points.size(); ++i) {
        fValues[i] = F(points[i]);
    }
    
    //��������������� �������.
    Point n_plus_2{}; //����� ������� X(n+2).
    Point n_plus_3 = Point(); //��������� - X(n+3).
    Point n_plus_4 = Point(); //���������� - X(n+4).
    Point n_plus_5 = Point(); //������ - X(n+5).

    int step = 0; // ���� ����� ��������.
    printTableHeader(file); //����� ��������� ������� � ����.
    printTableAdditionalRow(file, step); // ����� ������ � ������� ��������.
    printCurrentPoints(file, points, fValues); // ����� ������� ������.

    //������� ����.
    while (true) {
        int h = search_point_max_value(fValues); //�������, �������� ������� � ������� �����������, - Xh (������).
        int L = search_point_min_value(fValues); //�������, �������� ������� � ������� ����������, - XL (������).
        //����� �������.
        n_plus_2 = centroid_h(points, h);
        double f_n_plus_2 = F(n_plus_2);
        
        //�������� �������� ��������� ������.
        if (check_finished(points, fValues, f_n_plus_2, epsilon))
            break;
        if (step == 13) {
            std::cout << "check" << std::endl;
        }

        printTableAdditionalRow(file, step + 1); // ����� ������ � ������� ��������.
        
        //���������.
        n_plus_3 = reflection(n_plus_2, points[h], alpha);
        double f_n_plus_3 = F(n_plus_3);

        //���� ���������� ������� ����� �� ������ ������, �� ����� ����� ��������� ����������, ����� - ������.
        //�������� �� ������.
        bool compress{ true };
        for (size_t j{}; j < points.size(); ++j) {// ���������� ������� ���� ��������� ������, �� ����� ������?
            if (j != h) {
                if (!(f_n_plus_3 > fValues[j]) || f_n_plus_3 > fValues[h]) {
                    compress = false;
                    break;
                }
            }
        }

        //�������� �� ����������.
        if (f_n_plus_3 < fValues[h] && !compress) { //���������� ������� �� ������ ����� ������?
            //����������.
            n_plus_4 = stretching(n_plus_3, n_plus_2, gamma);// ���������� ���������� ������� ����� ������?
            double f_n_plus_4 = F(n_plus_4);
            if (f_n_plus_4 < fValues[L]) { //���� ��, �� ������ ������� = ���������� ���������� �������.
                file << "����� ���� " << step << " ��������� ���������->����������." << std::endl;
                points[h] = n_plus_4; // Xh = X(n+4).
                fValues[h] = f_n_plus_4;
                printCurrentPoints(file, points, fValues);
                step++;
                continue;
            }
            else { //����� ������ ������� = ����������.
                file << "����� ���� " << step << " ��������� ���������." << std::endl;
                points[h] = n_plus_3; // Xh = X(n+3).
                fValues[h] = f_n_plus_3;
                printCurrentPoints(file, points, fValues);
                step++;
                continue;
            }
        }
        
        //������.
        if (compress) {// ���� ����� ����� ��������� ������, � ��������� � ���������� �� ���� ������ �����������.
            file << "����� ���� " << step << " ��������� ������." << std::endl;
            n_plus_5 = compression(points[h], n_plus_2, beta);
            double f_n_plus_5 = F(n_plus_5);
            points[h] = n_plus_5; // Xh = X(n+5).
            fValues[h] = f_n_plus_5;
            printCurrentPoints(file, points, fValues);
            step++;
            continue;
        }

        //��������.
        if (f_n_plus_3 > fValues[h]) { //���������� ������� ��� ����, ��� ������ => ��������.
            file << "����� ���� " << step << " ��������� ��������." << std::endl;
            points = reduction(points, points[L]);
            for (size_t i{}; i < points.size(); ++i) {
                fValues[i] = F(points[i]);
            }
            printCurrentPoints(file, points, fValues);
            step++;
            continue;
        }
    }
    printResults(file, points, fValues);
}