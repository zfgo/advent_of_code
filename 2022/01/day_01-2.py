def main():
    f_name = "input1.txt"
    current = 0
    # maximum0 = 0
    # maximum1 = 0
    # maximum2 = 0
    maximums = [0, 0, 0]
    lines = []

    with (open(f_name, 'r')) as f:
        lines = f.readlines()
    
    for i in range(len(lines)):
        if lines[i] != "\n":
            # print(lines[i], end='')
            current += int(lines[i].rstrip())

        else:
            # print(current)
            # print(maximums)

            minimum = min(maximums)
            if current > minimum:
                maximums[maximums.index(minimum)] = current
        
            current = 0
    
    print(sum(maximums))


if __name__ == "__main__":
    main()
