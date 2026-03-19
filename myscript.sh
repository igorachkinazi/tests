#!/bin/bash

# This is a sample Bash script demonstrating basic features.

# 1. Print a simple message
echo "Hello from your first Bash script!"

# 2. Use a variable
name="User"
echo "Welcome, $name!"

# 3. Get user input
echo -n "What is your favorite color? "
read color
echo "So, your favorite color is $color. That's interesting!"

# 4. Display current date and time
echo "Today's date and time: $(date)"

# 5. Perform a simple conditional check
number=1
if [ $number -gt 5 ]; then
  echo "The number $number is greater than 5."
else
  echo "The number $number is not greater than 5."
fi

