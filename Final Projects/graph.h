#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;

class NetflixGraph 
{
    
    public:
        NetflixGraph(string filename);
        NetflixGraph();
        ~NetflixGraph();
        struct GraphEdge 
        {
            int v1;
            int v2;
            string show_name;
            GraphEdge(int setV1, int setV2)
            {
                v1 = setV1;
                v2 = setV2;
                show_name = "\0";
            }
            GraphEdge(int setV1, int setV2, string set_name){
                v1 = setV1;
                v2 = setV2;
                show_name = set_name;
            }
            int getAnother(int v);
        };

        struct GraphVertex 
        {
            GraphVertex(string setName) {
                name = setName;
            }
            string name;
            vector<string> movies;
            vector<GraphEdge*> ajacent_edges;
            bool operator== (GraphVertex const & other);
        };
        int find(GraphVertex* toFind);
    private:
        /**
         * function that takes in data from a .json file and turns it into NetflixGraph Vertices
         * data should be in the json form that is like the following:
         * 
         *  [{
         *  "title": "Coders",
         *  "director": "Matthew Novelli",
         *  "cast": "Adam Urish"
         *  },
         *  {
         *  "title": "JaSON",
         *  "director": "Vance Ursiny",
         *  "cast": "Jason Zou"
         *  }
         *  ]
         * 
         * @param filename a string of the filename to look for when deserializing the data
         */
        void deserialize(string filename); //take in contents of file, form it into graph
        
        /**
         * a helper function for processList, ultimately helping deserialize
         * 
         * given a list of actors to deserialize, a string of the curr_actor, and the movie corresponding to the list of actors,
         * insert these actors into a list.
         * 
         * If the curr_actor is already in the graph, then don't add another vertex. Instead, add the corresponding movie to the list
         * of movies in the already existing vertex corresponding to the actor in the graph
         * 
         * @param actors vector of actors corresponding to the movie
         * @param curr_actor string representing the state of the current actor being processed
         * @param movie the movie corresponding to the current list of actors
         */
        void helpDeserialize(vector<string>& actors, string& curr_actor, string& movie);

        /**
         * a helper function for deserialize
         * 
         * processes the list of people that are a part of the movie that is represented by the movie param
         * uses helpDeserialize to organize these actors into the list of vertices that make up the graph
         * 
         * @param people the current string in the json file that we are processing
         * @param actors actors that have already been included in the graph
         * @param curr_actor the string representing the current actor in process
         * @param movie the movie corresponding to the current actor
         */
        void processList(string& people, vector<string>& actors, string& curr_actor, string& movie);
        void _copy(NetflixGraph const & other);

        /**
         * Deserializes and then traverses through actors and makes edges if there are common movies between two actors/directors.
         * 
         * @param filename the string containing the filename to deserialize
         */ 
        void buildGraph(string filename);

        /**
         * Takes in two vertices as parameters.
         * If two actors/directors have a movie in common, it returns true and the name of the movie.
         * If no such movie exists, it returns false.
         * 
         * @param v1 the vertex containing data of first actor/director
         * @param v2 the vertex containing data of secon actor/director
         * 
         * @returns std::pair<bool, string> containing whether there is a common movie and if so what its name is.
         */
        std::pair<bool, string> cooperate(GraphVertex* v1, GraphVertex* v2);

        std::vector<GraphEdge*> edges_;
        std::vector<GraphVertex*> vertices_;

        /** Returns index of actor in vertices_ if found.
         *  Returns -1 if not found
         */
        int findActor(string name);
        

        /**
         * Finds the shortest path from vertices_[actor1_index] to vertices_[actor2_index] using dijkstra with a priority queue
         * Returns a map showing the previous node for each node traversed
         */
        std::map<int, int> shortestPath(int actor1_index, int actor2_index);

        /**
         * Extracts the path from the previous map provided by the shortestPath function
         * Returns a stack containing names of the shows along the path
         */
        std::stack<string> extractPath(std::map<int, int> previous, int actor1_index, int actor2_index);

    public:
        /**
         * Finds and prints out the shortest path between actor1 and actor2 and its length if a path exists using the dijkstra algorithm
         * @param actor1 first actor to find the path with
         * @param actor2 second actor to find the path with
         * @return a vector of strings containing the movies that make up the shortest path between the actors
         *         if it exists. Else, an empty vector
         */
        vector<string> dijkstra(string actor1, string actor2);
        const NetflixGraph& operator= (NetflixGraph const & other);

        /**
         * returns a vector of the vertices that help make up the graph. Used in testing cases
         * @return vector of vertex pointers that help form the graph
         */
        vector<GraphVertex*> getVertices() const {
            return vertices_;
        }

        /**
         * returns a vector of the edges that help make up the graph. Used in testing cases
         * @return vector of edge pointers that help form the graph
         */
        vector<GraphEdge*> getEdges() const {
            return edges_;
        }

        /**
         * Prints out the given path in the console
         * @param path the path to print
         */
        void printpath(std::vector<string>& path);

        /**
         * Helper function for findpath(), returns if the string is not in path
         * @param x the actor name
         * @param path the path to search
         * @return if the string is not in the path
         */
        bool isNotVisited(string x, std::vector<string>& path);

        /**
         * Actual all_paths driver code.  Finds all paths between "start" and "end" under the max size
         * Based on code by Abhishek Dey @ https://efficientcodeblog.wordpress.com/2018/02/15/finding-all-paths-between-two-nodes-in-a-graph/
         * @param start the name of the desired actor at the beginning of the path
         * @param end the name of the desired actor at the end of the path
         * @return a vector of all found paths
         */
        vector<vector<string>> findpaths(string start, string end, int size);

        //all paths found by findpaths()
        vector<vector<string>> paths;
};