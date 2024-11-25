"""
Title: Object Oriented Programming Labtest

Program Description: 
This program takes a password from user and checks if it meets the following password requirements:
-Length >= 10
-At least one number, special character and uppercase letter
If password does not meet all these requirements the program suggests a version of their password that does meet the above requirements
This process continues until user enters 'exit'

Date: 15th October 2024

Author: Susanna Perkins

Grade: 100%
"""
import random
import string

#Part 1
def is_valid(pw):
    
    nums = "0123456789"
    specials = "!£$%^&*()-_+=|\\/<>[],.@;:"
    
    #Length at least 10
    if len(pw) >= 10:
        #At least one number
        for i in nums:
            if i in pw:
                #At least one uppercase
                if pw.lower() != pw:
                    #At least one special character
                    for i in specials:
                        if i in pw:
                            return True     
    return False

#Part 2
def strengthen_password(pw):
    random_char = random.choice(string.ascii_letters + string.digits)
    upper_case = random.choice(string.ascii_uppercase)
    digit = random.choice(string.digits)
    special_character = random.choice(string.punctuation)
  
    nums = "0123456789"
    specials = "!£$%^&*()-_+=|\\/<>[],.@;:"
  
    if_num = 0
    if_specials = 0
    
    if is_valid(pw):
        print("Password is valid")
        return pw
    else:
        #Length at least 10
        while len(pw) < 10:
            pw += random_char
        
        #At least one number
        for i in nums:
            if i in pw:
                if_num += 1
        if if_num == 0:
            pw += digit
                    
        #At least one uppercase
        if pw.lower() == pw:
            pw += upper_case
        
        #At least one special character
        for i in specials:
            if i in pw:
                if_specials += 1
        if if_specials == 0:
            pw += special_character   

    print("Password is not valid.")
    print("New suggested password:", pw)
    return pw


#Part 3, Main scope
password = str(input("Enter a password for evaluation (or type 'exit' to quit): "))

while password != 'exit':
    strengthen_password(password)
    password = str(input("Enter a password for evaluation (or type 'exit' to quit): "))
