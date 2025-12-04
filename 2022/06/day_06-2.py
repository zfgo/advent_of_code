def main():
    file_name = "input.txt"
    line = ""
    

    with open(file_name, 'r') as f:
        line = f.readline()
    
    for i in range(len(line)-14):
        tmp = set(line[i:i+4])
        tmp_2 = set(line[i:i+14])
        # len(tmp) == 4 and 
        if len(tmp_2) == 14:
            print(i+14)
            break


    
    

if __name__ == "__main__":
    main()
