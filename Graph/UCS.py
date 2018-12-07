"""
    Requires PriorityQueue implementation.
    Problem is object of custom data structure, but it is easy to replace it with different data structure

    If you diff function definition with that of BFS, Only Queue is replaced by Priority Queue, and cost in handled in other places
"""

def UniformCostSearch(problem):
    frontierStack = util.PriorityQueue()
    path, visited = list(), set()
    currentNode = problem.getStartState()
    pathCost = 0
    from game import Directions
    while not problem.isGoalState(currentNode):
        if currentNode not in visited:
            visited.add(currentNode)
            for next, dirn, cost in problem.getSuccessors(currentNode):
                if next not in visited:
                    nextPath = path + [dirn]
                    nextCost = pathCost + cost
                    frontierStack.push((nextCost, next, nextPath), nextCost)

        if frontierStack.isEmpty():
           print('Faied to find path')
           return []   # Path Not found - failed to reach goal
        pathCost, currentNode, path = frontierStack.pop()

    return  path
