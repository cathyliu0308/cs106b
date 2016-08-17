#include "trailblazer.h"
#include "basicgraph.h"
#include "Color.h"
#include "pqueue.h"
#include "queue.h"
#include "stack.h"
#include "map.h"
#include "vector.h"

using namespace std;

bool DFSHelper(Vertex* start, Vertex* end, Vector<Vertex*>& path, BasicGraph& graph);
bool sameGroup(Vertex* v1, Vertex* v2, Vector<Set<Vertex*>>& vertexGroups);
void mergeGroups(Vertex* v1, Vertex* v2, Vector<Set<Vertex*>>& vertexGroups);

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    DFSHelper(start,end,path,graph);
    return path;
}
bool DFSHelper(Vertex* start, Vertex* end, Vector<Vertex*>& path, BasicGraph& graph) {
    if (start->visited == true) {
        return false;
    }
    start->visited = true;
    start->setColor(GREEN);
    path.add(start);
    if (start == end) {
        return true;
    }
    Set<Edge*> edges = start->edges;
    for (Edge* edge : edges) {
        if (DFSHelper(edge->finish,end,path,graph) == true)
            return true;
    }
    path.remove(path.size() - 1);
    start->setColor(GRAY);
    return false;
}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    if (start == end) {
        start->visited = true;
        start->setColor(GREEN);
        path.add(start);
        return path;
    }
    Queue<Vertex*> q;
    //start->visited = true;
    q.enqueue(start);
    start->setColor(YELLOW);
    while (q.size() > 0) {
        Vertex* v = q.dequeue();
        v->visited = true;
        if (v != end) {
            Set<Edge*> edges = v->edges;
            for (Edge* edge : edges) {
                if (edge->finish->visited == false) {
                    q.enqueue(edge->finish);
                    edge->finish->setColor(YELLOW);
                    edge->finish->previous = v;
                }
            }
        }
        else {
            while(true) {
                if (v->previous == NULL) {
                    path.insert(0, v);
                    v->setColor(GREEN);
                    break;
                }
                else {
                    path.insert(0, v);
                    v->setColor(GREEN);
                    v = v->previous;
                }
            }
            break;
        }
    }
    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    if (start == end) {
        start->visited = true;
        start->setColor(GREEN);
        path.add(start);
        return path;
    }
    Set<Vertex*> vertex = graph.getVertexSet();
    for (Vertex* v : vertex) {
        v->cost = POSITIVE_INFINITY;
    }
    PriorityQueue<Vertex*> pq;
    start->cost = 0;
    pq.enqueue(start,start->cost);
    start->setColor(YELLOW);
    while (pq.size() > 0) {
        Vertex* v = pq.dequeue();
        v->visited = true;
        if (v != end) {
            Set<Edge*> edges = v->edges;
            for (Edge* edge : edges) {
                if (edge->finish->visited == false) {
                    double cost = v->cost + edge->cost;
                    if (cost < edge->finish->cost) {
                        edge->finish->cost = cost;
                        if (edge->finish->getColor() != YELLOW) {
                            pq.enqueue(edge->finish,cost);
                            edge->finish->setColor(YELLOW);
                        }
                        else {
                            pq.changePriority(edge->finish,cost);
                        }
                        edge->finish->previous = v;
                    }
                }
            }
        }
        else {
            while(true) {
                if (v->previous == NULL) {
                    path.insert(0, v);
                    v->setColor(GREEN);
                    break;
                }
                else {
                    path.insert(0, v);
                    v->setColor(GREEN);
                    v = v->previous;
                }
            }
            break;
        }
    }
    return path;
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    if (start == end) {
        start->visited = true;
        start->setColor(GREEN);
        path.add(start);
        return path;
    }
    Set<Vertex*> vertex = graph.getVertexSet();
    for (Vertex* v : vertex) {
        v->cost = POSITIVE_INFINITY;
    }
    PriorityQueue<Vertex*> pq;
    double h = heuristicFunction(start, end);
    start->cost = 0;
    pq.enqueue(start,start->cost + h);
    start->setColor(YELLOW);
    while (pq.size() > 0) {
        Vertex* v = pq.dequeue();
        v->visited = true;
        if (v != end) {
            Set<Edge*> edges = v->edges;
            for (Edge* edge : edges) {
                if (edge->finish->visited == false) {
                    double h = heuristicFunction(edge->finish, end);
                    double cost = v->cost + edge->cost;
                    if (cost < edge->finish->cost) {
                        edge->finish->cost = cost;
                        if (edge->finish->getColor() != YELLOW) {
                            pq.enqueue(edge->finish,cost + h);
                            edge->finish->setColor(YELLOW);
                        }
                        else {
                            pq.changePriority(edge->finish,cost + h);
                        }
                        edge->finish->previous = v;
                    }
                }
            }
        }
        else {
            while(true) {
                if (v->previous == NULL) {
                    path.insert(0, v);
                    v->setColor(GREEN);
                    break;
                }
                else {
                    path.insert(0, v);
                    v->setColor(GREEN);
                    v = v->previous;
                }
            }
            break;
        }
    }
    return path;
}



Set<Edge*> kruskal(BasicGraph& graph) {
    graph.resetData();
    Set<Edge*> mst;
    Set<Edge*> edges = graph.getEdgeSet();
    Set<Vertex*> vertices = graph.getVertexSet();

    PriorityQueue<Edge*> pq;
    for (Edge* e : edges) {
        pq.add(e, e->cost);
    }

    Vector<Set<Vertex*>> vertexGroups;
    for (Vertex* vertex : vertices) {
        Set<Vertex*> vGroup;
        vGroup.add(vertex);
        vertexGroups.add(vGroup);
    }

    while (pq.size() > 0) {
        Edge* e = pq.dequeue();
        if (! sameGroup(e->start, e->finish, vertexGroups)) {
            mst.add(e);
            mergeGroups(e->start, e->finish, vertexGroups);
        }
    }
    return mst;
}

bool sameGroup(Vertex* v1, Vertex* v2, Vector<Set<Vertex*>>& vertexGroups) {
    //Set<Vertex*> vGroup;
    int i;
    for (i = 0; i < vertexGroups.size(); i++) {
        if (vertexGroups[i].contains(v1)) {
            break;
        }
    }
    if (vertexGroups[i].contains(v2)) {
        return true;
    }
    else
        return false;
}

void mergeGroups(Vertex* v1, Vertex* v2, Vector<Set<Vertex*>>& vertexGroups) {
    int index1;
    int index2;
    for (int i = 0; i < vertexGroups.size(); i ++) {
        if (vertexGroups[i].contains(v1)) {
            index1 = i;
        }
        else if (vertexGroups[i].contains(v2)) {
            index2 = i;
        }
    }
    vertexGroups[index1] += vertexGroups[index2];
    vertexGroups.remove(index2);
}
