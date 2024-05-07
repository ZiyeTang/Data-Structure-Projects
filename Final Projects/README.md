# ziyet3-ajatar2-novelli3-coombes3

Our data is all Netflix Movies and TV shows as of 2019, [sourced from kaggle](https://www.kaggle.com/shivamb/netflix-shows). We can make a graph out of this data by assigning each cast member a vertex, and connecting two cast members with an edge if they have worked on the same movie or TV show.
Our first implemented algorithim is Dijkstra's alorithim, which finds the smallest number of connections linking two given cast members together. Our second implemented algorithim displays all possible paths between two cast members.
Lastly, we have implemented a BFS traversal of our data.


## How to run:
**On EWS:**
1. `make && make netflix`
2. `./netflix`

A menu will be presented in the console:
>0. Quit.
>1. Find shortest path between two actors/directors.
>2. Find all paths between two actors/directors.
>3. Traverse through our list of actors and directors
>
>Enter the number of your choice: 

After choosing the desired menu option, follow the prompts.
Upon completion of the task, the menu will appear again.

## Important files and data:
### graph.\*
These files are responsible for data processing, deserialization, and graph building. They include the dijkstra algorithim and all paths algorithim.
### BFS.\*
These files contain the codebase for running the BFS traversal.
### main.cpp
This file is responsible for running the command line interface. Inside of a while loop, it prints the menu and calls the appropriate tasks based on the user's response.
### tests/
Tests directory. Contains `tests.cpp` and `data/`. See below for more information on the test suite.
### data/

`data/netflix_titles.csv` : original, raw data 

`data/netflix_titles.json` : raw data converted into JSON 

`data/netflix_titlestruncated.csv` : raw data with unneeded columns (year, description, etc.) removed 

`data/netflix_titlestruncated.json` : raw data with unneeded columns (year, description, etc.) removed and converted into JSON 

`data/sample.json` : tiny JSON dataset, used for testing

## Test Suite
Tests suite is located at `tests/tests.cpp` and uses test data located in `tests/data/`. The test data is as follows:

`tests_1.json` Contains two films, no relation.

`tests_2.json` One film, no data.

`tests_3.json` Five films, eight cast members, some relations.

`tests_4.json` For testing dijkstra paths, paths are detailed in `tests_4_dijkstra_paths.txt` and visualized in `test_4_graph.png`.

`tests_non_english.json` Tests parsing of non-english characters

## How to run the test suite:
**On EWS:**
1. `make test`
2. `./test`

Tests for different algorithims can be run with different arguments, for example:
`./test [deserialize]`
`./test [dijkstra]`
`./test [all_paths]`

