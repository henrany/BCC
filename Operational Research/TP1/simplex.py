# import time

# left with fixing the optimal values 
# using the auxiliary simplex ou using dual simplex
# certificate of optimality ou unboundness
# certificate of infeasibility

class SimplexMethod:
    def __init__(self, restrictionNo:int, numOfVar:int, table:list):
        self.table = table
        self.numOfVar = numOfVar
        self.restrictionNo = restrictionNo
        self.certtificattTable = []
        self.optimalValuesSet = set()
        self.auxCertificateRow = set()
        self.saveOriginalCostFunction = []
        self.optimalValues = []
        self.cost = 0
        self.useAuxillarySimplex = False
        self.rowValues = ()
        self.colValues = ()
        self.answer = ()
    
    def getRestrictionNum(self):
        return self.restrictionNo

    def getNumOfVar(self):
        return self.numOfVar

    def getTable(self):
        return self.table
    
    def setRowValues(self, value):
        self.rowValues = value

    def setColValues(self, value):
        self.colValues = value

    def getColValues(self):
        return self.colValues

    def getRowValues(self):
        return self.rowValues

    def setAnswer(self, value):
        self.answer = value

    def setCost(self, value):
        self.cost = value

    # initialize the matrix with 0 values 
    def initializeMatrix(self):
        table = self.getTable()
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        for i in range((restrictionNo+1)):
            vec = []
            for j in range(restrictionNo+numOfVar+1):
                vec.append(0)
            table.append(vec)

        for i in range(numOfVar+restrictionNo+1):
            self.saveOriginalCostFunction.append(0)
        
        for i in range(numOfVar):
            self.optimalValues.append(0)

        if restrictionNo >= numOfVar:
            for i in range(restrictionNo+1):
                vec = []
                for j in range(restrictionNo):
                    vec.append(0)
                self.certtificattTable.append(vec)
        else:
            for i in range(numOfVar):
                vec = []
                for j in  range(restrictionNo):
                    vec.append(0)
                self.certtificattTable.append(vec)
        return table

    # change the cost function
    def fillCostList(self,j:int, value:int):
        table = self.getTable()
        table[0][j] = value * -1
        self.saveOriginalCostFunction[j] = table[0][j]
        return table

    # fill the restrictions column
    def fillRestrictionList(self,i:int, j:int, value:int):
        table = self.getTable()
        resNo = self.getRestrictionNum()
        numVar = self.getNumOfVar()   
        if j == numVar:
            table[i+1][numVar+resNo] = value
            if value < 0:
                self.useAuxillarySimplex = True
                self.auxCertificateRow.add(i)
                for j in range(len(table[i+1])):
                    table[i+1][j] = table[i+1][j] * -1
                table[i+1][i+numVar] = -1
            else:
                table[i+1][i+numVar] = 1
        else:
            table[i+1][j] = value
        return table

    def FromTableau(self):
        self.initializeMatrix()
        restrictionNo = self.getRestrictionNum()
        inputList = list(map(int, input().split()))
        for i in range(len(inputList)):
            self.fillCostList(i,int(inputList[i]))

        for i in range(restrictionNo):
            inputList2 = list(map(int, input().split()))
            for j in range(len(inputList2)):
                self.fillRestrictionList(i, j,int(inputList2[j]))
        
        for i in range(restrictionNo+1):
            if i == 0: continue
            self.certtificattTable[i][i-1] = 1
        
    def FormAuxilliarySimplex(self):
        table = self.getTable()
        numOfVar = self.getNumOfVar()
        restrictionNo = self.getRestrictionNum()
        for i in range(restrictionNo+numOfVar+1):
            if i < numOfVar or i == numOfVar+restrictionNo:
                table[0][i] = 0
            else:
                table[0][i]  = 1

        for value in self.auxCertificateRow:
            for i in  range(len(self.certtificattTable[value])):
                self.certtificattTable[value+1][i] = self.certtificattTable[value+1][i] * -1

        for i in range(len(table)):
            if i == 0: continue
            for  j in range(len(table[i])):
                table[0][j] -= table[i][j]
                if j < restrictionNo:
                    self.certtificattTable[0][j] -= self.certtificattTable[i][j]
        self.setCost(table[0][restrictionNo+numOfVar])

    def getPivotColumn(self):
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        table = self.getTable()
        minCol = 0
        minValue = 101
        for j in range(restrictionNo+numOfVar):
            if table[0][j] < minValue and table[0][j] != 0:
                minCol = j
                minValue = table[0][j]
        self.setColValues((minCol, minValue))
        return (minCol, minValue)

    def getPivotRow(self):
        colValues = self.getColValues()
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        table = self.getTable()
        pivRow = 0
        minPivotValue = 101
        for i in range(1,restrictionNo+1):
            if table[i][colValues[0]] <= 0: continue
            else:
                value =  table[i][restrictionNo+numOfVar]/table[i][colValues[0]]
                if value < minPivotValue:
                    minPivotValue = value
                    pivRow = i
        self.setRowValues((pivRow, minPivotValue))
        return (pivRow, minPivotValue)

    def makePivotRowOne(self):
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        colValues = self.getColValues()
        rowValues = self.getRowValues()
        table = self.getTable()
        divValue = table[rowValues[0]][colValues[0]]

        for j in range(restrictionNo+numOfVar+1):
            if j < restrictionNo:
                self.certtificattTable[rowValues[0]][j] = self.certtificattTable[rowValues[0]][j]/divValue
            table[rowValues[0]][j] = table[rowValues[0]][j]/ divValue 
        return table

    def getPivotSubtractionValues(self):
        values:list = []
        colValues = self.getColValues()
        rowValues = self.getRowValues()
        restrictionNo = self.getRestrictionNum()
        table = self.makePivotRowOne()
        values.append(colValues[1])
        for i in range(1,restrictionNo+1):
            if i == rowValues[0]: 
                values.append(0)
            else:
                values.append(table[i][colValues[0]])
        return values

    def performNormalSimplex(self):
        rowValues = self.getRowValues()
        colValues = self.getColValues()
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        subtractionValues = self.getPivotSubtractionValues()
        table = self.getTable()
        for i in range(restrictionNo+1):
            if i == rowValues[0]:
                continue
            for j in range(restrictionNo+numOfVar+1):
                if j < restrictionNo:
                    self.certtificattTable[i][j] = self.certtificattTable[i][j] - (self.certtificattTable[rowValues[0]][j] * subtractionValues[i])
                table[i][j] = table[i][j] - (table[rowValues[0]][j] * subtractionValues[i])
            self.optimalValuesSet.add((rowValues[0], colValues[0]))
        self.setCost(table[0][numOfVar+restrictionNo])

    def simplex(self):
        self.FromTableau()
        if self.useAuxillarySimplex:
            self.FormAuxilliarySimplex()
            while True:
                pivotCol = self.getPivotColumn()
                if pivotCol[1] > 0:
                    if self.cost < 0:
                        self.setAnswer(("inviavel", self.certtificattTable[0]))
                        break
                    elif self.cost == 0:
                        self.table[0] = self.saveOriginalCostFunction
                        while True:
                            pivotCol = self.getPivotColumn()
        else:
            while True:
                pivotCol = self.getPivotColumn()
                pivotRow = self.getPivotRow()
                if pivotCol[1] > 0:
                    if self.cost < 0:
                        self.setAnswer(("inviavel", self.certtificattTable[0]))
                        break
                    else:
                        for value in self.optimalValuesSet:
                            if value[1] >= self.numOfVar: continue
                            self.optimalValues[value[1]] = self.table[value[0]][self.numOfVar + self.restrictionNo]
                        self.setAnswer(("otima", self.cost, self.optimalValues, self.certtificattTable[0]))
                    break
                elif pivotCol[1] < 0 and pivotRow[1] == 101:
                    self.setAnswer(("ilimitada", self.optimalValues,))
                    break
                self.performNormalSimplex()

    def run(self):
        self.simplex()
        return self.answer