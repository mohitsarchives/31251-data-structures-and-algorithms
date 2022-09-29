#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

//A large selection of data structures from the standard
//library. You need not feel compelled to use them all,
//but as you can't add any, they're all here just in case.
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <map>

template <typename vertex>
class weighted_graph {

	private:
	
	int totalWeight = 0; //stores the total weight of all the edges in the graph.
	int vertexCounter = 0; //counter to keep track of the number of vertices in the graph.
	int numberOfEdges = 0; //counter to keep track of the number of edges in the graph.
	std::vector<vertex> vertices; //this is a vector of vertices which holds the list of vertices.
	std::vector<std::vector<int>> adjacency_matrix; //this is a vector of vector of vertices that holds vertices and contains 
													//information about the edges.
	
	//You will need to add some data members here
	//to actually represent the graph internally,
	//and keep track of whatever you need to.
	
	//The graph_iterator class provides an iterator
	//over the vertices of the graph.
	//This is one of the harder parts, so if you're
	//not too comfortable with C++ leave this for last.
	//If you are, there are many ways of doing this,
	//as long as it passes the tests, it's okay.
	
	class graph_iterator {
		
		private:
		
		weighted_graph<vertex> graph_iter;
		int pos;
		
		//You may need data members here.
				
		public:
			graph_iterator(const weighted_graph &);
			graph_iterator(const weighted_graph &, size_t);
			~graph_iterator();
			graph_iterator operator=(const graph_iterator&);
			bool operator==(const graph_iterator&) const;
			bool operator!=(const graph_iterator&) const;
			graph_iterator operator++();
			graph_iterator operator++(int);
			const vertex operator*();
			const vertex* operator->();
	};
	
	//The neighbour_iterator class provides an iterator
	//over the neighbours of a given vertex. This is
	//probably harder (conceptually) than the graph_iterator.
	//Unless you know how iterators work.
	class neighbour_iterator {
			
		private:
		
		weighted_graph<vertex> neighbour_iter;
		vertex vert;
		size_t position;
		
		//You may need data members here.
				
		public:
			neighbour_iterator(const neighbour_iterator&);
			neighbour_iterator(const weighted_graph &, const vertex&);
			neighbour_iterator(const weighted_graph &, const vertex&, size_t);
			~neighbour_iterator();
			neighbour_iterator operator=(const neighbour_iterator& it);
			bool operator==(const neighbour_iterator&) const;
			bool operator!=(const neighbour_iterator&) const;
			neighbour_iterator operator++();
			neighbour_iterator operator++(int);			
			const std::pair<vertex, int> operator*();
			const std::pair<const vertex, int>* operator->();
	};
	
	public:
	
	
	weighted_graph(); //A constructor for weighted_graph. It should start empty.
	~weighted_graph(); //A destructor. Depending on how you do things, this may
					   //not be necessary.
	
	
	bool are_adjacent(const vertex&, const vertex&) const; //Returns true if the two vertices are
														   //adjacent, false otherwise.
	bool has_vertex(const vertex&) const; //Returns true if the passed in vertex is 
										  //a vertex of the graph, false otherwise.
	
	void add_vertex(const vertex&); //Adds the passed in vertex to the graph (with no edges).
	void add_edge(const vertex&, const vertex&, const int&); //Adds an edge between the two vertices
															 //with the given weight (as an int).
	
	void remove_vertex(const vertex&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const vertex&, const vertex&); //Removes the edge between the two vertices, if it exists.
	void set_edge_weight(const vertex&, const vertex&, const int&); //Changes the edge weight between the two
																	//vertices to the new weight (the int).
	
	int getIndex(const vertex&) const;
	int get_edge_weight(const vertex&, const vertex&) const; //Returns the weight on the edge between the two vertices.
	int degree(const vertex&) const; //Returns the degree of the vertex.
	int weighted_degree(const vertex&); //Returns the sum of the weights on all the edges incident to the vertex.
	int num_vertices() const; //Returns the total number of vertices in the graph.
	int num_edges() const; //Returns the total number of edges in the graph (just the count, not the weight).
	int total_weight(); //Returns the sum of all the edge weights in the graph.
	
	std::vector<vertex> get_vertices(); //Returns a vector containing all the vertices.
	std::vector<vertex> get_neighbours(const vertex&); //Returns a vector containing the neighbours of the given vertex.
	
	graph_iterator begin(); //Returns a graph_iterator pointing to the start of the vertex set.
	graph_iterator end(); //Returns a graph_iterator pointing to one-past-the-end of the vertex set.
	
	neighbour_iterator neighbours_begin(const vertex&); //Returns a neighbour_iterator pointing to the start
														//of the neighbour set for the given vertex.
	neighbour_iterator neighbours_end(const vertex&); //Returns a neighbour_iterator pointing to one-past-the-end
													  //of the neighbour set for the given vertex.

	std::vector<vertex> depth_first(const vertex&); //Returns the vertices of the graph in the order they
													//are visited in by a depth-first traversal starting at
													//the given vertex.
	std::vector<vertex> breadth_first(const vertex&); //Returns the vertices of the graph in the order they
													  //are visisted in by a breadth-first traversal starting
													  //at the given vertex.
	
	weighted_graph<vertex> mst(); //Returns a minimum spanning tree of the graph.
	
};

//Define all your methods down here (or move them up into the header, but be careful you don't double up).
//Although these are just the same names copied from above, you may find a few more clues in the full
//method headers. Note also that C++ is sensitive to the order you declare and define things in - you
//have to have it available before you use it.

template <typename vertex> weighted_graph<vertex>::graph_iterator::graph_iterator(const weighted_graph & g)
{
	graph_iter = g;
	pos = 0;
}
template <typename vertex> weighted_graph<vertex>::graph_iterator::graph_iterator(const weighted_graph & g, size_t start_pos)
{
	graph_iter=g;				//constructors to assign values to data members.
	pos = start_pos;
}
template <typename vertex> weighted_graph<vertex>::graph_iterator::~graph_iterator()
{
	
}
template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator=(const graph_iterator& it)
{ 
	auto g = graph_iterator(it, it.pos); 	//assigning the graph iterator and its position according to the constructor.
	return g; 
}
template <typename vertex> bool weighted_graph<vertex>::graph_iterator::operator==(const graph_iterator& it) const 
{ 
	return pos == it.pos;					//boolean statement that checks if the position is equal to the iterator's position.
}
template <typename vertex> bool weighted_graph<vertex>::graph_iterator::operator!=(const graph_iterator& it) const 
{ 
	return pos != it.pos; 					//boolean statement that checks if the position is not equal to the iterator's position.
}
template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator++()
{ 
	auto g = graph_iterator(graph_iter, ++pos); 		//increments the position of the graph iterator by 1. it is a pre-fix.
	return g; 
}
template <typename vertex> typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::graph_iterator::operator++(int)
{ 
	auto g = graph_iterator(graph_iter, pos++); 		//increments the position of the graph iterator by 1. it is a post-fix.
	return g; 
}
template <typename vertex> const vertex weighted_graph<vertex>::graph_iterator::operator*()
{ 
	auto v = graph_iter.vertices[pos]; 					//dereferences the iterator that acts as a pointer at position pos.
	return v; 
}
template <typename vertex> const vertex* weighted_graph<vertex>::graph_iterator::operator->()
{ 
	auto v = graph_iter.vertices[pos]; 					//dereferences the iterator that acts as a pointer at position pos.
	return v;
}

template <typename vertex> weighted_graph<vertex>::neighbour_iterator::neighbour_iterator(const weighted_graph & g, const vertex& u) 
{
	neighbour_iter = g;
	vert = u;
	position = 0;
}
template <typename vertex> weighted_graph<vertex>::neighbour_iterator::neighbour_iterator(const weighted_graph & g, const vertex& u, size_t start_pos) 
{
	neighbour_iter = g;
	vert = u;
	position = start_pos;
}
template <typename vertex> weighted_graph<vertex>::neighbour_iterator::~neighbour_iterator() 
{
	
}
template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator=(const neighbour_iterator& it) 
{ 
	auto n = neighbour_iterator(weighted_graph<vertex>(), vertex()); 
	return n; 
}
template <typename vertex> bool weighted_graph<vertex>::neighbour_iterator::operator==(const neighbour_iterator& it) const 
{ 
	return false; 
}
template <typename vertex> bool weighted_graph<vertex>::neighbour_iterator::operator!=(const neighbour_iterator& it) const 
{ 
	return false; 
}
template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator++() 
{ 
	auto n = neighbour_iterator(weighted_graph<vertex>(), vertex()); 
	return n; 
}
template <typename vertex> typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbour_iterator::operator++(int)
{ 
	auto n = neighbour_iterator(weighted_graph<vertex>(), vertex()); 
	return n; 
}			
template <typename vertex> const std::pair<vertex, int> weighted_graph<vertex>::neighbour_iterator::operator*()
{ 
	auto p = std::pair<vertex,int>(); 
	return p; 
}
template <typename vertex> const std::pair<const vertex, int>* weighted_graph<vertex>::neighbour_iterator::operator->()
{ 
	return nullptr; 
}

template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::begin() 
{
	return graph_iterator(*this);
}
template <typename vertex>	typename weighted_graph<vertex>::graph_iterator weighted_graph<vertex>::end() 
{
	return graph_iterator(*this, vertices.size());
}
	
template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_begin(const vertex& u) {
	return neighbour_iterator(*this, vertex());
}

template <typename vertex>	typename weighted_graph<vertex>::neighbour_iterator weighted_graph<vertex>::neighbours_end(const vertex& u) {
	return neighbour_iterator(weighted_graph<vertex>(), vertex());
}

template <typename vertex> weighted_graph<vertex>::weighted_graph(){

}

template <typename vertex> weighted_graph<vertex>::~weighted_graph(){
	
}

template <typename vertex> int weighted_graph<vertex>::getIndex(const vertex& u) const {
	for(int i = 0; i<vertices.size(); i++) //for-loop which is used to iterate over the vertex list.
	{
		if(vertices[i]==u) //if the vertex passed in as the parameter matches the vertex in the vertex list.
			return i;		//return the index of the vertex matched.
	}
}
template <typename vertex> bool weighted_graph<vertex>::has_vertex(const vertex& u) const {
	
	for(int i=0; i<vertices.size(); i++) //for-loop which is used to iterate over the vertex list.
	{
		if(vertices[i]==u)	//if the vertex passed in as the parameter matches the vertex in the vertex list at 
							//a given index index,
		return true;		//return true, else return false.
	}
	return false;
}
	
template <typename vertex> bool weighted_graph<vertex>::are_adjacent(const vertex& u, const vertex& v) const {
	if(has_vertex(u) && has_vertex(v)) //these are constraints to make sure that vertices entered are existent.
	{
		return adjacency_matrix[u][v];	//returns a non-zero value if the vertices are adjacent, else returns 0. 
	}
	return false;
}

template <typename vertex> void weighted_graph<vertex>::add_vertex(const vertex& v) {
			vertices.push_back(v); 		//this adds vertex v to the vector of vertices.
			vertexCounter++; 			// this increments the number of vertices in the graph by 1.
			adjacency_matrix.resize(vertexCounter);			//this resizes the adjacency matrix.
			for(int i = 0; i<vertices.size(); i++)			//for-loop which is used to iterate over the vertex list.
			{
				adjacency_matrix[i].resize(vertexCounter, 0);	//resizes the adjacency matrix in the iteration of the vertex list.
			}
}

template <typename vertex> void weighted_graph<vertex>::add_edge(const vertex& u, const vertex& v, const int& weight) 
{
	if(has_vertex(u) && has_vertex(v)) //these are constraints to make sure that vertices entered are existent.
	{
		if ((getIndex(u) >= 0) && (getIndex(u) < vertices.size()) && (getIndex(v) >= 0) && (getIndex(v) < vertices.size()) && (getIndex(u) != getIndex(v)))
			//the above statement are constraints to ensure that the vertices are within the scope of the adjacency matrix.
		{
			adjacency_matrix[getIndex(u)][getIndex(v)] = weight;		//this statement sets the edge of the given position in the matrix to the weight passed in the parameter.
			adjacency_matrix[getIndex(v)][getIndex(u)] = weight;	//same process repeated to work with undirected edges.
			numberOfEdges++;
			totalWeight += weight;
		}
	}
}
template <typename vertex> void weighted_graph<vertex>::remove_vertex(const vertex& u) 
{
		if(has_vertex(u)) //these are constraints to make sure that vertices entered are existent.
		{
	 		std::vector<int>::iterator it = vertices.begin();
			for(; it != vertices.end(); ) //iterator to iterate over vertex list.
			{
				if(*it==u)
				{
				vertices.erase(it);			//condition to check if element in the vertex list matches vertex passed in the parameter.
				vertexCounter--;			//decrement number of vertices in the graph.
				}
				else
					++it;
			}
		}
	for(int i=0; i<vertices.size(); i++)
	{
		adjacency_matrix[i].resize(vertexCounter); //resizing the adjacency matrix.
	}
}


template <typename vertex> void weighted_graph<vertex>::remove_edge(const vertex& u, const vertex& v) 
{
if(has_vertex(u) && has_vertex(v)) //these are constraints to make sure that vertices entered are existent.
	{
	if ((getIndex(u) >= 0) && (getIndex(u) < vertices.size()) && (getIndex(v) >= 0) && (getIndex(v) < vertices.size()) && (getIndex(u) != getIndex(v)))
	{
		adjacency_matrix[getIndex(u)][getIndex(v)] = 0;		//sets edgeweight to 0 since we are removing 0. nullifies the edge.
		adjacency_matrix[getIndex(v)][getIndex(u)] = 0;		// similar process since the edges are undirected.
			numberOfEdges--;
	}
	}
}

template <typename vertex> void weighted_graph<vertex>::set_edge_weight(const vertex& u, const vertex& v, const int& weight) {
	
	if(has_vertex(u) && has_vertex(v)) //these are constraints to make sure that vertices entered are existent.
	{
		adjacency_matrix[getIndex(u)][getIndex(v)] = weight; //sets the edges to the weight passed in the parameter.
		adjacency_matrix[getIndex(v)][getIndex(u)] = weight; //since it is an undirected edge, set the edge to the weight passed in the parameter.
	}
}

template <typename vertex> int weighted_graph<vertex>::get_edge_weight(const vertex& u, const vertex& v) const {
	
	if(has_vertex(u) && has_vertex(v)) //these are constraints to make sure that vertices entered are existent.
	{
		return adjacency_matrix[getIndex(u)][getIndex(v)];		//return the edge weight of the edge.
	}
}

template <typename vertex> int weighted_graph<vertex>::degree(const vertex& u) const {
	int degreeCounter = 0;
	if(has_vertex(u))
	{
		for(int i=0; i<vertices.size(); i++)
		{
			if(adjacency_matrix[getIndex(u)][i]!=false)		//if vertex has an edge connected to it
				++degreeCounter;							// increment the degree of the vertex.
		}
	}
	return degreeCounter;
}

template <typename vertex> int weighted_graph<vertex>::weighted_degree(const vertex& u) {
	int weightedDegree = 0;
	if(has_vertex(u))
	{
		for(int i = 0; i < vertices.size(); i++)
		{
			weightedDegree += adjacency_matrix[getIndex(u)][i];  // adds the weight of the edge to weightedDegree
		}
	}
	return weightedDegree;
}

template <typename vertex> int weighted_graph<vertex>::num_vertices() const {
	return vertexCounter; //returns number of vertices in the graph.
}

template <typename vertex> int weighted_graph<vertex>::num_edges() const {
	return numberOfEdges; //returns number of edges in the graph
}

template <typename vertex> int weighted_graph<vertex>::total_weight() {
	return totalWeight; //returns the total edge weight in the graph.
}
	
template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_vertices() {
	return vertices; //returns the vector of vertices in the graph.
}

template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_neighbours(const vertex& u) 
{
	std::vector<vertex> neighborsList;
	if(has_vertex(u)) //these are constraints to make sure that vertices entered are existent.
	{
		for(int i=0; i<vertices.size(); i++)
		{
			if(adjacency_matrix[getIndex(u)][i] != false)
			neighborsList.push_back(vertices[i]);
		}
	}
	return neighborsList;
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::depth_first(const vertex& start_vertex){
	if(has_vertex(start_vertex)) //these are constraints to make sure that vertices entered are existent.
	{
	bool visited[vertices.size()];
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		visited[i] = false;					//initially sets all the vertices condition (if they have been visited or not) to false.
	}
	
	std::stack<int> unprocessed;
	unprocessed.push(start_vertex); 		//pushes index of start vertex into the stack to begin the traversal.
	
	std::vector<int> ordered;
	
	while (!unprocessed.empty()){
		int n = unprocessed.top();
		unprocessed.pop();
		if (!visited[n]){
			visited[n] = true;
			ordered.push_back(n);			//push the vertex into the ordered list.
			for (unsigned i = vertices.size(); i != 0; i--){
				if (adjacency_matrix[n][i-1]){
					unprocessed.push(i-1);
				}
			}
		}
	}
		
	return ordered;					//returns the ordered list
	}
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::breadth_first(const vertex& start_vertex){
	
	if(has_vertex(start_vertex)) //these are constraints to make sure that vertices entered are existent.
	{
	bool visited[vertices.size()];
	for (unsigned i = 0; i < vertices.size(); i++)
	{
		visited[i] = false;				//sets vertices condition (if they have been visited or not) to false initially.
	}
	
	std::queue<int> unprocessed;			//queue is declared to visit different vertices that have not yet been visited in the graph.
	unprocessed.push(start_vertex);			//pushes vertex into the queue to begin the traversal.
	
	std::vector<int> ordered;
	
	while (!unprocessed.empty()){
		int n = unprocessed.front();	//accesses element at the front of the group.
		unprocessed.pop();				//this statement removes the first vertex from the queue.
		if (!visited[n]){
			visited[n] = true;
			ordered.push_back(n);
			for (unsigned i = 0; i < vertices.size(); i++){
				if (adjacency_matrix[n][i])
				{
					unprocessed.push(i);
				}
			}
			}
		}
				return ordered;			//returns the ordered list
	}
	
}

	
template <typename vertex>	weighted_graph<vertex> weighted_graph<vertex>::mst() {
	return weighted_graph<vertex>();
}


#endif