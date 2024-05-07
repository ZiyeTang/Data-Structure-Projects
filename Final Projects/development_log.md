## Week 04/17 - 04/23
### Deserialization
James and Matt worked on deserialization with JSON. The original data is given in .csv format, so we used an online converter to convert into JSON, and then found an C++ library called `nlohmann/json` to read the file and parse it into graph verticies. This was all done in the deserialization branch, which was then merged with master at the end of the week.

#### Building graph class
* Created graph class with a struct for nodes and one for edges.
* Implemented functions to build graph edges from the data in the vertices/nodes.
