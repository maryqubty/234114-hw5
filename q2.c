/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define LEX 1
#define LET_DIVER 2
#define MAX_LEN 20
#define letters_num ('Z'-'A')+1
#define Str1_char (1)
#define Str2_char (-1)

int CompareStrings(char* str1, char* str2, int rule);
void SortStrings(char* str_arr[], int n, int rule);

char upCase(char c);
int insensitive_compare(char *str1, char *str2);
void fill_zero_array(int letter_array[]);
void fill_array_with_letter_num(int array[] , char *str );
int check_array(int array[] );
void swap(char * str1 ,char * str2);
int strlen1(char * array);
void delete_malloc(char *str_arr[],int n);
void copy_arr(char * string_arr ,char * check);



// Print Functions' Declarations
void PrintNumStringsInputMessage();
void PrintStringsInputMessage(int n);
void PrintRuleOfComparisonInputMessage();
void PrintSortedStrings(char* str_arr[], int n);
void PrintAllocationError();



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
 /* this is the main function it fills the array with pointers to strings
 and calls the other functions in order to sort the
 strings and prints the string in a sorted way */
int main()
{
    PrintNumStringsInputMessage();
    int n;
    scanf("%d",&n);

    char * * str_arr =(char**)malloc((n+1)*sizeof(char*));
    if(str_arr==NULL){
            PrintAllocationError();
            return 0;
                     }

    PrintStringsInputMessage(n);

    char string_arr[MAX_LEN];
    for(int i=0;i<n;i++)
    {
        scanf("%s",string_arr);
        int size=strlen1(string_arr);

        char *check=(char *)malloc((size+1)*sizeof(char));
        if(check==NULL){
            PrintAllocationError();
            return 0;
                     }

         copy_arr(string_arr,check);
         check[size]=0;

         str_arr[i]=check;
    }

    PrintRuleOfComparisonInputMessage();
    int rule ;
    scanf("%d",&rule);

    SortStrings(str_arr,n,rule);

    PrintSortedStrings(str_arr, n);

    delete_malloc(str_arr,n);


    return 0;
}
/////////////////////////////////////////////////////
/*this function gets an array and frees it */
void delete_malloc(char *str_arr[],int n)
{

for(int i=0;i<n;i++)
{
    free(str_arr[i]);
}
free(str_arr);
}

/////////////////////////////////////////////////////
/*this function copies an array into another */
void copy_arr(char * string_arr ,char * check)
{
    while(*string_arr)
    {
        *check=*string_arr ;
        check++;
        string_arr++;
    }
}
int strlen1(char * array)
{
    int i=0;
    while(*array)
    {
        i++;
        array++;
    }
    return i;
}
/*this function compares between strings according to what the user chooses ,
 it returns a positive num if the first string is
 bigger than the second , negative num if smaller and 0 if they are the same */
int CompareStrings(char* str1, char* str2, int rule)
{

if(rule==LEX)
{
    return insensitive_compare(str1,str2);
}

else
{
   int letter_array1[letters_num];
   int letter_array2[letters_num];
   fill_zero_array(letter_array1);
   fill_zero_array(letter_array2);

   fill_array_with_letter_num(letter_array1 ,str1 );
   fill_array_with_letter_num(letter_array2 ,str2 );

   return (check_array(letter_array1)-check_array(letter_array2));
}

}
//////////////////////////////////////////////////////////////////
/*this function checks if the letter was already in the string , if not it adds it's character */
 void fill_array_with_letter_num(int array[] , char *str )
 {
 while(*str)
   {
        char letter=upCase(*str);

       if(letter>= 'A' && letter<= 'Z')
       {
           int index= (int)letter - (int)'A';
        /*   if(array[index]==0){array[index]=str_char ;}
           else
           if(array[index]!=str_char){array[index]=0 ;}
            */
            array[index]++;
       }
       str++;

   }

 }


///////////////////////////////////////////////////////////
/*this function returns the difference in num of letters in the two strings */
int check_array(int array[] )
{
    int counter1=0 ;
   /* int counter2=0;
    for(int i=0; i<letters_num ; i++)
    {
       if(array[i]!=0)
       {
           (array[i]>0)?counter1++:counter2++;
       }
    }
    return counter1-counter2;
    */
    for(int i=0; i<letters_num ; i++)
    {
       if(array[i]!=0) counter1++;
    }
    return counter1;
}
//////////////////////////////////////////////////////////////////
/*this function fills the array with zeros */
void fill_zero_array(int letter_array[])
{
    for(int i=0;i<letters_num;i++)
    {
     letter_array[i]=0;
    }
}
//////////////////////////////////////////////////////////////////
/*this function turns the small letter to capital letter */
char upCase(char c)
 {
if (c >= 'a' && c <= 'z')
    {
return c - 'a' + 'A';
    }
return c;
 }

//////////////////////////////////////////////////////////////////
/*this function compares between strings in insensitive way */
int insensitive_compare(char *str1, char *str2)
{
    while (*str1 && *str2 && (upCase(*str1)== upCase(*str2)) ){
        str1++;
        str2++;
    }
    return ((int)(upCase(*str1)) - (int)(upCase(*str2)));
}

/////////////////////////////////////////////////////////////////
/*this function swaps between strings */
void swap(char * str1 ,char * str2)
{
     int size1=strlen1(str1);
     int size2=strlen1(str2);

    char helper[MAX_LEN];
    copy_arr(str1,helper);
    helper[size1]=0;
    copy_arr(str2,str1);
    str1[size2]=0;
    copy_arr(helper,str2);
    str2[size1]=0;

}
/////////////////////////////////////////////////////////////////
/*this function sorts strings according to which is bigger in the chosen way */
void SortStrings(char* str_arr[], int n, int rule)
{
    if(n==1)return ;

    char ** pointer1=str_arr;
    int i=1;
      while(i<n)
      { ///////////////
          if(CompareStrings(*(pointer1),*(pointer1+1),rule)<=0 )
          {
              pointer1++;
              i++;
          }
          else
          {
              int k=i;
              while(k!=0)
              {
                  if(CompareStrings(str_arr[k-1],str_arr[k],rule)>0)
                     {
                         swap(str_arr[k],str_arr[k-1]);
                            k--;
                     }
                  else {k=0;}
              }
          }


      }

}

// Print Functions
void PrintNumStringsInputMessage()
{
    printf("Please enter the number of strings:\n");
}

void PrintStringsInputMessage(int n)
{
    printf("Please enter the %d strings:\n", n);
}

void PrintRuleOfComparisonInputMessage()
{
    printf("Please enter the rule of comparison between strings.\n");
    printf("%d: Lexicographic order.\n", LEX);
    printf("%d: By the diversity of letters.\n", LET_DIVER);
}

void PrintSortedStrings(char* str_arr[], int n)
{
    printf("The sorted strings are:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s\n", str_arr[i]);
    }
}

void PrintAllocationError()
{
    printf("ERROR: allocation failed.\n");
}
