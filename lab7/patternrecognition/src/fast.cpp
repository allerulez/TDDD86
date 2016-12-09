#include <vector>

using namespace std;

void main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input3200.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();
}
