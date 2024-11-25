/*
Title: Euclidean Algorithm

Description: Euclid's alg recursive function to calculate numbers' GCD

Date: 2nd Feb 2024

Author: Susanna Perkins
*/

#include <stdio.h>

// Function signatures
int gcd(int, int);

int main()
{
    int a,b,temp = 0;


    // Enter a and b
    printf("\nEnter value for a: ");
    scanf("%d", &a);
    printf("\nEnter value for b: ");
    scanf("%d", &b);

    // Data validation, ie a has to be bigger than b so swap if necessary
    if (a < b){
        temp = a;
        a = b;
        b = temp;
    }//end if

    printf("\nGCD of a and b: %d\n", gcd(a,b));
    
    return 0;

}//end main


int gcd(int n1, int n2)
{
    if (n2 == 0){
        return n1;
    }//end if

    else{
        return gcd(n2, n1 % n2);
    }//end else

}//end gcd function