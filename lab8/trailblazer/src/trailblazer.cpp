// TDDD86 aleev379 robka246

//#include <Set>
#include "costs.h"
#include "trailblazer.h"
#include "pqueue.h"
#include <queue>

using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    start->visited = true;
    if (start == end) {
        vector<Vertex*> retVec;
        start->setColor(GREEN);
        retVec.push_back(start);
        return retVec;
    } else {
        for (Edge* e: graph.getEdgeSet(start)) {
            if (!e->finish->visited) {
                e->finish->setColor(GRAY);
                vector<Vertex*> theVec;
                theVec.push_back(start);
                vector<Vertex*> tempVec = depthFirstSearch(graph, e->finish, end);
                theVec.insert(theVec.end(), tempVec.begin(), tempVec.end());
                if (theVec.back() == end) {
                    start->setColor(GREEN);
                    return theVec;
                }
            }
        }
    }
    vector<Vertex*> path;
    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    queue<vector<Vertex*>> aQueue;
    vector<Vertex*> firstVec;
    start->visited = true;
    firstVec.push_back(start);
    aQueue.push(firstVec);
    while(!aQueue.empty()) {
        Vertex* ver = aQueue.front().back();
        if(ver == end) {
            end->setColor(GREEN);
            return aQueue.front();
        }
        for (Edge* e: graph.getEdgeSet(ver)) {
            vector<Vertex*> newVec = vector<Vertex*>(aQueue.front());
            newVec.back()->setColor(GREEN);
            if (!e->finish->visited) {
                e->finish->setColor(Color(YELLOW));
                e->finish->visited = true;
                newVec.push_back(e->finish);
                aQueue.push(newVec);
            }
        }
        aQueue.pop();
    }

    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> prioQ;
    start->visited = true;
    //prioQ.enqueue(start, 0.0);
    for(Vertex* v: graph.getNodeSet()) {
        v->cost = INFINITY;
        prioQ.enqueue(v, INFINITY);
    }
    start->cost = 0.0;
    prioQ.changePriority(start, 0.0);
    while(!prioQ.isEmpty()) {
        Vertex* ver = prioQ.dequeue();
        ver->setColor(GREEN);
        for(Edge* e: graph.getEdgeSet(ver)) {
            if(!e->finish->visited) {
                double cost = ver->cost + e->cost;
                if (cost < e->finish->cost) {
                    e->finish->cost = cost;
                    e->finish->previous = ver;
                    prioQ.changePriority(e->finish, cost);
                }

                e->finish->setColor(YELLOW);
            }
        }
        ver->visited = true;
        if (end->visited) {
            Vertex* vert = end;
            vector<Vertex*> retVec;
            retVec.push_back(vert);
            while (vert != start) {
                vert = vert->previous;
                retVec.push_back(vert);
            }
            return retVec;
        }
    }
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> prioQ;
    start->visited = true;
    for(Vertex* v: graph.getNodeSet()) {
        v->cost = INFINITY;
        prioQ.enqueue(v, INFINITY);
    }
    start->cost = 0.0;
    prioQ.changePriority(start, 0.0);
    while(!prioQ.isEmpty()) {
        Vertex* ver = prioQ.dequeue();
        ver->setColor(GREEN);
        for(Edge* e: graph.getEdgeSet(ver)) {
            if(!e->finish->visited) {
                double cost = ver->cost + e->cost;
                if (cost < e->finish->cost) {
                    e->finish->cost = cost;
                    e->finish->previous = ver;
                    prioQ.changePriority(e->finish, cost + e->finish->heuristic(end));
                }

                e->finish->setColor(YELLOW);
            }
        }
        ver->visited = true;
        if (end->visited) {
            Vertex* vert = end;
            vector<Vertex*> retVec;
            retVec.push_back(vert);
            while (vert != start) {
                vert = vert->previous;
                retVec.push_back(vert);
            }
            return retVec;
        }
    }
    vector<Vertex*> path;
    return path;
}
