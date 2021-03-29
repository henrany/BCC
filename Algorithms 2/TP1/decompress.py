from trie import Trie


head = Trie()

class Decode:
    def __init__(self):
        self.decompress = head

    def Decompress(self,FileIn, FileOut):
        coded_file = open(FileIn, 'r')
        decoded_file = open(FileOut, 'w')
        text_from_file = coded_file.read()
        self.decompress.children = {'0': '', '1': text_from_file[1]}
        decoded_file.write(self.decompress.children['1'])
        text_from_file = text_from_file[2:]
        combination = ''
        code = 2
        for char in text_from_file:
            if char in '1234567890':
                combination += char
            else:
                self.decompress.children[str(code)] = self.decompress.children[combination] + char
                decoded_file.write(self.decompress.children[combination] + char)
                combination = ''
                code += 1
        coded_file.close()
        decoded_file.close()