#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

    firstNode = nullptr;
}

Tour::~Tour()
{

    Node* next = firstNode->next;
    while(true) {
        Node* gone = next;
        next = next->next;
        if (gone==firstNode) {
            break;
        }
        delete gone;

    }
}

void const Tour::show()
{
    bool shouldLoop = true;
    Node *first = firstNode;
    while(shouldLoop) {
        first = first->next;
        if (first == firstNode) {
            shouldLoop = false;
        }
    }
}

void const Tour::draw(QGraphicsScene *scene)
{
    bool shouldLoop = true;
    Node *first = firstNode;
    while(shouldLoop) {
        first->point.drawTo(first->next->point, scene);
        first = first->next;
        if (first == firstNode) {
            shouldLoop = false;
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
    bool shouldLoop = true;
    Node *first = firstNode;
    while(shouldLoop) {
        tourDistance += first->point.distanceTo(first->next->point);
        first = first->next;
        if (first == firstNode) {
            shouldLoop = false;
        }
    }
    return tourDistance;
}

void Tour::insertNearest(const Point &p)
{

    if(firstNode == nullptr) {
        firstNode = new Node(p, nullptr);
        firstNode->next = firstNode;
    } else {
        bool shouldLoop = true;
        Node* nearest = firstNode;
        Node* first = firstNode;
        double distanceToP = first->point.distanceTo(p);
        while(shouldLoop) {
            double temp = first->point.distanceTo(p);
            if(temp < distanceToP) {
                distanceToP = temp;
                nearest = first;
            }
            first = first->next;
            if (first == firstNode) {
                shouldLoop = false;
            }
        }
        Node* newNode = new Node(p, nearest->next);
        nearest->next = newNode;
    }
}

void Tour::insertSmallest(const Point &p)
{
    if(firstNode == nullptr) {
        firstNode = new Node(p, nullptr);
        firstNode->next = firstNode;
    }
    bool firstLap = true;
    Node* nearest = firstNode;
    Node* first = firstNode;
    double distanceBetween = (first->point.distanceTo(p)
                              + first->next->point.distanceTo(p))
            - (first->point.distanceTo(first->next->point));
    while(firstLap) {
        double temp = (first->point.distanceTo(p)
                       + first->next->point.distanceTo(p))
                - (first->point.distanceTo(first->next->point));
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
