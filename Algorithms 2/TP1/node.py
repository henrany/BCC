class Node:
    def __init__(self, key=None, code=None):
        self.key = key
        self.code = code
        self.children = dict()
        self.endofWord = False

    def addChild(self,key,code):
        self.children[key] = str(code)