/**
 * Author: Shawn Hatchwell
 * Date: 2020-02-15
 * License: CC0
 * Source: 
 * Description: 
 * Time:
 */
#define LSB(i) ((i) & -(i)) // zeroes all the bits except the least significant one
int A[SIZE];
int sum(int i) // Returns the sum from index 1 to i{     
    int sum = 0;
    while (i > 0)
        sum += A[i], i -= LSB(i);
    return sum;}
void add(int i, int k) // Adds k to element with index i{
    while (i < SIZE)
        A[i] += k, i += LSB(i);} 