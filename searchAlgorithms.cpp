#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

enum {
  DFS = 1,
  BFS,
  KRUSKAL,
  PRIMA,
  BELLMAN_FORD,
  Floyd_Warshall,
  Ford_Falkerson,
  END = 11
};

int depthFirstSearch (const size_t numberOfMatrixSize, size_t node) {
  int matrix[numberOfMatrixSize][numberOfMatrixSize];

  std::cout << "Please, enter a matrix for your graph " << std::endl;
  for (size_t firstIndex = 0; firstIndex < numberOfMatrixSize; ++firstIndex) {
    for (size_t secondIndex = 0; secondIndex < numberOfMatrixSize; ++secondIndex) {
      std::cin >> matrix[firstIndex][secondIndex];
    }
  }

  std::stack<int> searchPlan;
  searchPlan.push(--node);

  matrix[node][node] = 1;
  int counter = 1;

  while (!searchPlan.empty()) {
    node = searchPlan.top();
    searchPlan.pop();
    for (size_t index = 0; index < numberOfMatrixSize; ++index) {
      if (matrix[node][index] && !matrix[index][index]) {
        searchPlan.push(index);
        matrix[index][index] = 1;
        ++counter;
      }
    }
  }

  return counter;
}

int breadthFirstSearch(const size_t numberOfMatrixSize, size_t node) {
  int matrix[numberOfMatrixSize][numberOfMatrixSize];

  std::cout << "Please, enter a matrix for your graph " << std::endl;
  for (size_t firstIndex = 0; firstIndex < numberOfMatrixSize; ++firstIndex) {
    for(size_t secondIndex = 0; secondIndex < numberOfMatrixSize; ++secondIndex) {
      std::cin >> matrix[firstIndex][secondIndex];
    }
  }

  std::queue<int> searchPlan;
  searchPlan.push(--node);

  matrix[node][node] = 1;
  int counter = 1;

  while(!searchPlan.empty()) {
    node = searchPlan.front();
    searchPlan.pop();

    for (size_t index = 0; index < numberOfMatrixSize; ++index) {
      if (matrix[node][index] && !matrix[index][index]) {
        searchPlan.push(index);
        matrix[index][index] = 1;
        ++counter;
      }
    }
  }

  return counter;
}

struct edge {
  int x, y; 

  edge() {

  }

  edge (int firstArgument, int secondArgument) {
    x = firstArgument;
    y = secondArgument;
  }
};

void KruskalAlgorithm (size_t n, size_t m) {
  std::vector<edge> graphEdge (m);
  std::vector<edge> treeEdge;
  std::vector<int>  numberOfNodes (n);

  for (size_t index = 0; index < n; ++index) {
    numberOfNodes[index] = index;
  }

  for (size_t index = 0; index < m; ++index) {
    int a = 0;
    int b = 0;
    
    std::cout << "Please, enter two nodes that will be merged by edges" << std::endl;
    std::cin >> a >> b;

    graphEdge[index].x = a;
    graphEdge[index].y = b;
  }

  for (size_t index = 0; index < m; ++index) {
    int a = graphEdge[index].x;
    int b = graphEdge[index].y;

    if (numberOfNodes[a] != numberOfNodes[b]) {
      treeEdge.push_back(graphEdge[index]);
      int oldNumberOfNodes = numberOfNodes[b];
      int newNumberOfNodes = numberOfNodes[a];

      for (size_t someNewIndex = 0; someNewIndex < n; ++someNewIndex) {
        if (numberOfNodes[someNewIndex] == oldNumberOfNodes) {
          numberOfNodes[someNewIndex] = newNumberOfNodes;
        }
      }
    }
  }

  for (size_t index = 0; index < n - 1; ++index) {
    std::cout << treeEdge[index].x << " " << treeEdge[index].y;

    if (index != n - 2) {
      std::cout << std::endl;
    }
  }

  std::cout << std::endl;
}

void PrimaAlgorithm (int numberOfNodes, const int INFINITY = 1e7) {
  std::vector<bool> used (numberOfNodes);
  std::vector<int> min_element (numberOfNodes, INFINITY);
  std::vector<int> sel_element (numberOfNodes, -1);

  int matrix[numberOfNodes][numberOfNodes];

  std::cout << "Please, enter your matrix for your graph " << std::endl;
  for (int firstIndex = 0; firstIndex < numberOfNodes; ++firstIndex) {
    for (int secondIndex = 0; secondIndex < numberOfNodes; ++secondIndex) {
      std::cin >> matrix[firstIndex][secondIndex];
    }
  }

  min_element[0] = 0;
  
  for (int i = 0; i < numberOfNodes; ++i) {
	  int v = -1;

	  for (int j = 0; j < numberOfNodes; ++j) {
		  if (!used[j] && (v == -1 || min_element[j] < min_element[v])) {
			v = j;
      }
    }

	  if (min_element[v] == INFINITY) {
		  std::cout << "No MST!";
		  exit(0);
	  }
 
	  used[v] = true;

	  if (sel_element[v] != -1) {
		  std::cout << v << " " << sel_element[v] << std::endl;
    }

	  for (int to = 0; to < numberOfNodes; ++to) {
		  if (matrix[v][to] < min_element[to]) {
			  min_element[to] = matrix[v][to];
			  sel_element[to] = v;
		  }
    }
  }
}

struct secondEdge {
  size_t from;
  size_t to;
  int cost;
};

void Bellman_Ford_Algorithm(size_t numberOfNodes, const int INFINITY = 1e7) {
  std::vector<secondEdge> edgesVector;
  for (size_t firstIndex = 0; firstIndex < numberOfNodes; ++firstIndex) {
    for (size_t secondIndex = 0; secondIndex < numberOfNodes; ++secondIndex) {
      int edgeCost = 0;

      std::cout << "Please enter the cost of " << firstIndex << "->" << secondIndex << "edge" <<std::endl;
      std::cin >> edgeCost;

      if (edgeCost != 0 && edgeCost != 100000) {
        edgesVector.push_back({firstIndex, secondIndex, edgeCost});
      }
    }
  }

  int x ;
  std::vector<int> someVector(numberOfNodes, INFINITY);
  std::vector<int> newVector(numberOfNodes, -1);

  someVector[0] = 0;

  for(size_t firstIndex = 0; firstIndex < numberOfNodes; ++firstIndex){
    x = -1;
    for(size_t secondIndex = 0; secondIndex < edgesVector.size(); ++secondIndex){
      int from = edgesVector[secondIndex].from;
      int to = edgesVector[secondIndex].to;
      int cost = edgesVector[secondIndex].cost;

      if(someVector[to] > someVector[from] + cost ){
        someVector[to] = std::max(someVector[from] + cost, -INFINITY);
        newVector[to] = from;
        x = to;
      }
    }
  }
  if(x == -1){
    std::cout << "FALSE" << std::endl;
  }else{
    int y = x;

    for(size_t counter = 0; counter < numberOfNodes; ++counter){
      y = newVector[y];
    }

    std::vector<int> path;
    for(int cur = y;; cur = newVector[cur]){
      path.push_back(cur);
      if(cur == y && path.size() > 1){
        break;
      }
    }

    std::reverse(path.begin(), path.end());
    std::cout << "TRUE" << std::endl;

    // If you want more detailed info about this graph uncomment code bellow 
    /*std::cout << path.size() << std::endl;
    for(int index = 0; index < path.size(); ++index){
      std::cout << path[index] + 1;
      if(index != path.size()-1){
          std::cout << ' ';
      }
    }*/

    std::cout << std::endl;
  }
}

void Floyd_Warshall_Algorithm(size_t numberOfNodes) {
  int a[numberOfNodes][numberOfNodes];
  long long maxRange = 0;

  std::cout << "Enter matrix for a graph" << std::endl;
  for(size_t firstIndex = 0 ; firstIndex < numberOfNodes; ++firstIndex) {
    for(size_t secondIndex = 0; secondIndex < numberOfNodes; ++secondIndex) {
      std::cin >> a[firstIndex][secondIndex];
    }
  }

  for(size_t firstIndex = 0; firstIndex < numberOfNodes; ++firstIndex) {
    for(size_t secondIndex = 0; secondIndex < numberOfNodes; ++secondIndex) {
      for(size_t thirdIndex = 0; thirdIndex < numberOfNodes; ++thirdIndex){
        if(secondIndex != thirdIndex && a[secondIndex][firstIndex] != -1 && a[firstIndex][thirdIndex] != -1){
          if(a[secondIndex][thirdIndex] == -1){
            a[secondIndex][thirdIndex] = a[secondIndex][firstIndex] + a[firstIndex][thirdIndex];
          } else {
            a[secondIndex][thirdIndex] = std::min(a[secondIndex][thirdIndex], a[secondIndex][firstIndex] + a[firstIndex][thirdIndex]);
          }
        }
      }
    }
  }
  for(size_t firstIndex = 0; firstIndex < numberOfNodes; ++firstIndex) {
    for(size_t secondIndex = 0; secondIndex < numberOfNodes; ++secondIndex) {
      if(a[firstIndex][secondIndex] > maxRange) {
        maxRange = a[firstIndex][secondIndex];
      }
    }
  }
  std::cout << maxRange << std::endl;
}

const int MAX_E = (int) 1e6;
const int MAX_V = (int) 1e3;
const int INF   = (int) 1e9;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E], edgeCount;
int firstEdge[MAX_V], visited[MAX_V];

void addEdge(int u, int v, int cap) {
  onEnd[edgeCount] = v;                   
  nextEdge[edgeCount] = firstEdge[u];     
  firstEdge[u] = edgeCount;               
  capacity[edgeCount++] = cap;            
  onEnd[edgeCount] = u;                   
  nextEdge[edgeCount] = firstEdge[v];     
  firstEdge[v] = edgeCount;               
  capacity[edgeCount++] = 0;              
}

int findFlow(int u, int flow) {
  if (u == destinationVertex) return flow; 
  visited[u] = true;
  for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
    int to = onEnd[edge];
    if (!visited[to] && capacity[edge] > 0) {
      int minResult = findFlow(to, std::min(flow, capacity[edge])); 
      if (minResult > 0) {                    
        capacity[edge]      -= minResult;   
        capacity[edge ^ 1]  += minResult;   
        return minResult;
      }
    }
  }
  return 0; 
}

void Ford_Falkerson_Algorithm () {
  std::fill(firstEdge, firstEdge + MAX_V, -1);     
  std::cin >> numOfVertex >> numOfEdge;            
  std::cin >> sourceVertex >> destinationVertex;   
  for (int i = 0, u, v, cap; i < numOfEdge; i++) {
    std::cin >> u >> v >> cap;
    addEdge(u, v, cap);
  }

  int maxFlow = 0;
  int iterationResult = 0;
  while ((iterationResult = findFlow(sourceVertex, INF)) > 0) {
    std::fill(visited, visited + MAX_V, false);
    maxFlow += iterationResult;
  }

  std::cout << maxFlow << std::endl;
}

void menu() {
  std::cout << "(c) Made by JayTadDy(Sviatoslav Trenchuk)" << std::endl 
            << "Choose what algorithm you want to use :" << std::endl
            << "1) DFS" << std::endl
            << "2) BFS" << std::endl
            << "3) Kruskal's algorithm" << std::endl
            << "4) Prima's algorithm" << std::endl
            << "5) Bellman and Ford's algorithm" << std::endl
            << "6) Floyd and Warshall's algorithm" << std::endl
            << "7) Ford and Flarkenson's algorithm" << std::endl;
}

int main(int argc, const char *argv[]) {
  menu();

  size_t choise;

  while (choise != END) {
    std::cin >> choise;

    switch (choise) {
    {
    case DFS:
      size_t matrixSize = 0;
      size_t node = 0;

      std::cout << "Please enter matrix size and node you want to search" << std::endl;
      std::cin >> matrixSize >> node;
      
      int result = depthFirstSearch(matrixSize, node);

      std::cout << "The result is : " << result << std::endl << "Thank you for using this programm =) " << std::endl;

      break;
    }
    {
    case BFS:
      size_t matrixSize = 0;
      size_t node = 0;
      
      std::cout << "Please enter matrix size and node you want to search" << std::endl;
      std::cin >> matrixSize >> node;

      int result = breadthFirstSearch(matrixSize, node);

      std::cout << "The result is : " << result << std::endl << "Thank you for using this programm =) " << std::endl;

      break;
    }
    {
    case KRUSKAL:
      size_t numberOfEdges = 0;
      size_t numberOfNodes = 0;

      std::cin >> numberOfNodes >> numberOfEdges;

      KruskalAlgorithm(numberOfNodes, numberOfEdges);
    }
    {
    case PRIMA :
      int numberOfNodes = 0;
      
      std::cout << "Please, enter the number of the nodes " << std::endl;
      std::cin >> numberOfNodes;

      PrimaAlgorithm(numberOfNodes);

      break;  
    }
    {
    case BELLMAN_FORD:
      int numberofNodes = 0;

      std::cout << "Please, enter the number of the nodes " << std::endl;
      std::cin >> numberofNodes;

      Bellman_Ford_Algorithm(numberofNodes);

      break;
    }
    {
    case Floyd_Warshall:
      size_t numberOfNodes = 0;

      std::cout << "Please, enter the number of the nodes " << std::endl;
      std::cin >> numberOfNodes;

      Floyd_Warshall_Algorithm(numberOfNodes); 

      break;  
    }
    {
    case Ford_Falkerson:
      Ford_Falkerson_Algorithm();
      break;  
    }
    default:
      std::cout << "You have entered a wrong number " << std::endl;
      break;
    }
  }
  return 0;
}