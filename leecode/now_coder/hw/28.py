letter_de = list("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
letter_en = list("BCDEFGHIJKLMNOPQRSTUVWXYZAbcdefghijklmnopqrstuvwxyza")
num_de = list("0123456789")
num_en = list("1234567890")
 
def encrypt(ss, letter_de, letter_en, num_de, num_en):
    l = []
    for s in ss:
        if s in letter_de:
            # print(letter_de.index(s))
            l.append(letter_en[letter_de.index(s)])
        else:
            # print(num_de.index(s))
            l.append(num_en[num_de.index(s)])
    return "".join(l)


while True:
    try:
        str_de = input()
        str_en = input()

        print(encrypt(str_de, letter_de, letter_en, num_de, num_en))
        print(encrypt(str_en, letter_en, letter_de, num_en, num_de))
        # print(decrypt(str_en))

    except EOFError:
        break