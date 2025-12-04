columns = []


def routine(amount_to_move, move_from, move_to):
    move_from -= 1
    move_to -= 1
    # tmp = []

    for _ in range(amount_to_move):
        columns[move_to].append(columns[move_from].pop())
    
    # for _ in range(amount_to_move):
        # columns[move_to].append(tmp.pop())

    return


def main():
    file_name = "input.txt"
    lines = []
    total = 0
    crate_ct = 0
    row_ct = 0
    indicator = True
    column_ct = 0
    output = ""

    with open(file_name, 'r') as f:
        lines = f.readlines()
    
    for i in range(len(lines)):
        lines[i] = lines[i].rstrip("\n")
        row_ct += 1

        if lines[i].find('[') >= 0:
            for char in lines[i]:
                if char == '[':
                    crate_ct += 1
        elif indicator:
            indicator = False
            column_ct = len(lines[i].split())
            break
    
    row_ct -= 1
    
    for i in range(column_ct):
        columns.append([])
    
    # Add the characters to the stacks (note they are in reverse order)
    for i in range(row_ct):
        for j in range(column_ct):
            char_loc = (j * 4) + 1
            character = lines[i][char_loc]
            # print(character, char_loc)
            if character != ' ':
                columns[j].append(character)
    # print(columns)


    for i in range(column_ct):
        columns[i].reverse()
    
    for line in lines:
        if line.find("move") >= 0:
            line.rstrip()
            line_li = line.split()
            amount_to_move = int(line_li[1])
            move_from = int(line_li[3])
            move_to = int(line_li[5])

            routine(amount_to_move, move_from, move_to)
            # print(columns)



    for i in range(len(columns)):
        output += columns[i].pop()
            
    


    # print(crate_ct, column_ct, row_ct)
            

    
    print(output)


if __name__ == "__main__":
    main()
