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
    file_name = "input.txt"
    lines = []
    total = 0

    with open(file_name, "r") as f:
        lines = f.readlines()
    
    for i in range(len(lines) // 3):
        start_ind = i * 3

        for j in range(3):
            cur_ind = start_ind + j

            lines[cur_ind] = lines[cur_ind].rstrip()

        set_1 = set(lines[start_ind])
        set_2 = set(lines[start_ind + 1])
        set_3 = set(lines[start_ind + 2])

        intersect = set_1.intersection(set_2.intersection(set_3))

        total += map[intersect.pop()]



        # half_line_len = len(lines[i]) // 2

        # first_half_set = set(lines[i][0:half_line_len])
        # second_half_set = set(lines[i][half_line_len:])

        # intersect = first_half_set.intersection(second_half_set)

        # if len(intersect) == 1:
        #     total += map[intersect.pop()]
        
    print(total)



if __name__ == "__main__":
    main()
    