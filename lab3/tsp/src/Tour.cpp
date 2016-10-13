#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

    firstNode = NULL;
}

Tour::~Tour()
{

    Node* next = firstNode;

    while(next != NULL) {
        Node* gone = next;
        next = next->next;
        delete gone;
    }
}

void const Tour::show()
{
    bool firstLap = true;
    Node *first = firstNode;
    while(firstLap) {
        first->point.toString();
        first = first->next;
        if (first == firstNode) {
        firstLap = false;
        }
    }
}

void const Tour::draw(QGraphicsScene *scene)
{
    bool firstLap = true;
    Node *first = firstNode;
    while(firstLap) {
        first->point.drawTo(first->next->point, scene);
        first = first->next;
        if (first == firstNode) {
        firstLap = false;
        }
    }
}

int const Tour::size()
{
    int tourSize = 0;
    bool firstLap = true;
    Node *first = firstNode;
    while(firstLap) {
        tourSize++;
        first = first->next;
        if (first == firstNode) {
        firstLap = false;
        }
    }
    return tourSize;
}

double const Tour::distance()
{
    double tourDistance = 0.0;
    bool firstLap = true;
    Node *first = firstNode;
    while(firstLap) {
        tourDistance += first->point.distanceTo(first->next->point);
        first = first->next;
        if (first == firstNode) {
        firstLap = false;
        }
    }
    return tourDistance;
}

void Tour::insertNearest(Point p)
{

    if(firstNode == NULL) {
        firstNode = new Node(p, NULL);
        firstNode->next = firstNode;
    } else {
        bool firstLap = true;
        Node* nearest = firstNode;
        Node* first = firstNode;
        double distanceToP = first->point.distanceTo(p);
        while(firstLap) {
            double temp = first->point.distanceTo(p);
            if(temp < distanceToP) {
                distanceToP = temp;
                nearest = first;
            }
            first = first->next;
            if (first == firstNode) {
                firstLap = false;
            }
        }
        Node* newNode = new Node(p, nearest->next);
        nearest->next = newNode;
    }
}

void Tour::insertSmallest(Point p)
{
    if(firstNode == NULL) {
        firstNode = new Node(p, NULL);
        firstNode->next = firstNode;
    }
    bool firstLap = true;
    Node* nearest = firstNode;
    Node* first = firstNode;
    double distanceBetween = (first->point.distanceTo(p) + first->next->point.distanceTo(p)) - (first->point.distanceTo(first->next->point));
    while(firstLap) {
        double temp = (first->point.distanceTo(p) + first->next->point.distanceTo(p)) - (first->point.distanceTo(first->next->point));
        if(temp < distanceBetween) {
            distanceBetween = temp;
            nearest = first;
        }
        first = first->next;
        if (first == firstNode) {
        firstLap = false;
        }
    }
    Node* newNode = new Node (p, nearest->next);
    nearest->next = newNode;
}
