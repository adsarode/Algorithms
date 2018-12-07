"""
    Requires PriorityQueue implementation.
    Problem is object of custom data structure, but it is easy to replace it with different data structure

    If you diff function definition with that of UCS, Priority is changed from nextCost to nextCost + Heuristic cost
"""

def AStarSearch(problem):
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
                    priority = nextCost + heuristic(next, problem)
                    frontierStack.push((nextCost, next, nextPath), priority)

        if frontierStack.isEmpty():
           print('Faied to find path')
           return []   # Path Not found - failed to reach goal
        pathCost, currentNode, path = frontierStack.pop()

    return  path
