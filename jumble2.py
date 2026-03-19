#!/usr/bin/env python
import random

WORDS =  ("polish", "goldfish", "cough", "leather", "writer", 
          "reason", "tomatoes", "vessel", "minute", 
          "brother", "spring", "sister", "muscle", "wealth", 
          "doctor",  "throat", "attraction", "reaction", "giraffe")

HINTS =  ("surface smoother", "house fish", "ill symptom", 
          "material", "author", "explanation", 
          "vegetables", "boat", "time",
          "relative", "season", "relative", 
          "body tissue", "a lot of money", "physician", 
          "body part", "interesting place", "response", "animal") 

index = random.randrange(len(WORDS))
word = WORDS[index]

jumble = ""

while word:
    position = random.randrange(len(word))
    jumble += word[position]
    word = word[:position] + word[position + 1:]

score = 0
print ("Welcome to world jumble!\n\nThe jumbled word is: ", end="")
print (jumble)

guess = input("\nYour guess: ")
while guess != WORDS[index] and guess != "":
    if(guess == "hint"):
        print (HINTS[index])
        guess = input("Your guess: ")
        score += 10
        continue
    print ("Sorry, it is not it")
    score += 1
    guess = input("Your guess: ")

if(guess == WORDS[index]):
    print ("Congratulations! Your score is ", score, " (less is better)")
else:
    print ("Sorry, may be next time")

