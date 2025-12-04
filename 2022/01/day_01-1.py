def main():
    f_name = "input1.txt"
    current = 0
    maximum = 0
    tmp = 0
    lines = []

    with (open(f_name, 'r')) as f:
        lines = f.readlines()
    
    for i in range(len(lines)):
        if lines[i] != "\n":
            
            current += int(lines[i].rstrip())
        else:
            if current > maximum:
                maximum = current
            current = 0
    
    print(maximum)


if __name__ == "__main__":
    main()
