def head(l):
    return l[0]

def tail(l):
    return l[1]

def listTolinkedList(l):
    if not l:
        return None
    else:
        return (l[0], listTolinkedList(l[1:]))

def filterL(l,f):
    if not l:
        return None
    else:
        t = filterL(tail(l), f)
        h = head(l)
        return (h,t) if f(h) else t

def filterDivisible(l, n):
    return filterL(listTolinkedList(l), lambda x:x%n  == 0)

def appendL(l0,l1):
    if not l0 and not l1:
        return None
    elif not l0:
        return l1
    elif not l1:
        return l0
    else:
        return (head(l0), appendL(tail(l0),l1))

def qsort(l):
    if not l:
        return None
    else:
        t = tail(l)
        h = head(l)
        less = qsort(filterL(t, lambda x: x < h))
        high = qsort(filterL(t, lambda x: x >= h))
        return appendL(appendL(less, (h, None)),high)

def divisores_lista_encadeada(l,n):
    return qsort(filterDivisible(l,n))

print(divisores_lista_encadeada([1,7,10,5,99,30,15],3))