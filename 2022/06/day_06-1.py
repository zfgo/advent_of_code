def main():
    file_name = "input.txt"
    line = ""
    

    with open(file_name, 'r') as f:
        line = f.readline()
    
    for i in range(len(line)-4):
        tmp = set(line[i:i+4])
        if len(tmp) == 4:
            print(i+4)
            break


    
    

if __name__ == "__main__":
    main()
