//ALGORITHM

input: adjList[], s, t

//create new graphs in adjacency list representations
adjacencyListRed[adjList.size()] //stores u→v RED
adjacencyListBlue[adjList.size()]] //stores u→v BLUE

for(u = 0; u < adjList.size(); u++) {
	for(v = 0; v < adjList.size(); v++) {
		if((isPath(adjList,u,v) && ((u,v) == RED))
			adjacencyListRed[u].append(v)
		if((isPath(adjList,u,v) && ((u,v) == BLUE))
			adjacencyListBlue[u].append(v)

//case 1: in case the shortest path is all red edges
if((!adjacencyListRed[s].isEmpty()) && (isPath(adjacencyListRed,s,t)))
List1 = P(s,t, adjacencyListRed[])

//case 2: in case the shortest path is all blue edges
if((!adjacencyListBlue[s].isEmpty()) && (isPath(adjacencyListBlue,s,t)))
List2 = P(s,t, adjacencyListBlue[])

//case 3: in case the shortest separable path has a number of red edges then a number of blue edges
if(****condition to test if a vertex has RED incoming and BLUE outgoing****)
	X = temp connecting vertex
	tempList1 = P(s,x, adjacencyListRed[])
	tempList2 = P(x,t, adjacencyListBlue[])
	List3 = tempList1.append(x).append(tempList2)
