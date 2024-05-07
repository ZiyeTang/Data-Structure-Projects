#include "BFS.h"
#include <queue>

/**
 * Destructor, which might not be useful but just in case for any possible memory leakage. 
 */
BFS::Iterator::~Iterator()
{
  if(traversal!=NULL)
  {
    traversal=NULL;
  }
}

/**
 * Default iterator constructor.
 */
BFS::Iterator::Iterator() 
{
  traversal=NULL;
}

/**
 * Initializes a iterator on a the BFS traversal 'traversal',
 * which starts at the GraphVertex `start`.
 * @param traversal in which traversal the iterator is going to be used in.
 * @param start The start vertex of this iterator
 */
BFS::Iterator::Iterator(BFS* traversal, NetflixGraph::GraphVertex* start)
{
  this->traversal=traversal;
  current=start;
  int currentIdx=traversal->graph.find(current);
  traversal->visited[currentIdx]=true;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the graph.
 */
BFS::Iterator & BFS::Iterator::operator++() 
{
  if(traversal!=NULL && !traversal->empty()) 
  {
    NetflixGraph::GraphVertex* toRemove = traversal->pop();
    int toRemoveIdx=traversal->graph.find(toRemove);
    for(size_t i=0; i<toRemove->ajacent_edges.size(); i++)
    {
      int idx=toRemove->ajacent_edges[i]->getAnother(toRemoveIdx);
      if(!traversal->visited[idx])
      {
        traversal->add(traversal->graph.getVertices()[idx]);
        traversal->visited[idx]=true;
      }
    }
    current=traversal->peek();
    if (current==NULL)
    {
        bool allVisited=true;
        for(size_t i=0; i<traversal->visited.size(); i++)
        {
          if(!traversal->visited[i])
          {
            traversal->add(traversal->graph.getVertices()[i]);
            current=traversal->graph.getVertices()[i];
            traversal->visited[i]=true;
            allVisited=false;
            break;
          }
        }
    }    
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the pointer of the current GraphVertex.
 */
NetflixGraph::GraphVertex* BFS::Iterator::operator*() 
{
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool BFS::Iterator::operator!=(const BFS::Iterator &other) 
{
  bool thisEmpty = false; 
  bool otherEmpty = false;
  if (traversal == NULL) { thisEmpty = true; }
  if (other.traversal == NULL) { otherEmpty = true; }
  if (!thisEmpty)  { thisEmpty = traversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.traversal->empty(); }
  if (thisEmpty && otherEmpty) return false; 
  else if ((!thisEmpty)&&(!otherEmpty)) return (traversal != other.traversal); 
  else return true; 
}

/**
 * Defualt constructor, which doesn't really do any thing and won't be used,
 * but needed to successfully compile.
 */
BFS::BFS()
{
    graph=NetflixGraph();
}

/**
 * Initializes a breadth-first graph traversal on a given 'graph',
 * starting at `start`.
 * @param graph The graph this BFS is going to traverse
 * @param start The start vertex of this BFS
 */
BFS::BFS(const NetflixGraph& graph, NetflixGraph::GraphVertex* start) 
{  
  this->graph = graph;
  this->start = start;
  for (size_t i=0; i<this->graph.getVertices().size(); i++) 
  {
    visited.push_back(false);
  }
  toVisit.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first GraphVertex.
 */
BFS::Iterator BFS::begin() 
{
  return Iterator(this,start);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
BFS::Iterator BFS::end() 
{
  return Iterator();
}

/**
 * Adds a GraphVertex for the traversal to visit in the future.
 */
void BFS::add(NetflixGraph::GraphVertex* vertex) 
{
  toVisit.push(vertex);
}

/**
 * Removes and returns the current GraphVertex in the traversal.
 */
NetflixGraph::GraphVertex* BFS::pop() 
{
  NetflixGraph::GraphVertex* toRemove=toVisit.front();
  toVisit.pop();
  return toRemove;
}

/**
 * Returns the current GraphVertex in the traversal.
 */
NetflixGraph::GraphVertex* BFS::peek() const 
{
  return empty() ? NULL : toVisit.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const 
{
  return toVisit.empty();
}
