import sys
from compress import Compress
from decompress import Decode

encoder = Compress()
decoder = Decode()

def main():
    if len(sys.argv) < 2:
        print('command line should be more than 1')
    
    if sys.argv[1] == '-c':
        nameOfFile = sys.argv[2]
        name = ''
        for char in nameOfFile:
            if char == '.':
                break
            else:
                name+=char
        if len(sys.argv) == 3:
            encoder.Compressor(sys.argv[2], name +'.lz78')
        else:
            encoder.Compressor(sys.argv[2], sys.argv[4])
    
    if sys.argv[1] == '-x':
        decodeName = sys.argv[2]
        name = ''
        for char in decodeName:
            if char == '.':
                break
            else:
                name+=char
        if len(sys.argv) == 3:
            decoder.Decompress(sys.argv[2], name+'.txt')
        else:
            decoder.Decompress(sys.argv[2],sys.argv[4])

if __name__ == "__main__":
    main()