#include "myfuncs.h"
#include "constants.h"
#include <math.h>
#include <iomanip>
#include <string>
#include <iostream>

/*ОБЩИЙ ВЫВОД*/
//Функция для выполнения поиска по правильному симплексу с заданными параметрами.
void perform_search_first(std::ofstream& results_file, const double& epsilon, double t) {
    for (int i{}; i < 99; ++i) {
        results_file << "=";
    }
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "t = " << t << "." << std::endl;
    search_by_correct_simplex(results_file, epsilon, t);
}
//Функция для выполнения поиска по деформируемому многограннику.
void perform_search_second(std::ofstream& results_file, const double& epsilon, const double& alpha, const double& beta, const double& gamma) {
    for (int i{}; i < 99; ++i) {
        results_file << "=";
    }
    results_file << std::endl;
    results_file << "Epsilon = " << epsilon << "; " << "alpha = " << alpha << ", beta = " << beta << ", gamma = " << gamma << "." << std::endl;
    search_by_deformable_polyhedron(results_file, epsilon, alpha, beta, gamma);
}
//Запись в файл заголовка таблицы.
void printTableHeader(std::ofstream& output_file) {
    output_file << std::setw(10) << "Итерация"
        << std::setw(10) << "Точка"
        << std::setw(15) << "x1"
        << std::setw(15) << "x2"
        << std::setw(15) << "F(X)"
        << std::endl;
}
//Запись в файл строки таблицы.
static void printTableRow(std::ofstream& output_file, const std::string& pointName, const Point& p, const double& fValue) {
    output_file << std::setw(20) << pointName
        << std::setw(15) << p.x1
        << std::setw(15) << p.x2
        << std::setw(15) << fValue
        << std::endl;
}
//Вычисление значения заданной функции F(X)=5*x1^2 + 5*x2^2 + 8*x1*x2.
double F(const Point& p) {
    return 5 * pow(p.x1, 2) + 5 * pow(p.x2, 2) + 8 * p.x1 * p.x2;
}

/*ПОИСК ПО ПРАВИЛЬНОМУ СИМПЛЕКСУ*/
//Запись в файл дополнительных данных строки.
static void printTableAdditionalRow(std::ofstream& output_file, const int& step, const double& t) {
    output_file << std::setw(10) << step
        << std::setw(65) << "t = " << t
        << std::endl;
}
//Запись в файл результатов.
static void printResults(std::ofstream& output_file, const std::vector<Point>& simplex, const std::vector<double>& fValues, const double& t) {
    output_file << std::endl << "Конечные значения:" << std::endl;
    for (size_t i = 0; i < simplex.size(); ++i) {
        printTableRow(output_file, "X" + std::to_string(i), simplex[i], fValues[i]);
    }
    Point x_middle = Point((simplex[0].x1 + simplex[1].x1 + simplex[2].x1) / 3, (simplex[0].x2 + simplex[1].x2 + simplex[2].x2) / 3);
    output_file << std::setw(10) << ""
        << std::setw(10) << "Xср."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << F(x_middle)
        << std::setw(10) << "t = " << t
        << std::endl;
}
//Построение вершин начального симплекса по вершине X0.
static Point caculate_point_by_X0(const Point& X0, const double& d1, const double& d2, const int& number) {
    double x1{}, x2{};
    (number == 1) ? (x1 += X0.x1 + d1) : (x1 += X0.x1 + d2);
    (number == 2) ? (x2 += X0.x2 + d1) : (x2 += X0.x2 + d2);
    return Point(x1, x2);
}
//Сортировка вершин в порядке F(X0)<=F(X1)<=...<=F(XN).
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
//Поиск центра тяжести Xc вершин X0,X1,...,X(N-1).
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
//Поиск центра тяжести Xc вершин X0,X1,...,X(N-2),XN.
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
//Отражение вершины X.
static Point reflect(const Point& centroid, const Point& worst) {
    return Point(2 * centroid.x1 - worst.x1, 2 * centroid.x2 - worst.x2);
}
//Главная функция поиска по правильному симплексу.
void search_by_correct_simplex(std::ofstream& file, const double& epsilon, double& t) {
    //Шаг 0.
    double d1{ t / (n * sqrt(2)) * (sqrt(n + 1) + n - 1) }; //d1 для вычисления координат остальных вершин.
    double d2{ t / (n * sqrt(2)) * (sqrt(n + 1) - 1) }; //d2 для вычисления координат остальных вершин.
    Point X0 = Point(0, 0); // Базовая точка X0.
    std::vector<Point> simplex = { // Построение начального симплекса.
        X0,                                   // X0
        caculate_point_by_X0(X0, d1, d2, 1),  // X1
        caculate_point_by_X0(X0, d1, d2, 2)   // X2
    };
    std::vector<double> fValues(n + 1); // Для хранения значений функции F(X) в точках X0, X1, X2.
    int step = 0; // Учет числа итераций.
    printTableHeader(file); //Вывод заголовка таблицы в файл.
    
    //ГЛАВНЫЙ ЦИКЛ.
    while (true) {
        // Шаг 1.
        for (size_t i = 0; i < simplex.size(); ++i) {
            fValues[i] = F(simplex[i]);
        }
        
        // Шаг 2.
        sortVertices(simplex, fValues);
        // Вывод строки с номером итерации и t.
        printTableAdditionalRow(file, step, t);
        // Вывод текущих вершин.
        for (size_t i = 0; i < simplex.size(); ++i) {
            printTableRow(file, "X" + std::to_string(i), simplex[i], fValues[i]);
        }

        // Шаг 3.
        double sum = 0;
        for (size_t j = 0; j < fValues.size(); ++j) {
            sum += pow(fValues[j] - fValues[0], 2);
        }
        double accuracy = sum / (simplex.size() - 1);
        if (accuracy < epsilon) {
            std::cout << "Точность поиска по правильному симплексу достигнута. Результаты записаны в файл */results_first.txt." << std::endl;
            break;
        }

        // Шаг 4.
        Point c = centroid_n(simplex);
        Point xr = reflect(c, simplex.back());
        double fXr = F(xr);

        if (fXr < fValues.back()) {
            simplex.back() = xr;
            step++;
            continue;
        }

        // Шаг 5.
        c = centroid_n_1(simplex);
        xr = reflect(c, simplex[simplex.size() - 2]);
        fXr = F(xr);

        if (fXr < fValues[fValues.size() - 2]) {
            simplex.back() = xr;
            step++;
            continue;
        }

        // Шаг 6.
        t = t / 2;
        for (int i{ 1 }; i < simplex.size(); ++i) {
            simplex[i].x1 = (simplex[i].x1 + simplex[0].x1) / 2;
            simplex[i].x2 = (simplex[i].x2 + simplex[0].x2) / 2;
        }

        step++;
    }

    // Шаг 7.
    printResults(file, simplex, fValues, t);
}

/*ПОИСК ПО ДЕФОРМИРУЕМОМУ МНОГОГРАННИКУ*/
//Запись в файл дополнительных данных строки.
static void printTableAdditionalRow(std::ofstream& output_file, const int& step) {
    output_file << std::setw(10) << step
        << std::endl;
}
//Запиись в файл текущих вершин.
static void printCurrentPoints(std::ofstream& output_file, const std::vector<Point>& points, const std::vector<double>& fValues) {
    for (size_t i = 0; i < points.size(); ++i) {
        printTableRow(output_file, "X" + std::to_string(i), points[i], fValues[i]);
    }
}
//Запись в файл результатов.
static void printResults(std::ofstream& output_file, const std::vector<Point>& simplex, const std::vector<double>& fValues) {
    output_file << std::endl << "Конечные значения:" << std::endl;
    for (size_t i = 0; i < simplex.size(); ++i) {
        printTableRow(output_file, "X" + std::to_string(i), simplex[i], fValues[i]);
    }
    Point x_middle = Point((simplex[0].x1 + simplex[1].x1 + simplex[2].x1) / 3, (simplex[0].x2 + simplex[1].x2 + simplex[2].x2) / 3);
    output_file << std::setw(10) << ""
        << std::setw(10) << "Xср."
        << std::setw(15) << x_middle.x1
        << std::setw(15) << x_middle.x2
        << std::setw(15) << F(x_middle)
        << std::endl;
}
// Поиск номера вершины Xh, значение функции в которой максимальное.
static int search_point_max_value(const std::vector<double>& fValues) {
    int h{};
    for (size_t i = 1; i < fValues.size(); ++i) {
        if (fValues[i] > fValues[h]) {
            h = i;
        }
    }
    return h;
}
// Поиск номера вершины XL, значение функции в которой минимальное.
static int search_point_min_value(const std::vector<double>& fValues) {
    int L{};
    for (size_t i = 1; i < fValues.size(); ++i) {
        if (fValues[i] < fValues[L]) {
            L = i;
        }
    }
    return L;
}
// Центр тяжести X(n+2) всех вершин, исключая Xh.
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
// Отражение вершины Xh через центр тяжести X(n+2).
static Point reflection(const Point& n_plus_2, const Point& xh, const double& alpha) {
    Point n_plus_3{};
    n_plus_3.x1 = n_plus_2.x1 + alpha * (n_plus_2.x1 - xh.x1);
    n_plus_3.x2 = n_plus_2.x2 + alpha * (n_plus_2.x2 - xh.x2);
    return n_plus_3;
}
// Растяжение вектора X(n+3)-X(n+2).
static Point stretching(const Point& n_plus_3, const Point& n_plus_2, const double& gamma) {
    Point n_plus_4{};
    n_plus_4.x1 = n_plus_2.x1 + gamma * (n_plus_3.x1 - n_plus_2.x1);
    n_plus_4.x2 = n_plus_2.x2 + gamma * (n_plus_3.x2 - n_plus_2.x2);
    return n_plus_4;
}
// Сжатие вектора Xh-X(n+2).
static Point compression(const Point& xh, const Point& n_plus_2, const double& beta) {
    Point n_plus_5{};
    n_plus_5.x1 = n_plus_2.x1 + beta * (xh.x1 - n_plus_2.x1);
    n_plus_5.x2 = n_plus_2.x2 + beta * (xh.x2 - n_plus_2.x2);
    return n_plus_5;
}
// Редукция векторов Xj-XL в 2 раза.
static std::vector<Point> reduction(const std::vector<Point>& points, const Point& xL) {
    std::vector<Point> red_points(n+1);
    for (size_t j{}; j < points.size(); ++j) {
        red_points[j].x1 = xL.x1 + (points[j].x1 - xL.x1) / 2;
        red_points[j].x2 = xL.x2 + (points[j].x2 - xL.x2) / 2;
    }
    return red_points;
}
// Проверка критерия окончания поиска.
static bool check_finished(const std::vector<Point>& points, const std::vector<double>& fValues, const double& f_n_plus_2, const double& epsilon) {
    double sum = 0;
    for (size_t j = 0; j < fValues.size(); ++j) {
        sum += pow(fValues[j] - f_n_plus_2, 2);
    }
    long double accuracy = sqrt(sum / points.size());
    if (accuracy <= epsilon) {
        std::cout << "Точность поиска по деформируемому многограннику достигнута. Результаты записаны в файл */results_second.txt." << std::endl;
        return true;
    }
    return false;
}
//Главная функция поиска по деформируемому многограннику.
void search_by_deformable_polyhedron(std::ofstream& file, const double& epsilon, const double& alpha, const double& beta, const double& gamma) {
    //Используемый многогранник в качестве базы.
    Point X1 = Point(-1, 4);
    Point X2 = Point(-1, 8);
    Point X3 = Point(-3, 6);
    //Для хранения исследуемых вершин X1, X2, X3.
    std::vector<Point> points = {
        X1, // X1
        X2, // X2
        X3, // X3
    };
    std::vector<double> fValues(n+1); // Для хранения значений функции F(X) в вершинах X1, X2, X3.
    //Вычисление значений функции в вершинах X1, X2, X3.
    for (size_t i = 0; i < points.size(); ++i) {
        fValues[i] = F(points[i]);
    }
    
    //Вспомогательные вершины.
    Point n_plus_2{}; //Центр тяжести X(n+2).
    Point n_plus_3 = Point(); //Отражение - X(n+3).
    Point n_plus_4 = Point(); //Растяжение - X(n+4).
    Point n_plus_5 = Point(); //Сжатие - X(n+5).

    int step = 0; // Учет числа итераций.
    printTableHeader(file); //Вывод заголовка таблицы в файл.
    printTableAdditionalRow(file, step); // Вывод строки с номером итерации.
    printCurrentPoints(file, points, fValues); // Вывод текущих вершин.

    //ГЛАВНЫЙ ЦИКЛ.
    while (true) {
        int h = search_point_max_value(fValues); //Вершина, значение функции в которой максимально, - Xh (худшая).
        int L = search_point_min_value(fValues); //Вершина, значение функции в которой минимально, - XL (лучшая).
        //Центр тяжести.
        n_plus_2 = centroid_h(points, h);
        double f_n_plus_2 = F(n_plus_2);
        
        //Проверка критерия окончания поиска.
        if (check_finished(points, fValues, f_n_plus_2, epsilon))
            break;

        printTableAdditionalRow(file, step + 1); // Вывод строки с номером итерации.
        
        //Отражение.
        n_plus_3 = reflection(n_plus_2, points[h], alpha);
        double f_n_plus_3 = F(n_plus_3);

        //Если отраженная вершина лучше не только худшей, то имеет смысл выполнить растяжение, иначе - сжатие.
        //Проверка на сжатие.
        bool compress{ true };
        for (size_t j{}; j < points.size(); ++j) {// Отраженная вершина хуже остальных вершин, но лучше худшей?
            if (j != h) {
                if (!(f_n_plus_3 > fValues[j]) || f_n_plus_3 > fValues[h]) {
                    compress = false;
                    break;
                }
            }
        }

        //Проверка на рястяжение.
        if (f_n_plus_3 < fValues[h] && !compress) { //Отраженная вершина не только лучше худшей?
            //Растяжение.
            n_plus_4 = stretching(n_plus_3, n_plus_2, gamma);// Растянутая отраженная вершина лучше лучшей?
            double f_n_plus_4 = F(n_plus_4);
            if (f_n_plus_4 < fValues[L] && f_n_plus_4 < f_n_plus_3) { //Если да, то худшая вершина = растянутой отраженной вершине, если растянутая лучше отраженной.
                file << "После шага " << step << " выполнено отражение->растяжение." << std::endl;
                points[h] = n_plus_4; // Xh = X(n+4).
                fValues[h] = f_n_plus_4;
                printCurrentPoints(file, points, fValues);
                step++;
                continue;
            }
            else { //Иначе худшая вершина = отраженной.
                file << "После шага " << step << " выполнено отражение." << std::endl;
                points[h] = n_plus_3; // Xh = X(n+3).
                fValues[h] = f_n_plus_3;
                printCurrentPoints(file, points, fValues);
                step++;
                continue;
            }
        }
        
        //Сжатие.
        if (compress) {// Если имеет смысл выполнить сжатие, а отражение и растяжение не дает лучших результатов.
            file << "После шага " << step << " выполнено сжатие." << std::endl;
            n_plus_5 = compression(points[h], n_plus_2, beta);
            double f_n_plus_5 = F(n_plus_5);
            points[h] = n_plus_5; // Xh = X(n+5).
            fValues[h] = f_n_plus_5;
            printCurrentPoints(file, points, fValues);
            step++;
            continue;
        }

        //Редукция.
        if (f_n_plus_3 > fValues[h]) { //Отраженная вершина еще хуже, чем худшая => редукция.
            file << "После шага " << step << " выполнена редукция." << std::endl;
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