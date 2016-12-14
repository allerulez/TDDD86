#include <queue>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;



void fast () {//int argc, char *argv[]) {
    //QApplication a(argc, argv);

    // open file
    string filename = "input100.txt";
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

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Fast Pattern Recognition");
    view->show();

    auto cmp = [](pair<Point, double> first, pair<Point, double> second){return first.second > second.second;};

    auto begin = chrono::high_resolution_clock::now();
    for(Point p: points) {
        priority_queue<pair<Point, double>, vector<pair<Point, double>, decltype(cmp)> slopes(cmp);
        for (Point q: points) {
            slopes.push(pair<Point, double>(q, p.slopeTo(q)));
        }
        int count = 1;
        double slope;
        vector<Point> pointsToDraw;
        while (!slopes.empty()) {
            if(slope == slopes.top().second) {
                count++;
                pointsToDraw.push_back(slopes.top().first);
            } else if(count >= 3) {
                for(Point q: pointsToDraw) {
                    render_line(scene, p, q);
                }
                count = 1;
                pointsToDraw.clear();
            } else {
                count = 1;
                pointsToDraw.clear();
            }
            slopes.pop();
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    //return a.exec(); // start Qt event loop
}
