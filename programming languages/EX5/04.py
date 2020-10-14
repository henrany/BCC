class  ConsCell:
    def  __init__(self , h, t):
        """ Creates a new  cell  with  head == h, and  tail == t."""
        self.head = h
        self.tail = t

class  List:
    """ Describes a simple  list  data  type."""
    def  __init__(self , n):
        """ creates a new  list  with n as the  first  element."""
        self.start = n

    def  cons(self , e):
        """ Adds a new  element  into  the  list; hence , procuding a new  list."""
        return  List(ConsCell(e, self.start))

    def  __str__(self):
        """ Returns a textual  representation  of this  list."""
        ans = "["
        cell = self.start
        while  cell != 0:
            ans = ans + repr(cell.head)
            cell = cell.tail
            if cell != 0:
                ans = ans + ", "
        ans = ans + "]"
        return  ans

    def length(self):
        ans = 0
        cell = self.start
        while cell != 0:
            ans = ans + 1
            cell = cell.tail
        return ans
    
    def concat(self,n):
        cell = self.start
        l = []
        while cell != 0:
            l.append(cell.head)
            cell = cell.tail
        l.reverse()
        return l



def  test():

    a = List(0)
    b = a.cons(2)
    c = b.cons("Hi")
    d = b.cons("hello")
    print("List a = ", a.__str__ ())
    print("List b = ", b.__str__ ())
    print("List c = ", c.__str__ ())
    print("List d = ", d.__str__ ())
    print(c.concat(d))
test()