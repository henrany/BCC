# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
import math


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    actions = {}
    parent = {}
    visited = {}
    answer = []
    startState = problem.getStartState()
    stack = util.Stack()
    stack.push(startState)
    while not stack.isEmpty():
        topElement = stack.pop()
        visited[topElement] = True
        if problem.isGoalState(topElement):
            while topElement in actions:
                answer.append(actions[topElement])
                topElement = parent[topElement]
            return answer[::-1]
        toVisit = problem.getSuccessors(topElement)
        for node in toVisit:
            if node[0] not in visited:
                parent[node[0]] = topElement
                actions[node[0]] = node[1]
                stack.push(node[0])


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    actions = {}
    visited = {}
    parent = {}
    answer = []
    queue = util.Queue()
    startState = problem.getStartState()
    queue.push(startState)
    visited[startState] = True
    while not queue.isEmpty():
        topElement = queue.pop()
        if problem.isGoalState(topElement):
            while topElement in actions:
                answer.append(actions[topElement])
                topElement = parent[topElement]
            return answer[::-1]
        toVisit = problem.getSuccessors(topElement)
        for node in toVisit:
            if node[0] not in visited:
                parent[node[0]] = topElement
                actions[node[0]] = node[1]
                visited[node[0]] = True
                queue.push(node[0])


def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    actions = {}
    visited = {}
    parent = {}
    pathCost = {}
    answer = []
    pQueue = util.PriorityQueue()
    startState = problem.getStartState()
    pathCost[startState] = 0
    pQueue.push(startState, 0)
    visited[startState] = True
    while not pQueue.isEmpty():
        topElement = pQueue.pop()
        if problem.isGoalState(topElement):
            while topElement in actions:
                answer.append(actions[topElement])
                topElement = parent[topElement]
            return answer[::-1]
        toVisit = problem.getSuccessors(topElement)
        for node in toVisit:
            if node[0] not in visited:
                pathCost[node[0]] = pathCost[topElement] + node[2]
                parent[node[0]] = topElement
                actions[node[0]] = node[1]
                pQueue.push(node[0], pathCost[node[0]])
                visited[node[0]] = True
            elif pathCost[node[0]] > pathCost[topElement] + node[2]:
                cost = pathCost[topElement] + node[2]
                pQueue.update(node[0], cost)
                parent[node[0]] = topElement
                actions[node[0]] = node[1]
                pathCost[node[0]] = cost


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def greedySearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest heuristic first."""
    "*** YOUR CODE HERE ***"
    visited = {}
    actions = {}
    parent = {}
    answer = []
    pQueue = util.PriorityQueue()
    startState = problem.getStartState()
    cost = heuristic(startState, problem)
    pQueue.push(startState, cost)
    visited[startState] = True
    while not pQueue.isEmpty():
        topElement = pQueue.pop()
        if problem.isGoalState(topElement):
            while topElement in actions:
                answer.append(actions[topElement])
                topElement = parent[topElement]
            return answer[::-1]
        toVisit = problem.getSuccessors(topElement)
        for node in toVisit:
            if node[0] not in visited:
                cost = heuristic(node[0], problem)
                actions[node[0]] = node[1]
                parent[node[0]] = topElement
                visited[node[0]] = True
                pQueue.push(node[0], cost)


def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    actions = {}
    parent = {}
    visited = {}
    pathCost = {}
    answer = []
    pQueue = util.PriorityQueue()
    startState = problem.getStartState()
    pathCost[startState] = 0 
    pQueue.push(startState, 0)
    visited[startState] = True
    while not pQueue.isEmpty():
        topElement = pQueue.pop()
        if problem.isGoalState(topElement):
            while topElement in actions:
                answer.append(actions[topElement])
                topElement = parent[topElement]
            return answer[::-1]
        toVisit = problem.getSuccessors(topElement)
        for node in toVisit:
            if node[0] not in visited:
                cost = heuristic(node[0], problem)
                pathCost[node[0]] = node[2] + pathCost[topElement]
                bcost = cost + pathCost[node[0]]
                pQueue.push(node[0], bcost)
                actions[node[0]] = node[1]
                parent[node[0]] = topElement
                visited[node[0]] = True
            elif pathCost[node[0]] > pathCost[topElement] + node[2]:
                cost = pathCost[topElement] + node[2]
                pQueue.update(node[0], cost)
                parent[node[0]] = topElement
                actions[node[0]] = node[1]
                pathCost[node[0]] = cost


def foodHeuristic(state, problem):
    """
    Your heuristic for the FoodSearchProblem goes here.

    This heuristic must be consistent to ensure correctness.  First, try to come
    up with an admissible heuristic; almost all admissible heuristics will be
    consistent as well.

    If using A* ever finds a solution that is worse uniform cost search finds,
    your heuristic is *not* consistent, and probably not admissible!  On the
    other hand, inadmissible or inconsistent heuristics may find optimal
    solutions, so be careful.

    The state is a tuple ( pacmanPosition, foodGrid ) where foodGrid is a Grid
    (see game.py) of either True or False. You can call foodGrid.asList() to get
    a list of food coordinates instead.

    If you want access to info like walls, capsules, etc., you can query the
    problem.  For example, problem.walls gives you a Grid of where the walls
    are.

    If you want to *store* information to be reused in other calls to the
    heuristic, there is a dictionary called problem.heuristicInfo that you can
    use. For example, if you only want to count the walls once and store that
    value, try: problem.heuristicInfo['wallCount'] = problem.walls.count()
    Subsequent calls to this heuristic can access
    problem.heuristicInfo['wallCount']
    """
    position, foodGrid = state
    "*** YOUR CODE HERE ***"
    thisList = foodGrid.asList()
    thisList = thisList[::-1]
    dx = 0
    dy = 0
    walls = problem.walls.asList()
    if len(thisList) != 0:
        dx = abs(position[0] - thisList[0][0])
        dy = abs(position[1] - thisList[0][1])
    return dx + dy


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
ucs = uniformCostSearch
gs = greedySearch
astar = aStarSearch
tiny= tinyMazeSearch
