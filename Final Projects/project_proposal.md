## Leading Question
Given two cast members and/or directors, we would like to find the smallest number of connections that links them together through Netflix movies and TV shows. Then, we will display the movies that connect the cast members and/or directors. We would also like to display all possiible paths given two cast members and/or directors.

## Dataset Acquisition and Processing
We propose to use the [Netflix Movies and TV shows database](https://www.kaggle.com/shivamb/netflix-shows) from Kraggle, which was last updated 3 months ago. The data is provided in a `.csv` which we have converted to JSON. We propose that each cast member will be represented by a node, and if they have worked together in a TV show or movie, they will have an edge between them. The weights of each edge will be (1/total connections). We will drop any records with missing fields.

## Graph Algorithms
For our graph traversal, we propose to implement a BFS traversal using an iterator class. The iterator constructor should take in the first actor listed in the first netflix show. each time we call operator++ on the iterator, the iterator should update its internal position to a new actor until the list of actors has reached its end.

For our first algorithm, we will incorporate Dijikstra's Algorithm for our planned functionality of finding the closest connection between any two actors from any show (given that a connection exists). The output of this algorithm should be the number of connections needed for the fastest route from one actor to another. In addition, the output should list the shows that bridged the actors together on this shortest path.

For our second algorithm, we will incorporate an algorithim to find all paths between two cast members and/or directors, given a connection exists. The output of this algorithim will be each path between the cast members, numbers of cast members in each path, and total paths. We will not list the TV shows/movies to save screen space. In the event a path does not exist, we will output that it does not.

## Timeline

4/9 submit contract and proposal

4/15 makefile and initial project set up

4/19-23 mid project check-in, try to accomplish one of the goals from 4/23 by check-in

4/23 build graph and traversal and test those

4/30 implement dijikstra and test dijikstra

5/7 implement all paths algorithim and test

5/12 fix any remaining bugs, make report, and submit
