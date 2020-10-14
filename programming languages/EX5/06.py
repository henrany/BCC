class  Visitor:
    "A parameterized  list  visitor."
    def  __init__(self , cb):
        self.cb = cb
    def  __str__(self):
        return "Visitor  with  callback: {0}".format(self.cb)
    def  visit(self , n):
        for i in  range(0, len(n)):
            n[i] = self.cb.update(n[i])
        return n
class  CallbackBase:
    "The  basic  callback"
    def  __init__(self):
        self.f = lambda x: x+1
    def  __str__(self):
        return "basic  callback"
    def  shouldUpdate(self , i):
        return  True
    def  update(self , i):
        return  self.f(i) if self.shouldUpdate(i) else i
    
class CallbackCube(CallbackBase):
  def __init__(self):
    self.f = lambda x: x**3
  def __str__(self):
    return "double callback"

class CallbackOdd(CallbackBase):
    def __str__(self):
        return "odd callback"
    def shouldUpdate(self, i):
        return i % 2 == 1

# in python 3, the linearity of inheritance must be obeyed 
# because it was giving erros when CallbackBase was called first 

class CallbackMult(CallbackOdd, CallbackBase):
    def __str__(self):
        return "multiple callback"
# the comportment of object visiter on CallbackMult on integers will be of first 
# checking whether each of the element in  the list is odd, and if so ,
# it will then update thats element by incrementing it by 1, if not, it will leave the element as it is 
    

# v = Visitor(CallbackMult())
# print(v.visit([0,1,2,3]))