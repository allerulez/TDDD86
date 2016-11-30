// TDDD86 aleev379 robka246

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    // Constructor
    Tour();
    // Destructor
    ~Tour();
    // Prints all points in the linked list
    void const show();
    // Displays the path
    void const draw(QGraphicsScene* scene);
    // Returns the amount of elements in the linked list
    int const size();
    // Returns the Euklidian distance of the path
    double const distance();
    // Inserts a new Node using a nearest neighbour algorithm
    void insertNearest(const Point &p);
    // Inserts a new Node using a smallest increase algorithm
    void insertSmallest(const Point &p);

private:
    Node* firstNode;
};

#endif // TOUR_H
