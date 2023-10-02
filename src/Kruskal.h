#ifndef KRUSKAL_H
#define  KRUSKAL_H
#include <iostream>
#include <algorithm>
#include "Graph.h"

#define INDEPENDENT_SET -1

using namespace std;

class Kruskal{
public:
	Kruskal(){}
	void runKruskal(Graph& graph){
		this->graph = graph;

		sortEdges(graph.getEdges());

		for (Node& n: graph.getNodes()){
			makeSet(n);
		}

		int vGId, uGId;
		for( Edge& e: graph.getEdges()){
			uGId = idToGroup[e.getU().getId()];
			vGId = idToGroup[e.getV().getId()];
			//If at least one of the nodes is in independent set or nodes are in different set
			if(vGId == INDEPENDENT_SET || uGId == INDEPENDENT_SET || uGId != vGId){
				MST.push_back(e);
				unionSet(e);
			}
		}
	}
	void cutEdges(int cutCount){
		int heaviest;
		vector<int>a;
		idToGroup =  a;
		for(int i = 0; i < cutCount && MST.size() != 0; i ++){
			heaviest = MST.back().getW();
			// Cut heaviest edges
			while(heaviest == MST.back().getW() && MST.size() != 0){
				MST.pop_back();
			}
		}

		for(Node& n: graph.getNodes()){
			makeSet(n);
		}
		int uGId, vGId;
		int i=0;
		for( Edge& e:MST){
			uGId = idToGroup[e.getU().getId()];
			vGId = idToGroup[e.getV().getId()];
			//If at least one of the nodes is in independent set or nodes are in different set
			if(vGId == INDEPENDENT_SET || uGId == INDEPENDENT_SET || uGId != vGId){
				unionSet(e);
			}
		}
	}
	int getGroupId(int nodeId){
		return idToGroup[nodeId];
	}
private:
	//Stores which node is in which set
	vector<vector<int>> groupTable;
	vector<int> idToGroup;
	vector<Edge> MST;
	Graph graph;

	void sortEdges(vector<Edge>& edges){
		sort(edges.begin(), edges.end());
	}
	//At first all nodes are in independent set
	void makeSet(Node& n){
		idToGroup.push_back(INDEPENDENT_SET);
	}
	void unionSet(Edge& e){
		int uGId = idToGroup[e.getU().getId()];
		int vGId = idToGroup[e.getV().getId()];
		if(uGId == INDEPENDENT_SET){
			if(vGId == INDEPENDENT_SET){
				//New set
				vector<int> inVec;
				inVec.push_back(e.getU().getId());
				inVec.push_back(e.getV().getId());
				groupTable.push_back(inVec);
				//New set id -> size -1
				idToGroup[e.getU().getId()]  = groupTable.size() -1;
				idToGroup[e.getV().getId()]  = groupTable.size() -1;
			}else{
				groupTable[vGId].push_back(e.getU().getId());
				idToGroup[e.getU().getId()] = vGId;
			}
		}else if(vGId == INDEPENDENT_SET){
			groupTable[uGId].push_back(e.getV().getId());
			idToGroup[e.getV().getId()] = uGId;
			//e.getV().setGroupId(uGId);
		}else{
			int uGroupSize = groupTable[uGId].size();
			int vGroupSize = groupTable[vGId].size();
			int id;
			// Move group with fewer nodes to other group
			if(uGroupSize < vGroupSize){
				for(int i = 0; i < uGroupSize; i++){
					id = groupTable[uGId].back();
					groupTable[vGId].push_back(id);
					groupTable[uGId].pop_back();
					//graph.getNode(id).setGroupId(vGId);
					idToGroup[id] = vGId;
				}
			}else{
				for(int i = 0; i < vGroupSize; i++){
					id = groupTable[vGId].back();
					groupTable[uGId].push_back(groupTable[vGId].back());
					groupTable[vGId].pop_back();
					//graph.getNode(id).setGroupId(uGId);
					idToGroup[id] = uGId;
				}
			}
		}
	}
};
#endif
