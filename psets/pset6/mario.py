#!/usr/bin/python3

import sys
import cs50

def main():
    while True:
        print("Height: ")
        row=cs50.get_int()
        if row>0 and row<23:
            break
    
    for i in range(row):
        for j in range(row):
            if j >= row - i - 1:
                print("#", end = "")
            else:
                print(" ", end = "")
        print("  ", end = "")
        for j in range(row):
            if j <= i:
                print("#", end = "")
            else:
                print(" ", end = "")
        print("\n", end = "")

if __name__ == "__main__":
    main()