from collections import deque

#define initial,goal,open list,closed list,information
initial_node=(3,3,1)
goal_node=(0,0,0)
ol=deque()
cl=deque()
info={}

#check if there are not illegal states i.e. -1 or extra missionaries or cannibals
def is_good(node):
    if node[0]<0 or node[0]>3 or node[1]<0 or node[1]>3 :
        return False
    if (node[0]<node[1] and node[0]!=0) or (3-node[0]<3-node[1] and 3-node[0]!=0):
        return False
    return True

#check if a node is present in a particular list
def in_list(node,l):
    for node_present in l:
        if node==node_present:
            return True
    return False

def successor(n,ol,cl,info): 
    #to store all possible next states
    m=deque()
    next_states=((1, 0), (2, 0), (0, 1), (0, 2), (1, 1))

    for state in next_states:
        if n[2]==1:
            m.append((n[0]-state[0],n[1]-state[1],0))
        else:
            m.append((n[0]+state[0],n[1]+state[1],1))

        node=m.pop()
        #check if m is legal and not already in a list
        if is_good(node) and in_list(node,ol+cl)==False:
            m.append(node)
            info[node]=(int(info[n][0]+1),int(10*state[0]+20*state[1]),int(info[n][2])+10*state[0]+20*state[1],n)

    return m

def successor_ucs(n,ol,cl,info):
    m=deque()
    next_states=((1, 0), (2, 0), (0, 1), (0, 2), (1, 1))

    for state in next_states:
        if n[2]==1:
            m.append((n[0]-state[0],n[1]-state[1],0))
        else:
            m.append((n[0]+state[0],n[1]+state[1],1))

        node=m.pop()
        if is_good(node):
            #if list in open list check if g value is less and update
            if in_list(node,ol):
                if(info[n][2]+10*state[0]+20*state[1]<info[node][2]):
                    info[node]=(int(info[n][0]+1),int(10*state[0]+20*state[1]),int(info[n][2])+10*state[0]+20*state[1],n)
            #if list in closed list check if g value is less and move to open list
            elif in_list(node,cl):
                if(info[n][2]+10*state[0]+20*state[1]<info[node][2]):
                    cl.remove(node)
                    m.append(node)
                    info[node]=(int(info[n][0]+1),int(10*state[0]+20*state[1]),int(info[n][2])+10*state[0]+20*state[1],n)
            #if it is newly visited node then insert it
            else:
                m.append(node)
                info[node]=(int(info[n][0]+1),int(10*state[0]+20*state[1]),int(info[n][2])+10*state[0]+20*state[1],n)

    return m

def generated_expanded(ol,cl):
    print("\nNodes expanded : "+str(len(cl)))
    print("Nodes generated : "+str(len(ol)+len(cl)))

def print_path(cl,info):
    n=goal_node
    #make a path by visiting parent of each node
    path=deque()
    for node in reversed(cl):
        if info[n][3]==node:
            path.append(info[n])
            n=node

    print("\nPath:")
    for node in reversed(path):
        print(str(node[3])+' ---'+str(node[1])+'--->',end=' ')
    print(goal_node)
    print("Total cost : "+str(info[goal_node][2]))

def initialize(ol,info):
    ol.append(initial_node)
    info[initial_node]=(0,0,0,)        



