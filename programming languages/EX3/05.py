from functools import reduce
def filterInt(l):
    if not l:
        return []
    else:
        return list(filter(lambda x:isinstance(x,int),l))

def mult_int(l):
    return reduce(lambda x,acc: x*acc, filterInt(l), 1)

def filterDec(l):
    if not l:
        return []
    else:
        return list(filter(lambda x:isinstance(x,float), l))

def  sum_dec(l):
    return reduce(lambda x,acc: x+acc,filterDec(l), 0)

def filterStr(l):
    if not  l:
        return []
    else:
        return list(filter(lambda x:isinstance(x,str), l))

def letras_lower(l):
    return list(map(lambda x:x.lower(),filterStr(l)))

print(letras_lower([1,"A",9.0,0.9,5,4]))