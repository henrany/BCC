import sys

f = open(sys.argv[1],"r")
contents = f.read()
l = []
for i in contents:
    l.append(i)
f.close()

def make_int(l):
    if not l:
        return []
    else:
        return filter(lambda x: x != ',', l)

def toInt(l):
    return map(lambda x:int(x),make_int(l))

def listToLinkedList(l):
    if not l:
        return None
    else:
        return (l[0], listToLinkedList(l[1:]))
def output(l):
    print(toInt(l))
    print(listToLinkedList(toInt(l)))

orig_sys = sys.stdout
with open(sys.argv[2],'w') as out:
    sys.stdout = out
    output(l)