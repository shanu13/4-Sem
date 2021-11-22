from helper import *
 
initialize(ol,info)

while len(ol)>0:
    #remove a node from front
    n=ol.popleft()
    cl.append(n)
    print('\n')
    print(n)
    #if n is goal node then break
    if n==goal_node:
        break
    m=successor(n,ol,cl,info)
    print(*m,sep='  ',)
    #insert nodes which can be inserted to back
    ol+=m

generated_expanded(ol,cl)
print_path(cl,info)