alphabet = "abcdefghijklmnopqrstuvwxyz"

def map_letter_prios():
    map = {}
    count = 1

    for char in alphabet:
        map[char] = count
        map[char.upper()] = count + 26
        count += 1
    
    return map


def main():
    map = map_letter_prios()
    # print(map)
    file_name = "input.txt"
    lines = []
    total = 0

    with open(file_name, "r") as f:
        lines = f.readlines()
    
    for i in range(len(lines)):
        # line_len = 0
        lines[i] = lines[i].rstrip()

        half_line_len = len(lines[i]) // 2

        # print(lines[i][0:half_line_len-1])
        # print(lines[i][half_line_len:])
        first_half_set = set(lines[i][0:half_line_len])
        second_half_set = set(lines[i][half_line_len:])

        # print(first_half_set)
        # print(second_half_set)

        # print(first_half_set.intersection(second_half_set))

        intersect = first_half_set.intersection(second_half_set)

        if len(intersect) == 1:
            total += map[intersect.pop()]
        
    print(total)






if __name__ == "__main__":
    main()
    