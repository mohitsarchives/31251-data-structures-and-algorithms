#ifndef GRAPH_ALGS
#define GRAPH_ALGS

#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <algorithm>
#include "weighted_graph.hpp"
#include <limits>
#include "easy_weighted_graph_algorithms.cpp"

//Returns true if the graph is connected, false otherwise.
template <typename vertex>
bool is_connected(const weighted_graph<vertex>& g)
{
	std::vector<vertex> vertexFinal;  			//initialize a vector of vertices
	if(g.num_vertices()==0)						// checking if number of vertices in graph g = 0
	{
		return true;
	}
	else
	{
		vertexFinal = depth_first(g, *(g.begin())); 		//perform a depth first search on the vector of vertices
		return(vertexFinal.size() == g.num_vertices());		//return a boolean value of whether the vector of vertices size
	}														//is equal to the number of vertices in the graph
}

//Returns a vector of weighted graphs, where each weighted graph is a connected
//component of the input graph.
template <typename vertex>
std::vector<weighted_graph<vertex>> connected_components(const weighted_graph<vertex>& g)
{

	std::unordered_set<vertex> unorderedSet_vertex;		//creating an unordered set of type vertex
	std::vector<weighted_graph<vertex>> final_graph;	//creating a vector of weighted graphs
	if(g.num_vertices()==0)								// checking if number of vertices in graph g = 0
	{
		return std::vector<weighted_graph<vertex>>();
	}
		else
		{	
			for(auto itr = g.begin(); itr!=g.end(); itr++) 	//iterating over the graph g 
			{
				unorderedSet_vertex.insert(*itr);		//insert the value at that point in the iterator into an unordered set of type vertex
			}
			while(!unorderedSet_vertex.empty())			//checking if the unordered set is not empty
			{
				vertex v;
				weighted_graph<vertex> new_graph;
				std::vector<vertex> depth_result;
				
				v = *unorderedSet_vertex.begin();		//vertex copying value of first element in the unordered set
				unorderedSet_vertex.erase(v);			//erase that vertex from the unordered set
				depth_result = depth_first(g, v);		//copying the result of the depth first result into the above initialized variable
				
			for(auto itr = depth_result.begin(); itr!=depth_result.end(); itr++)	//iterating over the depth first search result
			{
				new_graph.add_vertex(*itr);							//add the vertex at that point to the created graph
				unorderedSet_vertex.erase(*itr);					//now erase that vertex from the unordered set
			}
			for(auto vertex_itr = depth_result.begin(); vertex_itr!=depth_result.end(); vertex_itr++)	//iterating through the depth search result
			{
				for(auto itr = g.neighbours_begin(*vertex_itr); itr!=g.neighbours_end(*vertex_itr); itr++)	//iterating through the neighbour of the vertex at the iterator in the graph
				{
					int i;
					i = g.get_edge_weight(*vertex_itr, itr->first);			//get edge weight between the two vertices in the graph 
					new_graph.add_edge(*vertex_itr, itr->first, i);			//add edge to the new graph
				}
			}
			final_graph.push_back(new_graph);				//add the temporary graph into the final resultant graph
		}
		return final_graph;									//return the final resultant graph
	}
}

//Returns a map of the vertices of the weighted graph g and their distances from
//the given starting vertex v.
template <typename vertex> 
std::map<vertex, int> dijkstras(const weighted_graph<vertex>& g, const vertex& v)
{
	std::map<vertex, int> dijkstra_map;					//create a map for tracing dijkstra algorithm progress
	std::unordered_set<vertex> dijkstra_visited;		//create an ordered set of visited vertices
	std::vector<vertex> dijkstra_unvisited;				
		if(g.num_vertices()>0)
		{
			for(auto itr = g.begin(); itr!=g.end(); itr++)		//runs an iterator through the graph g
			{
				dijkstra_unvisited.push_back(*itr);					//pushes back the vertex at that point in the iterator into the unvisited vertex list
				dijkstra_map.insert(std::make_pair(*itr, std::numeric_limits<int>::max()));		//add the vertex and set the limits of the vertex to infinity (max)
			}
			vertex source_vertex = v;
			dijkstra_map.at(source_vertex) = 0;
			vertex this_vertex = source_vertex;
			while(dijkstra_visited.size() != dijkstra_unvisited.size())		//condition while size of the list of visited vertices is not equal to the size of the list of unvisited vertices
			{
				dijkstra_visited.insert(this_vertex);
				int min = std::numeric_limits<int>::max();					//storing infinity as limits into a new variable called min
				for(auto itr = g.neighbours_begin(this_vertex); itr!=g.neighbours_end(this_vertex); itr++)	//running an iterator through the graph g
				{
					if(dijkstra_visited.count(itr->first) == 0)
					{
						int initial_dist, new_dist;
						new_dist = dijkstra_map.at(this_vertex) + itr->second; 
						initial_dist = dijkstra_map.at(itr->first);
						if(new_dist < initial_dist)
						{
							dijkstra_map.at(itr->first) = new_dist;
						}
					}
				}
				for(auto itr1 = dijkstra_unvisited.begin(); itr1 != dijkstra_unvisited.end(); itr1++)		//running an iterator through the unvisited list of vertices
				{
					if(dijkstra_visited.count(*itr1) == 0)
					{
						if(dijkstra_map.at(*itr1) < min)
						{
							min = dijkstra_map.at(*itr1);
							this_vertex = *itr1;
						}
					}
				}
			}
			return dijkstra_map;				//returns the map implemented and used for tracking the dijkstra algorithm
		}
	
		else
		{
			return std::map<vertex, int>();		//returns an empty map 
		}
}

//Returns a vector containing all the articulation points of the
//input weighted graph g.
template <typename vertex>
std::vector<vertex> articulation_points(const weighted_graph<vertex>& g){
		std::unordered_set<vertex> unvisited_vertices;		//creating an unordered set of vertices for unvisited vertices
		std::unordered_set<vertex> visited_vertices;		//creating an unordered set of vertices for visited vertices
		std::vector<vertex> articulating_vertices;			//creating a vector of vertices for articulation points
		weighted_graph<vertex> new_graph = g;
		int numVertices = new_graph.num_vertices();
		for(auto itr = g.begin(); itr!=g.end(); itr++)		//iterating over the graph g
		{
			unvisited_vertices.insert(*itr);
		}
		if(g.num_vertices()==0)								//checking if the number of vertices in the graph g is 0
		{
			return std::vector<vertex>();					//returning an empty vector of vertices
		}
		else
		{
			for(auto vertex_iterator = unvisited_vertices.begin(); vertex_iterator!= unvisited_vertices.end(); vertex_iterator++)	//running an iterator through the unvisited list of vertices
			{
				if( visited_vertices.count(*vertex_iterator)==0)	//check to see if the vertex exists in the list of visited vertices
				{
					vertex temp_vertex;
					temp_vertex = *vertex_iterator;
					
					new_graph.remove_vertex(temp_vertex);			//remove vertex from the graph
					 visited_vertices.insert(temp_vertex);			//insert the vertex into the list of visited vertices
					numVertices--;									//decrement count of number of vertices
				
				for(auto remove_edge_itr = g.neighbours_begin(temp_vertex); remove_edge_itr!=g.neighbours_end(temp_vertex); remove_edge_itr++) //run an iterator through the neighbours of the vertex in the graph g
				{
					new_graph.remove_edge(temp_vertex, remove_edge_itr->first);	//removes edge from the graph
				}
					std::vector<vertex> temp_vector2;
					temp_vector2 = depth_first(new_graph, *new_graph.begin());	//performs a depth first search on the graph and stores it into a temporary vector of vertices
				if(temp_vector2.size() < numVertices)
				{
					articulating_vertices.push_back(temp_vertex);				//pushes the vertex into the articulating vertices if size of the vertex list is lesser than number of vertices
				}
					new_graph.add_vertex(temp_vertex);							//add vertex into the graph
					for(auto add_edge_itr = g.neighbours_begin(temp_vertex); add_edge_itr!=g.neighbours_end(temp_vertex); add_edge_itr++)	//run an iterator through the graph g for the purpose of adding an edge
					{
						int i;
						i = g.get_edge_weight(temp_vertex, add_edge_itr->first);	//get the edge weight
						new_graph.add_edge(temp_vertex, add_edge_itr->first, i);	//add edge between the two vertices and pass the weight obtained from getting edge weight prior to performing the operation
					}
					numVertices++;
					}
		}
			return articulating_vertices;				//return final result of articulating vertices
	}
}

#endif