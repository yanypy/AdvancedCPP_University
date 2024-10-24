#include <iostream>
#include <vector>
#include <cstdlib> //  rand()
#include <algorithm> 

using namespace std;

const int N = 100; // liczba punktów w zbiorze
const int DIM = 3; // liczba wymiarów przestrzeni

struct Point {
    vector<double> coordinates;
};

bool dominates(Point a, Point b) {
    bool strictly_greater = false;
    for (int i = 0; i < DIM; i++) {
        if (a.coordinates[i] < b.coordinates[i]) {
            return false;
        }
        else if (a.coordinates[i] > b.coordinates[i]) {
            strictly_greater = true;
        }
    }
    return strictly_greater;
}

vector<Point> find_nondominated_points(vector<Point>& points) {
    vector<Point> nondominated;
    for (auto point : points) {
        bool dominated = false;
        for (auto other : points) {
            if (point.coordinates != other.coordinates && dominates(other, point)) {
                dominated = true;
                break;
            }
        }
        if (!dominated) {
            nondominated.push_back(point);
        }
    }
    return nondominated;
}

int main() {
    vector<Point> points;
    for (int i = 0; i < N; i++) {
        Point point;
        point.coordinates.resize(DIM);
        for (int j = 0; j < DIM; j++) {
            point.coordinates[j] = rand() % 100; // losujemy liczby z zakresu 0-99
        }
        points.push_back(point);
    }

    vector<Point> nondominated = find_nondominated_points(points);

    cout << "Liczba punktow niezdominowanych: " << nondominated.size() << endl;
    for (auto point : nondominated) {
        for (int i = 0; i < DIM; i++) {
            cout << point.coordinates[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}