def digits_sum(n):
    digits_sum = 0
    digits_sum += n % 10
    while n // 10 > 0:
        n = n // 10
        digits_sum += n % 10
    return digits_sum


def Luhn(number):
    """ n is a string """
    n_ls = [c for c in number]
    Lenth = len(number)
    position = 0

    luhn = 0
    for i in range(Lenth-1, -1, -1):
        if position % 2 == 0:
            luhn += int(n_ls[i])
        else:
            luhn += digits_sum(int(n_ls[i]) * 2)
        position += 1

    if luhn % 10 == 0:
        return True
    else:
        return False


number = input("Number: ")
n_ls = [c for c in number]
if len(number) == 15:
    head = n_ls[0] + n_ls[1]
    if (head == "34" or head == "37") and Luhn(number):
        print("AMEX")
    else:
        print("INVALID")
elif len(number) == 16:
    head = n_ls[0] + n_ls[1]
    if (int(head) >= 51 and int(head) <= 55) and Luhn(number):
        print("MASTERCARD")
    elif n_ls[0] == '4' and Luhn(number):
        print("VISA")
    else:
        print("INVALID")
elif len(number) == 13:
    if n_ls[0] == '4' and Luhn(number):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")