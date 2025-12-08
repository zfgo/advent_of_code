def math_hw(nums, ops):
    score = 0
    problem = 0
    for i in range(len(nums)):
        if ops[i] == '*':
            problem = 1
            for j in range(len(nums[i])):
                if nums[i][j]:
                    problem *= nums[i][j]
            score += problem
        if ops[i] == '+':
            problem = 0
            for j in range(len(nums[i])):
                problem += nums[i][j]
            score += problem

    return score

def main():
    fstr = "input.txt"
    lines = []

    with open(fstr, 'r') as f:
        lines = f.readlines()

    # parse the input
    for i, line in enumerate(lines):
        lines[i] = lines[i].rstrip('\n')

    ops = []
    nums = []
    cn_list = []
    
    for i in range(len(lines[0])-1, -1, -1):
        cn = 0
        exponent = 0
        for j in range(len(lines)):
            #print(lines[j][i])
            if lines[j][i] in '+*':
                # reached the end of this current number list (cn_list)
                ops.append(lines[j][i])
                cn = int(str(cn)[::-1]) # reverse the number bc im dumb
                cn_list.append(cn)
                nums.append(cn_list)
                cn_list = []
            elif lines[j][i] != ' ':
                cn += (10 ** exponent) * int(lines[j][i])
                exponent += 1
        cn = int(str(cn)[::-1]) # reverse the number bc im dumb
        cn_list.append(cn)

    for i in range(1, len(nums)):
        nums[i].pop(0)

    #print(nums)
    #print(ops)

    print("Math HW answer: ", math_hw(nums, ops))
    return

if __name__ == "__main__":
    main()
