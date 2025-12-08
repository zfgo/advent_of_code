def math_hw(nums, ops):
    score = 0
    problem = 0

    for i in range(len(nums[0])):
        if ops[i] == '*':
            problem = 1
            for j in range(4):
                problem *= nums[j][i]
            score += problem

        if ops[i] == '+':
            problem = 0
            for j in range(4):
                problem += nums[j][i]
            score += problem

    return score

def main():
    fstr = "input.txt"
    lines = []

    with open(fstr, 'r') as f:
        lines = f.readlines()

    # parse the input
    nums = []
    ops = []
    for i, line in enumerate(lines):
        if i == len(lines) - 1:
            ops = line.split()
            break
        nl = line.split()
        for j, n in enumerate(nl):
            nl[j] = int(n)
        nums.append(nl)

    print("Math HW answer: ", math_hw(nums, ops))
    return

if __name__ == "__main__":
    main()
