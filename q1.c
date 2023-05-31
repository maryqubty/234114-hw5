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
#define N 4
#define NO_ROAD -1
#define NO_PATH -1

int ShortestFullPath(int roads[N][N]);

// Print functions declarations
void PrintRoadsInputMessage();
void PrintLenOfShortestFullPath(int min_len);
void zero_fill_board(int places[N]);
int get_shortest_path(int roads[N][N] , int lengh ,int i , int j, int places[N]);
int ShortestFullPath(int roads[N][N]);
int visited_all_places(int places[N]);
int get_lowest_num(int value[N]);


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
 /*the main function fills the matrix and prints the shortest road */
int main()
{
     PrintRoadsInputMessage();
    int roads[N][N];

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        scanf("%d",&roads[i][j]);

    int min_len=ShortestFullPath(roads);

   PrintLenOfShortestFullPath(min_len);

    return 0;
}

/*this function fills the array with a start value (0) */
void zero_fill_board(int places[N])
{
   for(int i=0; i<N ; i++)
   {
       places[i]=0;
   }
}
/*this function calls another function to get the shortest road */
int ShortestFullPath(int roads[N][N])
{
    int lengh=0;
    int places[N];
    int index=0;
    zero_fill_board(places);
    lengh = get_shortest_path(roads,lengh ,index,index,places);

    return lengh;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/*this function works in a backtracking way, it gets the lenght of the roads and returns the shortest one  */
int get_shortest_path(int roads[N][N] , int lengh ,int i , int j,int places[N])
{
    lengh+=roads[i][j];
    if(roads[i][j]== NO_ROAD){return NO_PATH ;}

    if(j==0)
    {
        if(visited_all_places(places))
            {
             return lengh;}
        if(i!=0) return NO_PATH;
    }

    if(places[j]==1){return NO_PATH;}

    places[j]=1;
    int *value=malloc(N*sizeof(int));
    for(int k=0; k<N ; k++)
    {
        value[k]=get_shortest_path(roads,lengh ,j ,k,places);

    }
    places[j]=0;

    lengh=get_lowest_num(value);
    free(value);
    return lengh ;

}

//////////////////////////////////////////////////////////////////////////////
/*this function gets the array and returns the lowest value  */
int get_lowest_num(int value[N])
{   int lowest=NO_PATH;
    int i=0;
    while(i<N&&value[i]==NO_PATH)
    {
        i++;
    }
    if(i==N){return lowest;}
    else
    {
      lowest=value[i++];
      for(;i<N;i++)
      {
          if(value[i]!=NO_PATH && value[i]<lowest)
            lowest=value[i];
      }
    }
    return lowest;

}
/////////////////////////////////////////////////////////////////////////////
/*this function gets an array and checks if all the values are 1  */
int visited_all_places(int places[N])
{
    for(int i=1;i<N; i++)
    {
        if(places[i]==0){return 0;}
    }
    return 1;
}
//////////////////////////////////////////////////////////////////////////////
// Print functions
void PrintLenOfShortestFullPath(int min_len)
{
    if(min_len == NO_PATH)
    {
        printf("There is no such path!\n");
    }
    else
    {
        printf("The shortest path is of length: %d\n", min_len);
    }
}

void PrintRoadsInputMessage()
{
    printf("Please enter the roads %dX%d matrix row by row:\n", N, N);
}
