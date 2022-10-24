def mario(n):
    for i in range(1, n+1):
        print((n-i)*' ' + i*'#' + "  " + i*'#')


while True:
    try:
        n = int(input("Height: "))
        if n > 0 and n < 9:
            break
    except:
        print("invalid input!")
mario(n)