#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
using namespace std;
class Node{
public:
	Node(){ }
	Node(int w){
		this->w = w;
	}
	Node(int w, int id){
		this->w = w;
		this->id = id;
	}
	int getW(){
		return w;
	}
	int getId(){
		return id;
	}
private:
	int w, id;
};
class Edge{
public:
	Edge(Node& u, Node& v){
		this->u = u;
		this->v = v;
		this->w = calculateW();
	}
	void setV(Node& v){
		this->v = v;
		this->w = calculateW();
	}
	Node& getU(){
		return u;
	}
	Node& getV(){
		return v;
	}
	int getW(){
		return w;
	}
	bool operator < (Edge& e){
		return this->getW() < e.getW();
	}
	bool operator > (Edge& e){
		return this->getW() > e.getW();
	}
	friend ostream& operator<< (ostream& out, Edge& e){
		out << "{ u: " << e.getU().getId() << ", v: " << e.getV().getId() << ", w: " << e.getW() << " }";
		return out;
	}

private:
	Node u, v;
	int w;
	//To calculate absolute weight
	int calculateW(){
		if(u.getW() > v.getW())
			return u.getW() - v.getW();
		else
			return  v.getW() - u.getW();

	}
};
class Graph{
public:
	Graph(){}
	Graph(int row, int col){
		this->row = row;
		this->col = col;
	}
	void addNode(int w){
		Node n(w,nodes.size());
		nodes.push_back(n);
	}
	void addEdge(Node& u, Node &v){
		Edge e(u,v);
		edges.push_back(e);
	}
	Node& getNode(int r, int c){
		return nodes[convertDimension(r,c)];
	}
	Node& getNode(int i){
		return nodes[i];
	}
	vector<Edge>& getEdges(){
		return edges;
	}
	vector<Node>& getNodes(){
		return nodes;
	}
	int getSize(){
		return nodes.size();
	}
	int getEdgeSize(){
		return edges.size();
	}
private:
	int row, col;
	vector<Node> nodes;
	vector<Edge> edges;
	int convertDimension(int r, int c){
		return r * col + c;
	}
};
#endif
