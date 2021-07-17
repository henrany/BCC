from simplex import SimplexMethod

def main():
    valOne, valTwo = input().split()
    valOne = int(valOne)
    valTwo = int(valTwo)
    simplex = SimplexMethod(valOne, valTwo, [])
    answer = simplex.run()
    for ans in answer:
        if type(ans) is list:
            print(*ans)
        else:
            print(ans)

if __name__ == "__main__":
    main()
