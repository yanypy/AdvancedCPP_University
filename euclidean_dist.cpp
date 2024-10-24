#include <iostream>
#include <vector>
#include <cstdlib> // for rand() function
#include <cmath> // for sqrt() and M_PI constants
#include <algorithm> // for STL algorithms
#include <numeric> // for inner_product() and adjacent_difference()
#include <functional> // for functional objects

using namespace std;

const int N = 100; // number of points in the set
const double R = 1; // radius of the circle

using Point = std::pair<double, double>;

bool compare_x(Point a, Point b) {
    return a.first < b.first;
}

double euclidean_distance(Point a, Point b) {
    return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

#define M_PI 3.14

int main() {
    vector<Point> points;
    for (int i = 0; i < N; i++) {
        double angle = 2 * M_PI * rand() / RAND_MAX;
        //std::pair<double,double> point(R * cos(angle), R * sin(angle));
        //auto point = std::make_pair(R * cos(angle), R * sin(angle));
        Point point = { R * cos(angle), R * sin(angle) };
        points.push_back(point);
    }

    // find and sort non-dominated points by x-coordinate
    sort(points.begin(), points.end(), compare_x);

    // calculate Euclidean distances between adjacent points
    vector<double> distances;
    adjacent_difference(points.begin(), points.end(), back_inserter(distances),  euclidean_distance);
    distances.erase(distances.begin()); // first element is not a distance

    // calculate average and variance of distances
    double sum = accumulate(distances.begin(), distances.end(), 0.0);
    double mean = sum / distances.size();
    double var = inner_product(distances.begin(), distances.end(),
        distances.begin(), 0.0) / distances.size() - mean * mean;

    cout << "Average distance: " << mean << endl;
    cout << "Distance variance: " << var << endl;

    return 0;
}
