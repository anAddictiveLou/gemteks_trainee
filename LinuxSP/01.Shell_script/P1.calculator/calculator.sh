#!/bin/bash

# Check if the correct number of arguments are provided
if [ $# -ne 3 ]; then
  echo "Usage: $0 <num1> <operator> <num2>"
  exit 1
fi

num1="$1"
operator="$2"
num2="$3"

# Perform the arithmetic operation based on the operator
case "$operator" in
  "+")
    result=$((num1 + num2))
    echo "Result: $result"
    ;;
  "-")
    result=$((num1 - num2))
    echo "Result: $result"
    ;;
  "*")
    result=$((num1 * num2))
    echo "Result: $result"
    ;;
  "/")
    if [ $num2 -eq 0 ]; then
      echo "Error: Division by zero is not allowed."
    else
      result=$(awk "BEGIN {printf \"%.2f\", $num1 / $num2}")
      echo "$result"
    fi
    ;;
  *)
    echo "Invalid operator. Please use +, -, *, or /."
    exit 1
    ;;
esac
