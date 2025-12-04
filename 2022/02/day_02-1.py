def main():
    f_name = "input.txt"
    lines = []
    # rock = {"A", "X"}
    # paper = {"B", "Y"}
    # scissors = {"C", "Z"}
    score = 0

    outcomes = {"A X\n":(1 + 3), "A Y\n":(2 + 6), "A Z\n":(3 + 0),
                "B X\n":(1 + 0), "B Y\n":(2 + 3), "B Z\n":(3 + 6), 
                "C X\n":(1 + 6), "C Y\n":(2 + 0), "C Z\n":(3 + 3)}

    # scores = {"r":1, "p":2, "s":3, "l":0, "d":3, "w":6}

    with open(f_name, 'r') as f:
        lines = f.readlines()
    
    for line in lines:
        # line = line.rstrip()
        # l = line.split(" ")

        # if l[0] == 
        score += outcomes[line]

    print(score)



    return


if __name__ == "__main__":
    main()