#include <iostream>
#include "Kruskal.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv){
	if(argc <= 3){
		cout << "Usage: <FILE_PATH> <CUT_COUNT> <OUTPUT_DIR>" << endl;
		return -1;
	}
	string file_name = argv[1];
	ifstream file(file_name);
	if (!file.is_open()){
		cout << file_name << " file couldn't open!" << endl;
		return -1;
	}
	char c;
	int header_size = 4;
	string buffer;
	int rowNum, colNum;
	// Pass header
	for(int i = 0; i < header_size; ){
		file.get(c);
		buffer += c;
		if(c == ' ' || c == '\n'){
			if(i == 1){
				colNum = stoi(buffer);
			}else if( i == 2){
				rowNum = stoi(buffer);
			}
			buffer = "";
			i++;
		}
	}
	Graph g(rowNum, colNum);
	cout << "r: " << rowNum << ", c: " << colNum << endl;
	//Read nodes from file
	while(file.get(c)){
		if(c == ' '){
			g.addNode(stoi(buffer));
			buffer = "";
			continue;
		}else{
			buffer += c;
		}
	}
	file.close();
	// o-o-o    o-o-o
	// | |      | | |
	// o-o-o -> o-o-o
	// | |      | | |
	// o o o    o-o-o
	//Build edges
	for(int i = 0; i < rowNum - 1; i++ ){
		for(int j = 0; j < colNum - 1; j++){
			//Build edge with next column
			g.addEdge(g.getNode(i, j), g.getNode(i, j+1));
			if(i == rowNum -2){//Son satır -> i+1
				g.addEdge(g.getNode(i+1, j), g.getNode(i+1, j+1));
			}
			//Build edge with next row
			g.addEdge(g.getNode(i, j), g.getNode(i + 1, j));
			if(j == colNum - 2){//Son sütun-> j+1
				g.addEdge(g.getNode(i, j+1), g.getNode(i + 1, j+1));
			}
		}
	}
	Kruskal kruskal;
	kruskal.runKruskal(g);
	kruskal.cutEdges(stoi(argv[2]));
	//Output file
	ofstream outFile(string(argv[3]) +string(argv[2]) + "output.pgm");
	//RGB color density
	int colorDensity = 255;
	if(!outFile.is_open()){
		cout << "Error while write to file!" << endl;
	}
	//Output file header
	outFile << "P3 " << to_string(colNum) << " " << to_string(rowNum) << " " << to_string(colorDensity) << "\n";
	//Stores RGB value by group id
	unordered_map<int, int*> densityMap;
	int RGB[3], groupNum = 0, groupId, colCount = 1;
	// Could be useful to get different colors each run
	//srand(time(NULL));
	for(int i = 0; i < g.getSize(); i ++){
		groupId = kruskal.getGroupId(i);
		if(groupId == INDEPENDENT_SET || densityMap.find(groupId) == densityMap.end()){
			//Generate random RGB value for each node
			for(int j = 0; j < 3; j ++){
				// 0-255 -> % 256
				RGB[j] = rand() % (colorDensity + 1);
			}
			//Don't generate color if node is in independent set
			if(groupId != INDEPENDENT_SET)
				densityMap[groupId] = new int []{RGB[0], RGB[1], RGB[2]};

			outFile << RGB[0] << " " << RGB[1] << " " << RGB[2] << " " ;
			
			groupNum ++;
		}else{
			outFile << densityMap[groupId][0] << " " << densityMap[groupId][1] << " " << densityMap[groupId][2] << " " ;
		}
		//Reached to last column
		if(colCount++ == colNum){
			outFile << "\n";
			colCount = 1;
		}
	}
	cout << "Number of groups: " << groupNum << endl;
	outFile.close();
}
