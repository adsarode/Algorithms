"""
    Requires Stack implementation which is very easy.
    Problem is object of custom data structure, but it is easy to replace it with different data structure
"""

def DepthFirstSearch(problem):
    frontierStack = util.Stack()
    path, visited = list(), set()
    currentNode = problem.getStartState()
    from game import Directions
    while not problem.isGoalState(currentNode):
        if currentNode not in visited:
            visited.add(currentNode)
            for next, dirn, _ in problem.getSuccessors(currentNode):
                if next not in visited:
                    nextPath = path + [dirn]
                    frontierStack.push((next, nextPath))

        if frontierStack.isEmpty():
            print('Faied to find path')
            return []   # Path Not found - failed to reach goal
        currentNode, path = frontierStack.pop()

    return  path
