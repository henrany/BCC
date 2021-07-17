# import time

class SimplexMethod:
    def __init__(self, restrictionNo:int, numOfVar:int, table:list):
        self.table = table
        self.auxTable = []
        self.restrictionNo = restrictionNo
        self.cost = 0
        self.numOfVar = numOfVar
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

    def getAnswer(self):
        return self.answer

    def setCost(self, value):
        self.cost = value

    # initialize the matrix with 0 values 
    def initializeMatrix(self):
        table = self.getTable()
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        for i in range((restrictionNo+2)):
            vec = []
            for j in range(restrictionNo+numOfVar+1):
                vec.append(0)
            table.append(vec)
        return table

    # change the cost function
    def fillCostList(self,j:int, value:int):
        table = self.getTable()
        table[0][j] = value * -1
        return table

    # fill the restrictions column
    def fillRestrictionList(self,i:int, j:int, value:int):
        table = self.getTable()
        resNo = self.getRestrictionNum()
        numVar = self.getNumOfVar()    
        if j == numVar:
            table[i+1][numVar+resNo] = value
            if value < 0:
                for j in range(len(table[i+1])):
                    table[i+1][j] = table[i+1][j] * -1
                table[i+1][i+numVar] = -1
            else:
                table[i+1][i+numVar] = 1
        else:
            table[i+1][j] = value
        return table

    def getPivotColumn(self):
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        table = self.getTable()
        minCol = 0
        minValue = 101
        for j in range(restrictionNo+numOfVar+1):
            if table[0][j] < minValue and table[0][j] != 0:
                minCol = j
                minValue = table[0][j]
        self.setColValues((minCol, minValue))
        return (minCol, minValue)

    def getPivotRow(self):
        # later these parameters will called once 
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
        # needs to be calculated once, later change the parameters to be called only once
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        colValues = self.getColValues()
        rowValues = self.getRowValues()
        table = self.getTable()
        divValue = table[rowValues[0]][colValues[0]]
        for j in range(restrictionNo+numOfVar+1):
            table[rowValues[0]][j] = table[rowValues[0]][j]/ divValue 
        return table

    def getPivotSubtractionValues(self):
        values:list = []
        # later this call will be done only once
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
        # again this call will be done only once
        # later these parameters will change our the whole program will be changed to classes
        rowValues = self.getRowValues()
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        subtractionValues = self.getPivotSubtractionValues()
        table = self.getTable()
        for i in range(restrictionNo+1):
            if i == rowValues[0]: continue
            for j in range(restrictionNo+numOfVar+1):
                table[i][j] = table[i][j] - (table[rowValues[0]][j] * subtractionValues[i])
        self.setCost(table[0][numOfVar+restrictionNo])


    def simplex(self):
        while True:
            pivotCol = self.getPivotColumn()
            pivotRow = self.getPivotRow()
            if pivotCol[1] > 0:
                if self.cost < 0:
                    self.setAnswer(("inviavel", self.auxTable))
                else:
                    self.setAnswer(("otima", self.cost, ))
                break
            elif pivotCol[1] < 0 and pivotRow[1] == 101:
                self.setAnswer(("ilimitada", (1,1,1)))
                break
            self.performNormalSimplex()

    def FromTableau(self):
        self.initializeMatrix()
        restrictionNo = self.getRestrictionNum()
        numOfVar = self.getNumOfVar()
        for i in range(numOfVar):
            val = int(input("input: "))
            self.fillCostList(i,val)

        for i in range(restrictionNo):
            for j in range(numOfVar+1):
                val = int(input("input2: "))
                self.fillRestrictionList(i, j,val)

    def run(self):
        self.FromTableau()
        self.simplex()
        return self.answer



simpleRun = SimplexMethod(4,4,[])
print(simpleRun.run())