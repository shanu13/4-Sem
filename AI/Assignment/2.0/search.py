from collections import deque

initialNode = (3,3,1)
goalNode = (0,0,0)

openList = deque()
closedList = deque()

solution = {}



def isValid(node):
	if node[0] <0 or node[0]>3 or node[1]<0 or node[1]>3:
		return False
	if (node[0]<node[1] and node[0]!=0) or (3-node[0]<3-node[1] and 3-node[0]!=0):
		return False
	return True

def inList(node, List):
	for isnode in List:
		if node == isnode:
			return True;
	return False



def succesorFunction(node,openlist,closedList,solution):
	nextNodes = deque()
	nextStates = ((1,0),(0,1),(1,1),(2,0),(0,2))
	for state in nextStates:
		if node[2] ==1 :
			nextNodes.append((node[0]-state[0],node[1]-state[1],0))
		else:
			nextNodes.append((node[0]+state[0],node[1]+state[1],1))

		nextnode = nextNodes.pop();

		if isValid(nextnode) and inList(nextnode,openList+closedList) ==False:
			nextNodes.append(nextnode)
			solution[nextnode] = (int(solution[node][0] +1), int(10*state[0]+20*state[1]), int(solution[node][2])+10*state[0]+20*state[1],node)


	return nextNodes;


def Counting(openList,closedList):
	print("\n Nodes Expanded = " + str(len(closedList)));
	print("\n Nodes Generated = " + str(len(openList) + len(closedList)));


def generatePath(closedList,solution):
	gnode = goalNode
	path = deque()
	for node in reversed(closedList):
		if solution[gnode][3] == node:
			path.append(solution[gnode])
			gnode = node
	print("\n")
	for node in reversed(path):
		print(str(node[3]) + "----> + ",end='');
	print(goalNode)



def BFS():

	while len(openList)>0:
		node = openList.popleft()
		closedList.append(node)
		print(node)
		if node == goalNode:
			print("Success");
			break;
		succesorNode = succesorFunction(node,openList,closedList,solution)
		print(*succesorNode,"  ")
		openList.extend(succesorNode)
	Counting(openList,closedList)
	generatePath(closedList,solution);
	

def DFS():
	while len(openList)>0 :
		node = openList.popleft()
		closedList.append(node);
		print(node);

		if node == goalNode:
			print("Sucess");
			break;
		nextnodes = succesorFunction(node,openList,closedList,solution);
		print(*nextnodes,sep=" ")
		openList.extendleft(nextnodes);

		

	Counting(openList,closedList);
	generatePath(closedList,solution) 

def IterativeDeeping():
	


def main():
	openList.append(initialNode);
	solution[initialNode] = (0,0,0)
	# BFS();
	DFS()



if __name__ == '__main__':
	main()





