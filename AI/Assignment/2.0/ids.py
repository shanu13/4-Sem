import itertools
from helper import *

reach_goal=False
#for counting total node expanded(duplicates possible)
clc=deque()

#check for k-0,1,2........
for k in itertools.count(start=0):
    clc+=cl
    #clear so that no duplicates in closed list from earlier k
    cl.clear()
    ol.append(initial_node)
    info.clear()
    info[initial_node]=(0,0,0,) 
    #check till open list becomes empty
    while len(ol)>0:
        n=ol.popleft()
        cl.append(n)
        print('\n')
        print(n)
        #if goal is found then exit expansion
        if n==goal_node:
            reach_goal=True
            break
        #if depth of node is k then don't generate its successor
        if info[n][0]==k:
            continue
        m=successor(n,ol,cl,info)
        print(*m,sep='  ',)
        ol=m+ol
    if reach_goal:
        break

generated_expanded(ol,clc)
print_path(cl,info)
