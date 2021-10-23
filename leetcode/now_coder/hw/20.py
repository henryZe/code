import re

def check(string):
    n = len(string)
    if n < 9:
        return False

    substr = []
    for i in range(n - 2):
        substr.append(string[i:i+3])
    if len(substr) != len(set(substr)):
        return False

    Upper = '[A-Z]'
    Lower = '[a-z]'
    num = '\d'
    chars = '[^A-Za-z0-9_]'
    patterns = [Upper, Lower, num, chars]
    check_type = 0

    for pattern in patterns:
        pw = re.search(pattern, string)
        if pw:
            check_type += 1
    if check_type < 3:
        return False

    return True

while True:
    try:
        string = input()
        if check(string):
            print("OK")
        else:
            print("NG")
    except:
        break
