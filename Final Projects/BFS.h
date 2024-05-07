#pragma once

#include <iterator>
#include <queue>
#include <vector>
#include "graph.h"

using namespace std;


class BFS {
  public:

    class Iterator : std::iterator<std::forward_iterator_tag, NetflixGraph::GraphVertex> {
      public:
        ~Iterator();
        Iterator();
        Iterator(BFS* traversal, NetflixGraph::GraphVertex* start);
        Iterator & operator++();
        NetflixGraph::GraphVertex* operator*();
        bool operator!=(const Iterator &other);

      private:
        NetflixGraph::GraphVertex* current;
        BFS* traversal;
    };

    BFS(const NetflixGraph& graph, NetflixGraph::GraphVertex* start);
    BFS();
    Iterator begin();
    Iterator end();

    void add(NetflixGraph::GraphVertex* vertex);
    NetflixGraph::GraphVertex* pop();
    NetflixGraph::GraphVertex* peek() const;  
    bool empty() const;
    
  private:
    NetflixGraph graph;
    NetflixGraph::GraphVertex* start;
    queue<NetflixGraph::GraphVertex*> toVisit;
    vector<bool> visited;
};
