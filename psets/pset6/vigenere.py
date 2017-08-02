#!/usr/bin/python3

import sys
import cs50
import math
from itertools import cycle

def main():
    if len(sys.argv) == 1 or len(sys.argv) > 2:
        print("Wrong number of parameters, one is expected!\n")
        return 1
    arg = sys.argv[1]
    temp = [ord(char) for char in arg]
    
    cipher_with = []
    for ascii in temp:
        if 65 <= ascii <= 90:
            cipher_with.append(ascii - 65)
        elif 97 <= ascii <= 122:
            cipher_with.append(ascii - 97)
        else:
            print("Keyword must only contain letters A-Z and a-z!")
            return False
    
    plaintext = input("plaintext: ")
    result = ""
    j = 0
    for i in range(len(plaintext)):
        ascii = ord(plaintext[i])
        if 65 <= ascii <= 90:
            ascii -= 65
            ascii += cipher_with[j % len(cipher_with)]
            ascii %= 26
            ascii += 65
            result += chr(ascii)
        elif 97 <= ascii <= 122:
            ascii -= 97
            ascii += cipher_with[j % len(cipher_with)]
            ascii %= 26
            ascii += 97
            result += chr(ascii)
        else:
            result += plaintext[i]
            continue
        j += 1

    print(result)
            
    



if __name__ == "__main__":
    main()