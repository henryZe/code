while True:
    try:
        string = input()
        dict = {}
        for s in string:
            if s not in dict:
                dict[s] = 1
            else:
                dict[s] += 1

        freq = min(dict.values())
        for key, value in dict.items():
            if value == freq:
                string = string.replace(key, "")
        print(string)

    except:
        break