#!/usr/bin/python3

import sys
import cs50
import math

def main():
    novci = [25, 10, 5, 1]
    fchange = -1
    i = 0
    
    print("O hai(o)")
    while(fchange < 0):
        fchange =  float(input("How much change is owed?\n"))
    ichange = round(fchange * 100)
    money = 0
    while(ichange > 0):
        if ichange - novci[i] < 0:
            i = i + 1
        else:
            ichange -= novci[i]
            money = money + 1
    print(money)
            
        
if __name__ == "__main__":
    main()