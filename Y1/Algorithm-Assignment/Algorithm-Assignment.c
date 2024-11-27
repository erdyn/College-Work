/*
Title: Algorithms Assignment, tasks 1-4

Program Description: 
This program manages and processes simulated aeronautical company data by storing it in an array of structures.
It implements sorting algorithms with varying complexities to organize the data by different fields (such as issue codes or product IDs).
Additionally, a function is coded to copy all the sorted data into a single linked list, allowing efficient search algorithms to find specific issue codes or product IDs based on user input.

Date: April 2024

Author: Susanna Perkins

Grade: 100%
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Symbolic names
#define SIZE 11
#define UNIQUE_LINES 7
#define DESCRIPTION 100


// Structure templates

// Batch Date/Time
struct batchDateTime {
    int dayOfMonth;
    int hourOfDay;
    int minuteOfHour;
};

// Issue code and description
struct issue {
    int issueCode;
    char description[DESCRIPTION];
};

// Resolution code and description
struct resolution{
    int resolutionCode;
    char description[DESCRIPTION];
};

// Production Line
struct productionLine {
    int lineCode;
    int batchCode;
    struct batchDateTime date;
    int productId;
    struct issue issue;
    struct resolution solution;
    int employeeId;
};

// Task 2 linked list node
struct node {
    struct productionLine linkedlist;
    struct node *next;
};

// Funx signatures
void printProductionLine(struct productionLine[], int);


/*  Task1 Description:
The production line logs are in a random order for each day. Order each line in Product id, Issue code, date & time order.
There are huge amounts of data stored, the running time of this algorithm is O(NLog(N)). 
Sorting Algorithm used: Merge Sort
Display ordered data    */
// Task1 funxs
void task1(struct productionLine[], struct productionLine[], struct productionLine[], struct productionLine[]);
void prodIDmerge1(struct productionLine[], int, int);
void prodIDmerge(struct productionLine[], int, int, int);
void issuecodeSort(struct productionLine[]);
void issuecodeMergeSort(struct productionLine[], int, int);
void issuecodeMerge(struct productionLine[],int,int,int);
void datetimeSort(struct productionLine[]);
void datetimeMergeSort(struct productionLine[],int,int);
void datetimeMerge(struct productionLine[],int,int,int);
void printProductionLineProdIDIssueCodeDate(struct productionLine line[], int lineNum);


/*  Task2 Description:
Linked list to report issue codes by product Id and line Id for all production lines.
Time complexity of algorithm: O(N)
Display ordered data    */
// Task 2 funxs
struct node* structTolinkedList(struct productionLine[], struct productionLine[], struct productionLine[], struct productionLine[], int);
void task2(struct productionLine[], struct productionLine[], struct productionLine[], struct productionLine[]);
void printLink(struct node *);


/*  Task3 Description:
Search for the earliest occurrence of an issue code for a user-given product id across all production lines.
Time complexity of search algorithm: O(Log(N))
Algorithm used: Binary search   */
// Task 3 funxs
void task3(struct productionLine[], struct productionLine[], struct productionLine[], struct productionLine[]);
int binarySearch(struct productionLine[], int, int, int, int);
bool validInput(int, int *, int);


/*  Task4 Description:
Report which summarises the number of issues reported for a product across all production lines.
Time comlexity: O(N)   */
// Task 4 funxs
void task4(struct productionLine[], struct productionLine[], struct productionLine[], struct productionLine[]);
int* linearSearch(struct productionLine[], struct productionLine[], struct productionLine[], struct productionLine[], int, int, int[]);


int main() 
{
// Unordered sample test data for each production line
    struct productionLine line1[SIZE] =
    {
        {1, 10894, {10, 8, 30}, 20475, {3147, "Faulty component"}, {2147, "Replaced component"}, 5421},
        {1, 10173, {5, 15, 45}, 20314, {3276, "Assembly issue"}, {2276, "Reassembled product"}, 9876},
        {1, 10249, {15, 11, 20}, 20129, {3032, "Quality control failed"}, {2032, "Improved quality control process"}, 2345},
        {1, 10752, {25, 14, 10}, 20786, {3428, "Packaging error"}, {2428, "Repackaged product"}, 8765},
        {1, 10618, {18, 10, 55}, 20651, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {1, 10509, {9, 12, 40}, 20937, {3210, "Delayed delivery"}, {2210, "Expedited delivery"}, 4389},
        {1, 10987, {20, 9, 5}, 20802, {3856, "Incorrect labeling"}, {2856, "Corrected labeling"}, 6234},
        //duplicates
        {1, 10173, {6, 15, 45}, 20314, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 9876},
        {1, 10618, {18, 10, 55}, 20802, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {1, 10987, {19, 10, 20}, 20802, {3856, "Incorrect labeling"}, {2856, "Corrected labeling"}, 6234},
        {1, 10894, {7, 8, 31}, 20314, {3147, "Faulty component"}, {2147, "Replaced component"}, 5421}
    };//line1


    struct productionLine line2[SIZE] =
    {
        {2, 10249, {15, 11, 20}, 20475, {3147, "Faulty component"}, {2147, "Replaced component"}, 5421},
        {2, 10894, {7, 8, 31}, 20937, {3276, "Assembly issue"}, {2276, "Reassembled product"}, 8765},
        {2, 10173, {20, 12, 40}, 20786, {3032, "Quality control failed"}, {2032, "Improved quality control process"}, 8765},
        {2, 10987, {6, 12, 40}, 20651, {3428, "Packaging error"}, {2428, "Repackaged product"}, 8765},
        {2, 10509, {10, 14, 10}, 20802, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {2, 10173, {25, 15, 45}, 20314, {3147, "Faulty component"}, {2147, "Replaced component"}, 9876},
        {2, 10618, {18, 10, 55}, 20314, {3210, "Delayed delivery"}, {2210, "Expedited delivery"}, 4389},
        //duplicates with modifications
        {2, 10618, {18, 10, 55}, 20802, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {2, 10987, {19, 9, 5}, 20314, {3856, "Incorrect labeling"}, {2856, "Corrected labeling"}, 6234},
        {2, 10618, {20, 12, 40}, 20475, {3210, "Delayed delivery"}, {2210, "Expedited delivery"}, 4389},
        {2, 10752, {15, 11, 20}, 20129, {3856, "Incorrect labeling"}, {2856, "Corrected labeling"}, 6234}
    };//line2


    struct productionLine line3[SIZE] =
    {
        {3, 10987, {6, 12, 40}, 20802, {3428, "Packaging error"}, {2428, "Repackaged product"}, 8765},
        {3, 10509, {10, 14, 10}, 20937, {3032, "Quality control failed"}, {2032, "Improved quality control process"}, 8765},
        {3, 10173, {20, 12, 40}, 20314, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {3, 10894, {7, 8, 31}, 20475, {3147, "Faulty component"}, {2147, "Replaced component"}, 5421},
        {3, 10618, {18, 10, 55}, 20314, {3210, "Delayed delivery"}, {2210, "Expedited delivery"}, 4389},
        {3, 10173, {25, 15, 45}, 20786, {3147, "Faulty component"}, {2147, "Replaced component"}, 9876},
        {3, 10249, {15, 11, 20}, 20651, {3276, "Assembly issue"}, {2276, "Reassembled product"}, 8765},
        //duplicates with modifications
        {3, 10618, {18, 11, 56}, 20314, {3210, "Delayed delivery"}, {2210, "Expedited delivery"}, 4389},
        {3, 10987, {19, 9, 5}, 20802, {3856, "Incorrect labeling"}, {2856, "Corrected labeling"}, 6234},
        {3, 10618, {20, 12, 48}, 20314, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {3, 10752, {15, 11, 20}, 20129, {3276, "Assembly issue"}, {2276, "Reassembled product"}, 6234}
    };//line3


    struct productionLine line4[SIZE] =
    {
        {4, 10618, {18, 10, 55}, 20651, {3032, "Quality control failed"}, {2032, "Improved quality control process"}, 8765},
        {4, 10173, {20, 12, 40}, 20314, {3276, "Assembly issue"}, {2276, "Reassembled product"}, 8765},
        {4, 10894, {7, 8, 31}, 20475, {3428, "Packaging error"}, {2428, "Repackaged product"}, 8765},
        {4, 10987, {6, 12, 40}, 20937, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {4, 10509, {10, 14, 10}, 20786, {3147, "Faulty component"}, {2147, "Replaced component"}, 5421},
        {4, 10249, {15, 11, 20}, 20314, {3856, "Incorrect labeling"}, {2856, "Corrected labeling"}, 6234},
        {4, 10173, {25, 15, 45}, 20786, {3210, "Delayed delivery"}, {2210, "Expedited delivery"}, 4389},
        //duplicates with changes
        {4, 10987, {19, 9, 5}, 20802, {3965, "Shipping issue"}, {2965, "Reshipped product"}, 8765},
        {4, 10618, {20, 13, 40}, 20314, {3276, "Assembly issue"}, {2276, "Reassembled product"}, 8765},
        {4, 10894, {6, 8, 31}, 20314, {3147, "Faulty component"}, {2147, "Replaced component"}, 5421},
        {4, 10752, {15, 11, 20}, 20129, {3032, "Quality control failed"}, {2032, "Improved quality control process"}, 8765}
    };//line4


    // Print unordered production lines
    printProductionLine(line1, 1);
    printProductionLine(line2, 2);
    printProductionLine(line3, 3);
    printProductionLine(line4, 4);

    // Call task 1
    task1(line1, line2, line3, line4);

    // Call task 2
    task2(line1, line2, line3, line4);

    // Call task 3
    task3(line1, line2, line3, line4);

    // Call task 4
    task4(line1, line2, line3, line4);

    return 0;
}//end main


// Displays production line
void printProductionLine(struct productionLine line[], int lineNum) 
{
    printf("\n\n\nProduction Line %d:\n\n", lineNum);
    printf("Batch Code:\tDate:  Time:\tProductID:   IssueCode: Issue Description:\t  ResolutionCode:\tResolution Description:\t\tEmployeeID:");
    printf("\n---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t\t", line[i].batchCode);
        printf("%d\t%d:%d\t", line[i].date.dayOfMonth, line[i].date.hourOfDay, line[i].date.minuteOfHour);
        printf("%d\t\t", line[i].productId);
        printf("%d\t", line[i].issue.issueCode);
        printf("%-23s\t\t", line[i].issue.description);
        printf("%d\t", line[i].solution.resolutionCode);
        printf("\t%-32s  ", line[i].solution.description);
        printf("%d\n", line[i].employeeId);
    }

}//end display product line funx


// Task1
void task1(struct productionLine line1[], struct productionLine line2[], struct productionLine line3[], struct productionLine line4[])
{

    printf("\n\n\nTask 1: ");
    printf("\nEach production line ordered by Product id, Issue code, date & time order");

    // Sort line 1
    prodIDmerge1(line1, 0, SIZE - 1);
    datetimeSort(line1);
    issuecodeSort(line1);

    // Sort line 2
    prodIDmerge1(line2, 0, SIZE - 1);
    datetimeSort(line2);
    issuecodeSort(line2);

    // Sort line 3
    prodIDmerge1(line3, 0, SIZE - 1);
    datetimeSort(line3);
    issuecodeSort(line3);

    // Sort line 4
    prodIDmerge1(line4, 0, SIZE - 1);
    datetimeSort(line4);
    issuecodeSort(line4);

    // Dislay sorted lines
    printProductionLineProdIDIssueCodeDate(line1, 1);
    printProductionLineProdIDIssueCodeDate(line2, 2);    
    printProductionLineProdIDIssueCodeDate(line3, 3);
    printProductionLineProdIDIssueCodeDate(line4, 4);

}//end task 1


// Merge sort product ID
void prodIDmerge1(struct productionLine line[], int l, int h)
{
    int mid = 0;

    if(l >= h){
        return;
    }
    else{
        mid = (l + h)/2;
        prodIDmerge1(line, l, mid );
        prodIDmerge1(line, mid+1, h);
        prodIDmerge(line, l, mid, h);
    }

}//end prodIDmerge1


// Merge part of sort for product ID
void prodIDmerge(struct productionLine line[], int l, int m, int h)
{
    struct productionLine tempstruct[SIZE];
    int i;
    int left = l;
    int right = m + 1;
    int t = left;
    while(left <= m && right <=h){
        if(line[left].productId <= line[right].productId){
            tempstruct[t++] = line[left++];
        }
        else{
            tempstruct[t++] = line[right++];
        }
    }
    if(left>m){
        while(right <= h){
            tempstruct[t++] = line[right++];
        }
    }
    else{
        while(left <= m){
            tempstruct[t++] = line[left++];
        }
    }

    for(i = l; i <= h; i++){
        line[i] = tempstruct[i];
    }

}//end prodIDmerge


// Find duplicates for sorting by issue code after precedence of product ID
void issuecodeSort(struct productionLine line[])
{

    int start = 0;
    int end = 0;
    int curr = 0;
    int i;
    for(i=0;i<SIZE;i++)
    {
        start = i;
        curr = i;
        while(line[curr].productId == line[i].productId)
        {
            i++;
        }
        i--;
        end = i;
        if (end > start)
        {
            issuecodeMergeSort(line, start, end);
        }
    }

}//end issuecodeSort


// Merge sort issuecodes
void issuecodeMergeSort(struct productionLine line[], int low, int high)
{

    int mid = 0;
    if(low >= high)
    {
        return;
    }
    else
    {
        mid = (low+high)/2;
        issuecodeMergeSort(line, low, mid);
        issuecodeMergeSort(line, mid +1, high);
        issuecodeMerge(line, low, mid, high);
    }

}//end issuecodeMergeSort


// Merge part of sort for issue code
void issuecodeMerge(struct productionLine line[],int low ,int mid ,int high)
{

    struct productionLine tempstruct[SIZE];
    int i, j, t;
    i = low; // i is left
    j = mid + 1; // j is right
    t = i; // t is temp variable
    while (i <= mid && j <= high)
    {
        if (line[i].issue.issueCode<= line[j].issue.issueCode)
        {
            tempstruct[t++] = line[i++];
        }
        else
        {
            tempstruct[t++] = line[j++];
        }
    }
    if (i > mid)
    {
        while (j <= high)
        {
            tempstruct[t++] = line[j++];
        }
    }
    else
    {
        while (i <= mid)
        {
            tempstruct[t++] = line[i++];
        }
    }
    for (i = low; i <= high; i++)
    {
        line[i] = tempstruct[i];
    }

}//end issuecodeMerge


// Find duplicates for sorting by batchDateTime after precedence of product ID and issue code
void datetimeSort(struct productionLine line[])
{
    
    int start = 0;
    int end = 0;
    int curr = 0;
    int i;
    for(i=0;i<SIZE;i++)
    {
        start = i;
        curr = i;
        while(line[curr].productId == line[i].productId)
        {
            i++;
        }
        i--;
        end = i;
        if (end > start)
        {
            datetimeMergeSort(line, start, end);
        }
    } 

}//end datetimeSort


// Merge sort batchdateTime
void datetimeMergeSort(struct productionLine line[], int low, int high)
{
    
    int mid = 0;
    if(low >= high)
    {
        return;
    }
    else
    {
        mid = (low+high)/2;
        datetimeMergeSort(line, low, mid);
        datetimeMergeSort(line, mid +1, high);
        datetimeMerge(line, low, mid, high);
    }

}//end datetimeMergeSort


// Merge part of sort for batchDateTime
void datetimeMerge(struct productionLine line[], int low, int mid, int high)
{
    
    struct productionLine tempstruct[SIZE];
    int i, j, t;
    i = low; // i is left
    j = mid + 1; // j is right
    t = i; // t is temp

    while (i <= mid && j <= high)
    {
        if (line[i].date.dayOfMonth<= line[j].date.dayOfMonth)
        {
            tempstruct[t++] = line[i++];
        }
        else if(line[i].date.dayOfMonth>= line[j].date.dayOfMonth)
        {
            tempstruct[t++] = line[j++];
        }
        else
        {
            if (line[i].date.hourOfDay<= line[j].date.hourOfDay)
            {
                tempstruct[t++] = line[i++];
            }
            else if(line[i].date.hourOfDay>= line[j].date.hourOfDay)
            {
                tempstruct[t++] = line[j++];
            }
            else
            {
            
                if (line[i].date.minuteOfHour<= line[j].date.minuteOfHour)
                {
                    tempstruct[t++] = line[i++];
                }
                else if(line[i].date.minuteOfHour>= line[j].date.minuteOfHour)
                {
                    tempstruct[t++] = line[j++];
                }
            }
        }
    }
    if (i > mid)
    {
        while (j <= high)
        {
            tempstruct[t++] = line[j++];
        }
    }
    else
    {
        while (i <= mid)
        {
            tempstruct[t++] = line[i++];
        }
    }
    for (i = low; i <= high; i++)
    {
        line[i] = tempstruct[i];
    }

}//end datetimeMerge


// Print task1's sorted values
void printProductionLineProdIDIssueCodeDate(struct productionLine line[], int lineNum) 
{
    printf("\n\nProduction Line %d:\n\n", lineNum);
    printf("ProductID:\tIssueCode:\tDate:  Time:");
    printf("\n----------------------------------------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t\t", line[i].productId);
        printf("%d\t\t", line[i].issue.issueCode);
        printf("%d\t%d:%d\n", line[i].date.dayOfMonth, line[i].date.hourOfDay, line[i].date.minuteOfHour);
    }

}//end display product line funx



// Task 2
void task2( struct productionLine line1[], struct productionLine line2[], struct productionLine line3[], struct productionLine line4[])
{
    struct node *head = NULL;
    // Converting all data to single linked list
    head = structTolinkedList(line1, line2, line3, line4, SIZE);
    printf("\n\n\nTask 2:");
    printf("\nLinked list to report issue codes by product Id and line Id for all production lines");
    printLink(head);

}//end task2


// Copying the ordered structures to a linked list
struct node* structTolinkedList(struct productionLine line1[], struct productionLine line2[], struct productionLine line3[], struct productionLine line4[], int n)
{
  struct node *head = NULL;
  struct node *temp = NULL;

  // Copying line 1's values
  for (int i = 0; i < SIZE; i++) {
    if (head == NULL) {
      head = (struct node *)malloc(sizeof(struct node));
      head->linkedlist = line1[i];
      head->next = NULL;
      temp = head;
    } else {
      temp->next = (struct node *)malloc(sizeof(struct node));
      temp = temp->next;
      temp->linkedlist = line1[i];
      temp->next = NULL;
    }
  }//end line1

  // Copying line 2's values
  for (int i = 0; i < SIZE; i++) {
    if (head == NULL) {
      head = (struct node *)malloc(sizeof(struct node));
      head->linkedlist = line2[i];
      head->next = NULL;
      temp = head;
    } else {
      temp->next = (struct node *)malloc(sizeof(struct node));
      temp = temp->next;
      temp->linkedlist = line2[i];
      temp->next = NULL;
    }
  }//end line2

  // Copying line 3's values
  for (int i = 0; i < SIZE; i++) {
    if (head == NULL) {
      head = (struct node *)malloc(sizeof(struct node));
      head->linkedlist = line3[i];
      head->next = NULL;
      temp = head;
    } else {
      temp->next = (struct node *)malloc(sizeof(struct node));
      temp = temp->next;
      temp->linkedlist = line3[i];
      temp->next = NULL;
    }
  }//end line3

  // Copying line 4's values
  for (int i = 0; i < SIZE; i++) {
    if (head == NULL) {
      head = (struct node *)malloc(sizeof(struct node));
      head->linkedlist = line4[i];
      head->next = NULL;
      temp = head;
    } else {
      temp->next = (struct node *)malloc(sizeof(struct node));
      temp = temp->next;
      temp->linkedlist = line4[i];
      temp->next = NULL;
    }
  }//end line4

  return head;

}//end structTolinkedList


// Display linked list
void printLink(struct node *head)
{
    if (head == NULL){
        printf("\nLinked list is empty");
    }
    struct node *ptr = NULL;
    ptr = head;
    printf("\n\nProduction Lines:\n\n");
    printf("Line ID | ProductID | Issue Code");
    printf("\n--------------------------------");
  
    while(ptr!= NULL){
        printf("\n%d\t   %d\t %d", ptr->linkedlist.lineCode, ptr->linkedlist.productId, ptr->linkedlist.issue.issueCode);
        ptr = ptr -> next;
    }

}//end print link



// Task 3
void task3(struct productionLine line1[], struct productionLine line2[], struct productionLine line3[], struct productionLine line4[])
{
    struct productionLine tempstruct[4];
    int pID = 0;
    int iC = 0;
    int low = 0;
    int high = SIZE - 1;
    int result = 0;
    int occurences = 0;
    int results[44];
    int pIDs[UNIQUE_LINES] = {20475, 20314, 20129, 20786, 20651, 20937, 20802};
    int iCs[UNIQUE_LINES] = {3147, 3276, 3032, 3428, 3965, 3210, 3856};

    printf("\n\n\nTask 3\n");
    printf("Search for the earliest occurrence of an issue code for a given product id across all production lines.\n");

    printf("\n\nSample ProductIDs:\n 20475\n 20314\n 20129\n 20786\n 20651\n 20937\n 20802");
    printf("\nWhat productID do you want to search for?\n");
    scanf("%d", &pID);
    // Check if user entered an actual Product ID
    while (!validInput(pID, pIDs, SIZE)) {
        printf("\nInvalid product ID. Please enter a valid one:\n");
        scanf("%d", &pID);
    }


    printf("\n\nSample Issue Codes:\n 3147\tFaulty component\n 3276\tAssembly issue\n 3032\tQuality control failed\n 3428\tPackaging error\n 3965\tShipping issue\n 3210\tDelayed delivery\n 3856\tIncorrect labeling");
    printf("\nWhat issue code do you want to search for?\n");
    scanf("%d", &iC);
    // Check if user entered an actual Issue Code
    while (!validInput(iC, iCs, SIZE)) {
        printf("\nInvalid issue code. Please enter a valid one:\n");
        scanf("%d", &iC);
    }


    // Search for product id and then corresponding issue code, return values


    // Line 1
    // Call binary Search function
    result = binarySearch(line1, low, high, pID, iC);

    // Display result
    if (result == -1) // Target not found within array
    {
        printf("\nThe combination you are looking for does not exist in production line 1.\n");
    }
    else // Position of target found
    {
        tempstruct[occurences] = line1[result];
        results[occurences] = result;
        occurences ++;
    }


    // Line 2 search
    result = binarySearch(line2, low, high, pID, iC);

    // Display result
    if (result == -1) // Target not found within array
    {
        printf("\nThe combination you are looking for does not exist in production line 2.\n");
    }
    else // Position of target found
    {
        tempstruct[occurences] = line2[result];
        results[occurences] = result;
        occurences ++;
    }


    // Line 3 search
    result = binarySearch(line3, low, high, pID, iC);

    // Display result
    if (result == -1) // Target not found within array
    {
        printf("\nThe combination you are looking for does not exist in production line 3.\n");
    }
    else // Position of target found
    {
        tempstruct[occurences] = line3[result];
        results[occurences] = result;
        occurences ++;
    }


    // Line 4 search
    result = binarySearch(line4, low, high, pID, iC);

    // Display result
    if (result == -1) // Target not found within array
    {
        printf("\nThe combination you are looking for does not exist in production line 4.\n");
    }
    else // Position of target found
    {
        tempstruct[occurences] = line4[result];
        results[occurences] = result;
        occurences ++;
    }

    // Display the fisrt occurence
    result = binarySearch(tempstruct, low, occurences, pID, iC);
    if(result != -1)
    {
        //display line that has the occurence
        printf("\n\n\nFirst Occurence of productID: %d and issue code: %d\n\n", pID, iC);
        printf("Productionline \tProductID:\tIssueCode:\tDate:  Time:");
        printf("\n-------------------------------------------------------------\n");
        printf("%d\t\t", tempstruct[0].lineCode);
        printf("%d\t\t", tempstruct[0].productId);
        printf("%d\t\t", tempstruct[0].issue.issueCode);
        printf("%d\t%d:%d\n", tempstruct[0].date.dayOfMonth, tempstruct[0].date.hourOfDay, tempstruct[0].date.minuteOfHour);
    }

}//end task 3


// Binary search + checking for first occurence after finding target
int binarySearch(struct productionLine line[], int low, int high, int productID, int IC)
{
    int mid = 0;

    // If this case occurs, this means that the target number does not exist within the array
    if (low > high)
    {
        // Returning -1 just indicates that the number was not found in the if statement within the int main().
        return -1;
    } 
    else
    {
        mid = (low + high) / 2; 

        // Target found
        if (line[mid].productId == productID && line[mid].issue.issueCode == IC)
        { 
            return mid;
        }
        // Target is less than the mid
        else if (productID < line[mid].productId || (line[mid].productId == productID && line[mid].issue.issueCode < IC))
        {
            return binarySearch(line, low, mid - 1, productID, IC);
        }
        // Target is greater than the mid
        else 
        {
            return binarySearch(line, mid + 1, high, productID, IC);
        }
    }

}//end binarySearch()

// Function to check if a value exists in an array
bool validInput(int value, int *array, int size) 
{
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return true;
        }
    }
    return false;
}//end validInput


// Task 4
void task4(struct productionLine line1[], struct productionLine line2[], struct productionLine line3[], struct productionLine line4[])
{
    int arr_20129[UNIQUE_LINES];
    int arr_20314[UNIQUE_LINES];
    int arr_20475[UNIQUE_LINES];
    int arr_20651[UNIQUE_LINES];
    int arr_20786[UNIQUE_LINES];
    int arr_20802[UNIQUE_LINES];
    int arr_20937[UNIQUE_LINES];

    int* counts[UNIQUE_LINES] = {arr_20129, arr_20314, arr_20475, arr_20651, arr_20786, arr_20802, arr_20937};

    int arrOfProdIDs[] = {20129, 20314, 20475, 20651, 20786, 20802, 20937};
    int issueCodeIndexMap[UNIQUE_LINES] = {3032, 3147, 3210, 3276, 3428, 3856, 3965};
    int total;


    for (int i = 0; i < UNIQUE_LINES; i++){
        counts[i] = linearSearch(line1, line2, line3, line4, arrOfProdIDs[i], SIZE, issueCodeIndexMap);
    }

    printf("\n\n\nTask 4");
    printf("\nIssues reported on products over all production lines:\n");
    printf("\nIssue Codes     |\t3032\t3147\t3210\t3276\t3428\t3856\t3965\tTotal Issues\n");
    printf("----------------------------------------------------------------------------------------------\n");
    // Display product Ids and their recorded issue codes across the production lines
    for (int i = 0; i < UNIQUE_LINES; i++) {
        total = 0;
        printf("Product ID %d: ", arrOfProdIDs[i]);
        for (int j = 0; j < UNIQUE_LINES; j++) {
            printf("\t%d ", counts[i][j]);
            total += counts[i][j];
        }
        printf("\t   %d\n", total);
    }



}//end task 4

// Linear search to find and count issue codes across product ids
int* linearSearch(struct productionLine line1[], struct productionLine line2[], struct productionLine line3[], struct productionLine line4[], int prodID, int N, int issueCodeIndexMap[])
{

    int* issueCodesPresence = (int *)calloc(UNIQUE_LINES, sizeof(int));


    // Line 1
    for (int i = 0; i < N; i++) {
        if (line1[i].productId == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line1[i].issue.issueCode == issueCodeIndexMap[j]) {
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }


    // Line 2
    for (int i = 0; i < N; i++) {
        if (line2[i].productId == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line2[i].issue.issueCode == issueCodeIndexMap[j]) {
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }


    // Line 3
    for (int i = 0; i < N; i++) {
        if (line3[i].productId == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line3[i].issue.issueCode == issueCodeIndexMap[j]) {
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }


    // Line 4
    for (int i = 0; i < N; i++) {
        if (line4[i].productId == prodID) {
            for (int j = 0; j < 7; j++) {
                if (line4[i].issue.issueCode == issueCodeIndexMap[j]) {
                    issueCodesPresence[j]++;
                    break;
                }
            }
        }
    }


    return issueCodesPresence;
}//end linear search
