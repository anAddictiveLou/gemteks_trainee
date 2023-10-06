#!/bin/bash

# Read the number of integers (N) from the user
read n

# Read the array of integers (space-separated) from the user
read -a arr

# Initialize an associative array to store the frequency of each integer
declare -A freq_occur

# Count the frequency of each integer in the array
for num in "${arr[@]}"; do
    if [ -n "${freq_occur[$num]}" ]; then
        freq_occur[$num]=$((freq_occur[$num] + 1))
    else
        freq_occur[$num]=1
    fi
done

# Find the number that occurs only once
for num in "${arr[@]}"; do
    if [ ${freq_occur[$num]} -eq 1 ]; then
        echo "$num"
        exit
    fi
done
