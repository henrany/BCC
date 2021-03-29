
class Node(object):
    def __init__(self, level, selected_items, cost, weight, bound):
        self.level = level
        self.selected_items = selected_items
        self.cost = cost
        self.weight = weight
        self.bound = bound