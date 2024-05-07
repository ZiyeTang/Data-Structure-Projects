#include <iostream>
#include <string>
#include <string.h>
#include "graph.h"
#include "BFS.h"


int printMenu(ostream* out, istream* in);


int main(int argc, char *argv[]) {  //run with ./netflix for cout and cin or ./netflix {input file name or "cin"} {output file name or "cout"} without the quotes
    ostream* out = &cout;
    istream* in = &cin;
    if(argc == 3){
        if(strcmp(argv[1],"cin") == 0){       //input stream
            in = &cin;
        }else {
            ifstream* input_file = new ifstream(argv[1]);
            if(!input_file->is_open()){
                cout << "Cannot open " << argv[1] << ".\n";
                in = &cin;
            }else{
                in = input_file;                
            }
        }

        if(strcmp(argv[2],"cout") == 0){      //output stream
            out = &cout;
        }else{
            out = new ofstream(argv[2]);
        }
    } else if(argc != 1){
        cout << "Invalid parameter count, defaulting to cout and cin.\n";
    }

    int idx = 0;
    const string filename = "data/sample.json"; // data/netflix_titlestruncated.json";

    NetflixGraph netflixGraph(filename);
    vector<NetflixGraph::GraphVertex*> vertices = netflixGraph.getVertices();
    NetflixGraph::GraphVertex* start =vertices[0];
    BFS bfs(netflixGraph, start);
    BFS::Iterator bfs_iterator = bfs.begin();


    int choice = printMenu(out, in);
    while(choice != 0){
        if(choice == 1){            //dijkstra
            in->ignore();
            *out << "Enter the name of the first actor/director: ";
            std::string actor1, actor2;
            std::getline(*in, actor1);
            *out << "Enter the name of the second actor/director: ";
            std::getline(*in, actor2);
            vector<string> shortest_path = netflixGraph.dijkstra(actor1, actor2);
            *out << endl << "Length of Path: " << shortest_path.size() << endl;
            if (shortest_path.empty()) {
                *out << endl << "No path was found between " << actor1 << " and " << actor2 << endl;
            }
            *out << endl;
            for (const string& s : shortest_path) {
                *out << s << endl;
            }
        } else if(choice == 2){         //all paths
            in->ignore();
            *out << "Enter the name of the first actor/director: ";
            std::string actor1, actor2;
            int size = -1;
            std::getline(*in, actor1);
            *out << "Enter the name of the second actor/director: ";
            std::getline(*in, actor2);
            *out << "Enter the maximum path size, or -1 for infinite (dangerous!): ";
            std::cin >> size;
            vector<string> check = netflixGraph.dijkstra(actor1, actor2);
            if (check.size() == 0) {
                std::cout << "No path found between these actor/directors." << std::endl;
            } else {
                vector<vector<string>> allpaths = netflixGraph.findpaths(actor1, actor2, size);
                if (allpaths.size() == 0) {
                    std::cout << "No paths found between these actor/directors." << std::endl;
                }
            }
        } else if(choice == 3) {         //traversal
            NetflixGraph::GraphVertex* current = *bfs_iterator;
            *out << endl << current->name << endl;
        } else if (choice == 4) {
            int steps = 1;
            *out << endl << "Input how many steps would you like to traverse (default = 1): ";
            *in >> steps;
            if (in->fail()) {
                steps = 1;
                in->clear();
                in->ignore(numeric_limits<streamsize>::max(),'\n');
            }

            if (steps < 0) steps = 1;

            for (int i = 0; i < steps; i++) {
                if (bfs_iterator != bfs.end()) {
                    ++bfs_iterator;
                } else {
                    break;
                }
            }
        } else if(choice == 0){
            break;
        }else {        
            *out << "Invalid option please enter the number to the left of your choice." << endl;
        }
        choice = printMenu(out, in);
    }    

    return 0;
}

//prints the menu
int printMenu(ostream* out, istream* in){
    int choice = -1;
    *out << endl << "**************************Menu**************************" << endl;
    *out << "0. Quit." << endl;
    *out << "1. Find shortest path between two actors/directors." << endl;
    *out << "2. Find all paths between two actors/directors." << endl;
    *out << "3. Display current actor in the traversal" << endl;
    *out << "4. Advance in the traversal by a chosen amount" << endl << endl;
    *out << "Enter the number of your choice: ";
    *in >> choice;
    return choice;
}