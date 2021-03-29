from trie import Trie

head = Trie()

class Compress:
    def __init__(self):
        self.compressor = head
    
    def Compressor(self,FileIn, FileOut):
        input_file = open(FileIn, 'r')
        encoded_file = open(FileOut, 'w')
        text_from_file = input_file.read()
        combination = ''
        code = 1
        for char in text_from_file:
            combination += char
            if combination not in self.compressor.root.children:
                self.compressor.root.addChild(combination,code)
                if len(combination) == 1:
                    encoded_file.write('0' + combination)
                else:
                    encoded_file.write(self.compressor.root.children[combination[0:-1]] + combination[-1])
                code += 1
                combination = ''
        input_file.close()
        encoded_file.close()
        return True