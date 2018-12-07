"""
    Requires Queue implementation which is very easy.
    Problem is object of custom data structure, but it is easy to replace it with different data structure

    If you diff function definition with that of DFS, Only Stack is replaced by Queue
"""

def BreadthFirstSearch(problem):
    frontierStack = util.Queue()
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
