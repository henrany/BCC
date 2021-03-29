from node import Node
import csv

class kpBacktrack:
    """
    weights: list of all the weights
    profit: the profit of each of the weights
    totalCap: the total capacity of the bag
    totalItems: the total number of items
    """
    def __init__(self,weights,profit, totalCap, totalItems):
        self.weights = weights
        self.profit = profit
        self.totalCap = totalCap
        self.finalSol = [None] * totalItems
        self.interSol = [None] * totalItems
        self.finalProfit = 0
        self.finalWeight = 0
        self.totalItems = totalItems
    
    # sort the values by profit/weight
    def sortProfitWeight(self):
        items = []
        for i in range(self.totalItems):
            items.append({'value' :i,'p':self.profit[i]/self.weights[i]})
        items = sorted(items,key=lambda k: k['p'], reverse=True)
        newWeights = []
        newProfits = []
        for key in items:
            newWeights.append(self.weights[key['value']])
            newProfits.append(self.profit[key['value']])
        self.profit = newProfits[:]
        self.weights = newWeights[:]

    # calculating the bonnd
    def bound(self,currentCap, currentWgt, currentIdx):
        b = currentCap
        c = currentWgt
        i = currentIdx+1
        for i in range(self.totalItems):
            c = c+self.weights[i]
            if c < self.totalCap:
                b = b+self.profit[i]
            else:
                return b+(1 - (c - self.totalCap)/self.weights[i])*self.profit[i]
        return b

    # knapsack function which takes the current index
    # current capacity and the current weight
    def knapsack(self,currentIdx, currentCap, currentWgt):
        # first checks whetere the weight can be added
        if currentWgt + self.weights[currentIdx] <= self.totalCap:
            # store the intermediate solution
            self.interSol[currentIdx] = 1
            # check if  its not out of bounds when calling knapsack again recursively
            if currentIdx+1 < self.totalItems :
                self.knapsack(currentIdx+1,currentCap+self.profit[currentIdx],currentWgt+self.weights[currentIdx])
            # update the final profit if the current profit is greater than it
            if currentCap + self.profit[currentIdx] > self.finalProfit:
                self.finalProfit = currentCap + self.profit[currentIdx]
                self.finalWeight = currentWgt + self.weights[currentIdx]
        # check whether the bound is greater than the final profit
        if self.bound(currentCap, currentWgt, currentIdx) >= self.finalProfit:
            self.interSol[currentIdx] = 0
            if currentIdx+1 < self.totalItems:
                self.knapsack(currentIdx+1,currentCap, currentWgt)
            # update the current profit and current weight
            if currentCap > self.finalProfit:
                self.finalProfit = currentCap
                self.finalWeight = currentWgt
                for j in range(currentIdx):
                    self.finalSol[j] = self.interSol[j]

    # return the final results
    def solver(self):
        return self.finalProfit