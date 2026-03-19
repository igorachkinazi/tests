#!/usr/bin/env python
import random

WORDS = ( "polish", "goldfish", "cough", "leather", "writer", "reason", "tomatoes", "vessel", "minute", "brother", "spring", "sister", "muscle", "wealth", "doctor", "throat", "attraction", "reaction", "giraffe" )

word = random.choice(WORDS)

tmp = word
jumble = ""

while tmp:
    position = random.randrange(len(tmp))
    jumble += tmp[position]
    tmp = tmp[:position] + tmp[position + 1:]
print ("Welcome to world jumble\n\nThe jumbled word is: ", end="")
print (jumble)

guess = input("\nYour guess: ")
while guess != word and guess != "":
    print ("Sorry, it is not it")
    guess = input("Your guess: ")
if(guess == word):
    print ("Congratulations!")
else:
    print ("Sorry, may be next time")

