class  Animal:
    atrb_animal = 0
    def  __init__(self , nome):
        self.nome = nome
    def  __str__(self):
        return  self.nome + " eh um  animal"
    def  comer(self):
        print(self.nome + ", que eh um animal , esta  comendo.")
class  Mamifero(Animal):
    def  __str__(self):
        return(self.nome + " eh um  mamifero")
    def  beber_leite(self):
        print(self.nome + ", que eh um mamifero , esta  bebendoleite.")
class  Cao(Mamifero):
    def  __str__(self):
        return  self.nome + " eh um  cachorro"
    def  latir(self):
        print(self.nome + " esta  latindo  bem  auto.")
    def  comer(self):
        print(self.nome + " late  quando  come.")
        self.latir()
def  test():
    a1 = Animal("Tigrinho")
    a2 = Mamifero("Oncinha")
    a3 = Cao("Mameluco")
    print(a1)             # 1
    print(a2)             # 2
    print(a3)             # 3
    a1.comer ()            # 4
    a2.beber_leite ()     # 5
    a2.comer ()            # 6
    a3.latir ()            # 7
    a3.beber_leite ()     # 8
    a3.comer ()            # 9
    # a1.beber_leite ()     # 10
    a1 = a3
    a1.latir ()            # 11