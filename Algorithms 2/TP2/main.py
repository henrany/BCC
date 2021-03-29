import sys
import time
import os
import csv
from kp_backtrack import kpBacktrack
from kp_bab import branch_and_bounds

# function for writing to csv
def writeToFile(values, fileIn):
    with open(fileIn,'w') as file:
        writer = csv.writer(file, delimiter=';')
        writer.writerows(values)

def main():
    # getting all the tests files
    # all the tests cases should be in single folder and 
    # the name of the folder passed in the command line
    # as the first argument
    arr = os.listdir(sys.argv[1])
    # sort the list of files inside tests files
    # this is done just for better reading of files
    arr = sorted(arr)
    # get all the output to be written to file
    listOfValues = []
    listOfValues.append(['test_name','Student_Name','backtrack_exe_time(ms)','branch_&_bound_exe_time(ms)','value'])
    for files in arr:
        profits = []
        weights = []
        weight_cost = []
        totalItems = 0
        totalCap = 0
        # reading the informations in the file
        textFile = open(sys.argv[1]+'/'+files,'r')
        readFile = textFile.read()
        reader = readFile.split('\n')
        for i in range(len(readFile.split('\n'))):
            if i == 0:
                value = reader[i].split(' ')
                totalItems = int(value[0])
                totalCap = int(value[1])
            else:
                value = reader[i].split(' ')
                profits.append(float(value[0]))
                weights.append(float(value[1]))
                weight_cost.append((float(value[1]),float(value[0])))
        # calling backtract
        head = kpBacktrack(weights,profits,totalCap,totalItems)
        # sort them by profit/weight
        head.sortProfitWeight()
        # time of executionn of bactract
        backStartTime = time.process_time()
        head.knapsack(0,0,0)
        backEndTime = time.process_time() - backStartTime
        # excecution time for branch and bound
        babStarttime = time.process_time()
        branch_and_bounds(totalItems,totalCap,weight_cost)
        babEndtime = time.process_time() - babStarttime
        # converting from seconds to milliseconds
        backEndTime = backEndTime* 1000
        babEndtime = babEndtime * 1000
        # list for writing to csv
        listOfValues.append([files,'Henry Tamekloe',backEndTime,babEndtime,head.finalProfit])
        textFile.close()
    writeToFile(listOfValues,'output.csv')

if __name__ == "__main__":
    # run the code by python3 main.py <tests Folder>
    # all the tests cases should be in a single folder
    main()