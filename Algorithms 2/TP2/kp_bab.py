from queue import Queue
from node import Node

def branch_and_bounds(totalItems, capacity, weight_cost):
    """
    totalItems: number of existing items
    capacity: the capacity of knapsack
    weight_cost: list of tuples like: [(weight, profit), ...]
    return the best profit
    """
    priority_queue = Queue()

    #sort items in non-increasing order by profit/weight
    ratios = [(index, item[1] / float(item[0])) for index, item in enumerate(weight_cost)]
    ratios = sorted(ratios, key=lambda x: x[1], reverse=True)
    # storing the best solution
    best_so_far = Node(0, [], 0.0, 0.0, 0.0)
    node = Node(0, [], 0.0, 0.0, calculate_bound(best_so_far, totalItems, capacity, weight_cost, ratios))
    priority_queue.push(node)
    # transverse through the tree
    while len(priority_queue) > 0:
        curr_node = priority_queue.pop()
        # check if we can get a better value
        if curr_node.bound > best_so_far.cost:
            curr_node_index = ratios[curr_node.level][0]
            next_item_cost = weight_cost[curr_node_index][1]
            next_item_weight = weight_cost[curr_node_index][0]
            # go to the next level of the tree
            next_added = Node(
                curr_node.level + 1,
                curr_node.selected_items + [curr_node_index],
                curr_node.cost + next_item_cost,
                curr_node.weight + next_item_weight,
                curr_node.bound
            )
            # check if the next value can be added to the solution
            if next_added.weight <= capacity:
                if next_added.cost > best_so_far.cost:
                    best_so_far = next_added
                
                if next_added.bound > best_so_far.cost:
                    priority_queue.push(next_added)

            next_not_added = Node(curr_node.level + 1, curr_node.selected_items, curr_node.cost,
                                  curr_node.weight, curr_node.bound)
            next_not_added.bound = calculate_bound(next_not_added, totalItems, capacity, weight_cost, ratios)
            if next_not_added.bound > best_so_far.cost:
                priority_queue.push(next_not_added)

    best_combination = [0] * totalItems
    # calculate the solution we've gottn and return the best profit
    for value in best_so_far.selected_items:
        best_combination[value] = 1
    return float(best_so_far.cost)


def calculate_bound(node, totalItems, capacity, weight_cost, ratios):
    # stop if the current weight is greater than the total capacity
    if node.weight >= capacity:
        return 0
    # if not, tranverse through the level we are at 
    # and calculate the upper bound
    else:
        upper_bound = node.cost
        total_weight = node.weight
        current_level = node.level

        while current_level < totalItems:
            current_index = ratios[current_level][0]
            # check if we won't go over the capacity level
            if total_weight + weight_cost[current_index][0] > capacity:
                cost = weight_cost[current_index][1]
                weight = weight_cost[current_index][0]
                upper_bound += (capacity - total_weight) * cost/weight
                break
            upper_bound += weight_cost[current_index][1]
            total_weight += weight_cost[current_index][0]
            current_level += 1

        return upper_bound