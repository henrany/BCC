def capitalizeString(l):
    if not l:
        return []
    else:
        return list(map(lambda x: x.upper(), l))

def longestLength(l):
    m = 0
    words = ''
    for word in l:
        if m < len(word):
            m = len(word)
            words = word
    return words.upper()

def up_max_str(l):
    print(capitalizeString(l))
    return longestLength(l)

print(up_max_str(["azul","branco","amarelo"]))