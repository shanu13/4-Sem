#find node with minimum g value in open list 
def min_in_ol(ol,info):
    mini=10000
    min_node=tuple
    for dict in info:
        for node in ol:
            if node==dict and mini>info[dict][2]:
                mini=info[dict][2]
                min_node=dict            
    return min_node

from helper import *

initialize(ol,info)

while len(ol)>0:
    #take n as minumum g valued node
    n=min_in_ol(ol,info)
    ol.remove(min_in_ol(ol,info))
    cl.append(n)
    print('\n')
    print(n)
    if n==goal_node:
        break
    m=successor_ucs(n,ol,cl,info)
    print(*m,sep='  ',)
    ##insert nodes which can be inserted order don't matter because we have to select minimum
    ol+=m

generated_expanded(ol,cl)
print_path(cl,info)