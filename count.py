#!/usr/bin/env python

start = int(input("Enter first number: "))
end = int(input("Enter last number: "))
countby = int(input("Enter count by: "))

for i in range(start, end, countby):
    print (i,' ', end="")
print ("")

