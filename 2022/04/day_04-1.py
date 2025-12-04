import re

def main():
    file_name = "input.txt"
    lines = []
    ranges = []
    total = 0

    with open(file_name, 'r') as f:
        lines = f.readlines()
    
    for i in range(len(lines)):
        lines[i] = lines[i].rstrip()

        tmp = []
        tmp = re.split(',|-', lines[i])
        # tmp = lines[i].split('-|,')
        # print(tmp)
        for j in range(4):
            tmp[j] = int(tmp[j])
        
        ranges.append(tmp)
    
    for i in range(len(ranges)):
        # possible valid outcomes:
        if (ranges[i][0] >= ranges[i][2]) and (ranges[i][1] <= ranges[i][3]):
            total += 1
            # print(ranges[i])
        elif (ranges[i][0] <= ranges[i][2]) and (ranges[i][1] >= ranges[i][3]):
            total += 1
            # print(ranges[i])

    
    print(total)


if __name__ == "__main__":
    main()
