 
from collections import deque

	
class state(object):

	def __init__(self,missionaries,carnibals,boat):
		self.m = missionaries
		self.c = carnibals
		self.b = boat
		
			
	def successorFunction(self) :
		if self.b ==1:
			signal = -1
			direction = 'move boat from original to new'
		else :
		 signal = 1
		 direction = 'move boat from new to original'	

		for i in range (3) : # missionaries
			for j in range(3): #carnibals
				newState = state(self.m + signal*i, self.c + signal*j, self.b + signal*1)
				if i+j >=1 and i+j <=2 and newState.stateValidation():
					action = "took %d missionaries , %d carnibals %s ,%r" % (i,j,direction,newState)
					yield action,newState

	def stateValidation(self) : 
		if self.m <0 and self.c <0 and self.m >3 and self.c >3  or (self.b != 0 and self.b !=1 ):
			return False
		if self.c > self.m and self.m > 0 :
			return False
		if self.c < self.m  and self.m <3:
			return False

		return True

	def goalState(self) : 
		if self.c == 0 and self.m == 0 and self.b == 0:
			return True
		else:
			return False  

	def __repr__(self):
	  return "< State (%d, %d, %d) >" % (self.m, self.c, self.b)



class node(object):
	def __init__(self,State,parent,action,depth):
		self.State = State
		self.parent = parent
		self.action = action
		self.depth =  depth


	def stateExpansion(self):
		for (action,State) in self.State.successorFunction():
			newNode = node(State,self,action,self.depth +1)
			yield newNode


	def Solution(self):
		solution = []
		goalnode = self
		while goalnode.parent is not None:
			solution.append(goalnode.action)
			goalnode = goalnode.parent
		solution.reverse()
		return solution


def BFS(initialState):
    startNode = node(initialState,None,None,0)
    fringe = deque([startNode])
    numExpnasions = 0
    maxDepth = -1
    while True: 
	    if not fringe :
	    	print("%d expansions" %numExpnasions)
	    	return None

	    nextnode = fringe.popleft()
	    if nextnode.depth > maxDepth:
	    	maxDepth = nextnode.depth
	    	print("[depth = %d]" % (maxDepth))

	    if nextnode.State.goalState():
	    	print("%d expansions " % (numExpnasions))
	    	solution = nextnode.Solution()
	    	return solution
	    numExpnasions+=1
	    fringe.extend(nextnode.stateExpansion())



def DFS(initialState):
	startNode = node(initialState,None,None,0);
	fringe - deque([startNode]);
	numExpnasions = 0;
	maxDepth = -1;

	while True:
		if not fringe:
			print("%d expansions" %numExpnasions);
		nextnode = fringe.popleft()

		if(nextnode.State.goalState()):
			print("%d total expansions" %numExpnasions);
			solution = nextnode.Solution()
			return solution
		


	

def main():
	initialState = state(3,3,1)
	solution = BFS(initialState)
	if solution is None :
		print("No Solution")
	else:
		print("solution (%d steps )" %(len(solution)))
		for step in solution:
			print("%s " % step)



if __name__ == "__main__":
	main()
