def head(l):
    return l[0]

def tail(l):
    return l[1]

def listTolinkedList(l):
    if not l:
        return None
    else:
        return (l[0], listTolinkedList(l[1:]))

def mapl(func,l):
    if not l:
        return None
    else:
        return (func(head(l)), mapl(func, tail(l)))

def mod_lista_encadeada(l,n):
   return mapl(lambda x: x % n,listTolinkedList(l))

print(mod_lista_encadeada([2,5],2))