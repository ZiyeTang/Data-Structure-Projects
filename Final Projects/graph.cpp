#include "graph.h"
#include <fstream>
#include <functional>
#include <climits>
#include "nlohmann/json.hpp"

using nlohmann::json;

/**
 * Compare if two graph vertices are the same.
 */
bool NetflixGraph::GraphVertex::operator== (GraphVertex const & other)
{
    return this->name==other.name && this->movies==other.movies;
}

/**
 * Given the index of vertex, return the index of another vertex that connected by this edge.
 */
int NetflixGraph::GraphEdge::getAnother(int v)
{
    if(v==v1)
        return v2;
    if(v==v2)
        return v1;
    return -1;
}

NetflixGraph::~NetflixGraph()
{
    for(size_t i=0;i<edges_.size();i++)
    {
        if(edges_[i]!=NULL)
        {
            delete edges_[i];
            edges_[i]=NULL;
        }
    }
    for(size_t i=0;i<vertices_.size();i++)
    {
        if(vertices_[i]!=NULL)
        {
            delete vertices_[i];
            vertices_[i]=NULL;
        }
    }
}

NetflixGraph::NetflixGraph() 
{
}

NetflixGraph::NetflixGraph(const string filename) {
    buildGraph(filename);
}

void NetflixGraph::deserialize(const string filename) {
    vector<string> actors;
    std::ifstream input(filename);
    json j;
    input >> j;
    int i = 0;
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        string movie = j[i]["title"]; // gets the movie we are on
        string cast = j[i]["cast"]; // gets the cast of the movie we are on
        string director = j[i]["director"]; // gets the director of the movie
        
        string curr_actor = "";

        processList(director, actors, curr_actor, movie);
        processList(cast, actors, curr_actor, movie);

        i++;
    }
    return;
}

void NetflixGraph::helpDeserialize(vector<string>& actors, string& curr_actor, string& movie) {
    if (!std::count(actors.begin(), actors.end(), curr_actor)) {
        actors.push_back(curr_actor);
        GraphVertex* vertex = new GraphVertex(curr_actor);
        vertex->movies.push_back(movie);
        vertices_.push_back(vertex);
    } else {
        vector<string>::iterator itr = std::find(actors.begin(), actors.end(), curr_actor);
        int idx = std::distance(actors.begin(), itr);
        vertices_[idx]->movies.push_back(movie);
    }
}

void NetflixGraph::processList(string& people, vector<string>& actors, string& curr_actor, string& movie) {
    for (size_t k = 0; k < people.size(); k++) {
        if (people[k] == ',') {
            helpDeserialize(actors, curr_actor, movie);
            curr_actor = "";
            k++;
        } else {
            curr_actor += people[k];
        }
    }
    if (curr_actor != "") {
        helpDeserialize(actors, curr_actor, movie);
        curr_actor = "";
    }
}

/**
 * Traverses through actors and makes edges if there are common movies between two actors/directors.
 */
void NetflixGraph::buildGraph(const string filename) 
{    
    deserialize(filename);

    for(size_t i=0; i<vertices_.size(); i++)
    {
        for(size_t j=i+1; j<vertices_.size(); j++)
        {
            std::pair<bool, string> connection = cooperate(vertices_[i], vertices_[j]);
            if(connection.first){
                GraphEdge* edge = new GraphEdge(i,j, connection.second);
                edges_.push_back(edge);
                vertices_[i]->ajacent_edges.push_back(edge);
                vertices_[j]->ajacent_edges.push_back(edge);
            }
        }
    }
}

/**
 * Helper function for buildGraph.
 * If two actors/directors have a movie in common, it returns true and the name of the movie.
 * If no such movie exists, it returns false.
 * 
 * @param v1 the vertex containing data of first actor/director
 * @param v2 the vertex containing data of secon actor/director
 * 
 * @returns std::pair<bool, string> containing whether there is a common movie and if so what its name is.
 */
std::pair<bool, string> NetflixGraph::cooperate(GraphVertex* v1, GraphVertex* v2)
{
    for(size_t i=0; i<v1->movies.size(); i++)
    {
        for(size_t j=0; j<v2->movies.size(); j++)
        {
            if(v1->movies[i]==v2->movies[j]){
                return std::pair<bool, string>(true, v1->movies[i]);
            }
        }
    }
    return std::pair<bool, string>(false, "\0");
}

/**
 * Helper function for operator=(NetflixGraph const & other)
 * copy the given graph to this graph.
 */
void NetflixGraph::_copy(NetflixGraph const & other) 
{
    vertices_.clear();
    edges_.clear();
    vector<GraphVertex*> otherVertices = other.getVertices();
    vector<GraphEdge*> otherEdges=other.getEdges();

    for (auto it=otherVertices.begin(); it!=otherVertices.end(); it++) 
    {
        GraphVertex* v=new GraphVertex((*it)->name);
        v->movies=(*it)->movies;
        for(auto it2=(*it)->ajacent_edges.begin(); it2!=(*it)->ajacent_edges.end();it2++)
        {
            v->ajacent_edges.push_back(*it2);
        }
        vertices_.push_back(v);
    }

    for (auto it=otherEdges.begin(); it!=otherEdges.end(); it++) 
    {
        edges_.push_back(new GraphEdge((*it)->v1, (*it)->v2));
    }
}

/**
 * Do assignment between NetflixGraph objects.
 */
const NetflixGraph& NetflixGraph::operator= (NetflixGraph const & other)
{
    _copy(other);
    return *this;
}

/**
 * Finds and prints out the shortest path between actor1 and actor2 if a path exists using 
 * the dijkstra algorithm
 */
vector<string> NetflixGraph::dijkstra(string actor1, string actor2){
    int actor1_index = findActor(actor1);
    int actor2_index = findActor(actor2);
    if(actor1_index == -1){
        return vector<string>();
    }
    if(actor2_index == -1){
        return vector<string>();
    }
    if(actor1_index == actor2_index){
        return vector<string>();
    }

    std::map<int, int> previous = shortestPath(actor1_index, actor2_index);


    if(previous.find(actor2_index) == previous.end()){
        return vector<string>();
    }

    stack<string> path = extractPath(previous, actor1_index, actor2_index);
    
    vector<string> ret; // vector of the path to return
    while(!path.empty()){
        ret.push_back(path.top());
        path.pop();
    }
    return ret;
}

/**
 * Extracts the path from the previous map provided by the shortestPath function
 * Returns a stack containing names of the shows along the path
 */
std::stack<string> NetflixGraph::extractPath(std::map<int, int> previous, int actor1_index, int actor2_index){
    stack<string> path;
    int curr_index = actor2_index;
    while(curr_index != actor1_index){
        int connecting_index = previous.find(curr_index)->second;
        GraphVertex* curr_node = vertices_.at(curr_index);
        for(size_t i = 0; i < curr_node->ajacent_edges.size(); i++){
            if((curr_node->ajacent_edges.at(i)->v1 == connecting_index) || (curr_node->ajacent_edges.at(i)->v2 == connecting_index)){
                path.push(curr_node->ajacent_edges.at(i)->show_name);
                curr_index = connecting_index;
                break;
            }
        }
    }
    return path;
}

/**
 * Finds the shortest path from vertices_[actor1_index] to vertices_[actor2_index] using dijkstra with a priority queue
 * Returns a map showing the previous node for each node traversed
 */
std::map<int, int> NetflixGraph::shortestPath(int actor1_index, int actor2_index){
    //initialize distances
    std::map<int, int> distances;   //vertex, distance
    for(size_t i = 0; i < vertices_.size(); i++){
        distances.insert(make_pair(i, INT_MAX));
    }
    distances.find(actor1_index)->second = 0;

    std::map<int, int> previous; //(vertex index, previous vertex index)
    std::priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, greater<std::pair<int, int>>> pri_q;  //priority queue (distance, vertex_index)
    std::map<int, bool> visited; // whether a vertex has been visited or not
    pri_q.push(make_pair(0, actor1_index));

    while(!pri_q.empty() && (pri_q.top().second != actor2_index)){
        std::pair<int, int> curr = pri_q.top();
        GraphVertex* curr_node = vertices_[curr.second];
        if(visited.find(curr.second) == visited.end()){ // if it has not been visited
            for(size_t i = 0; i < curr_node->ajacent_edges.size(); i++){
                int connecting_node;
                connecting_node = (curr_node->ajacent_edges.at(i)->v1 == curr.second ? curr_node->ajacent_edges.at(i)->v2 : curr_node->ajacent_edges.at(i)->v1);
                if(visited.find(connecting_node) == visited.end()){
                    auto dist = distances.find(connecting_node);
                    if((curr.first + 1) < dist->second){    // if the distance will be shortened, set new distance and assign to previous
                        dist->second = curr.first + 1;
                        auto prev = previous.find(connecting_node);
                        if(prev == previous.end()){
                            previous.insert(make_pair(connecting_node, curr.second));
                        }else{
                            prev->second = curr.second;
                        }

                        pri_q.push(make_pair(curr.first + 1, connecting_node));
                    }
                }
            }
        }
        visited.insert(make_pair(curr.second, true));
        pri_q.pop();
    }
    return previous;
}

/** Returns index of actor in vertices_ if found.
 *  Returns -1 if not found
 */
int NetflixGraph::findActor(string name){
    for(size_t i = 0; i < vertices_.size(); i++){
        if(vertices_[i]->name == name){
            return i;
        }
    }
    return -1;
}

/**
 * Take the pointer to a vertex and return the index of that vertex in
 * in the vector of vertices called "vertices_".
 * @param toFind the pointer to the vertex to find.
 */
int NetflixGraph::find(GraphVertex* toFind)
{
    int idx=0;
    for(auto it=vertices_.begin(); it!=vertices_.end(); it++)
    {
        if(*toFind==**it)
        {
            return idx;
        }
        idx++;
    }
    return -1;
}

/**
 * Helper function for findpath(), returns if the string is not in path
 * @param x the actor name
 * @param path the path to search
 * @return if the string is not in the path
*/
bool NetflixGraph::isNotVisited(string x, vector<string>& path) {
    int size = path.size();
    for (int i = 0; i < size; i++) {
        if (path[i] == x) {
            return false;
        }
    }
    return true;
}

/**
 * Actual all_paths driver code.  Finds all paths between "start" and "end" under the max size
 * Based on code by Abhishek Dey @ https://efficientcodeblog.wordpress.com/2018/02/15/finding-all-paths-between-two-nodes-in-a-graph/
 * @param start the name of the desired actor at the beginning of the path
 * @param end the name of the desired actor at the end of the path
 * @return a vector of all found paths
 */
vector<vector<string>> NetflixGraph::findpaths(string start, string end, int size) {
    //initialize queue (to store paths), vector (for storing the actual path), and paths container (for exporting list of paths)
    paths.clear();
    std::queue<std::vector<string>> q;
    std::vector<string> path;

    path.push_back(start);

    q.push(path);


    while(!q.empty() && (size == -1 || int(path.size()) <= size)) {
        //initialize path and queue
        path = q.front();
        q.pop();

        //search for the last actor in the path. if does not exist (findActor()==-1), break loop
        string last = path[path.size() - 1];
        int lastIndex = findActor(last);
        if (lastIndex == -1) {
            std::cout << "Invalid actor name(s). Check and try again." << std::endl;
            paths.clear();
            break;
        }
        //if last actor of current current path is destination, send path to final vector and print
        if (last == end && path.size() > 1 && path[0] == start && path[path.size()-1] == end) { 
            printpath(path);
            paths.push_back(path);
        }
        //main logic -- find adjacent edges of last vertex in path
        //if its not visited, start a new path and insert into queue
        for (size_t i = 0; i < vertices_[lastIndex]->ajacent_edges.size(); i++) {
            //each edge has two listed verticies -- this block of code decides which one to use
            int index;
            int V1index = vertices_[lastIndex]->ajacent_edges[i]->v1;
            int V2index = vertices_[lastIndex]->ajacent_edges[i]->v2;
            (vertices_[V1index] != vertices_[lastIndex]) ? index = V1index : index = V2index;

            if (isNotVisited(vertices_[index]->name, path)) {
                std::vector<string> newpath(path);
                newpath.push_back(vertices_[index]->name);
                q.push(newpath);
            }
        }
    }
    return paths;
}

/**
 * Prints out the given path in the console
 * @param path the path to print
 */
void NetflixGraph::printpath(vector<string>& path) {
    if (path.size() == 0) {
        std::cout << "No paths found." << std::endl;
    } else {
        std::cout << std::endl << "(" << path.size() << ") ";
        for (auto i : path) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

}