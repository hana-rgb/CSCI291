#include<stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define nRows 8
#define nCols 3
// PROTOTYPES
int arrayIn[5]={10, 20, 30, 40, 50};
int arrayOut[5]={10, 10, 20, 40, 50};
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);


int main(){
int arr[SIZE];
int arr2d[nRows][nCols];
print_matrix(arr2d,nRows);
void array(int 10, int 10, int 30, int 20, int 40, int 40, int 50, int 50);
//Call to different functions
}

void print_array(int array[], int length){
   for(int i=0;i<SIZE; i++){
      printf("array[%d]= %d\n", i, array[i]);
   }
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<nRows; i++){
    for(int j=0;j<nCols; j++)
    arr2d[i][j]=i*nCols+j+1;
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}
//FUNCTION DEFINITIONS
