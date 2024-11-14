#include <stdio.h>
#include <stdbool.h>

#define SIZE 24

void print_array(int array[],int length);
void print_matrix(int mat[][3],int rows);
bool isValid(const int arr[],int length,int pos);
void remove_element(int arr[],int length,int pos);
void insert_element(int arr[],int length,int pos,int value);
void reshape(const int arr[],int length,int rows,int cols,int arr2d[rows][cols]);
void trans_matrix(int rows,int cols,const int mat[rows][cols],int mat_transp[cols][rows]);
bool found_duplicate(int arr[],int length);

int main(){
    int arr[SIZE] = {0};
    int arr2d[8][3] = {0};
    int arrayIn[5] = {10,20,30,40,50};
    int arrayOut[5] = {10,10,20,40,50};

    print_matrix(arr2d,8);
    print_array(arrayIn,5);
    remove_element(arrayIn,5,2);
    insert_element(arrayIn,5,1,25);
    reshape(arrayIn,5,8,3,arr2d);

    if(found_duplicate(arrayOut,5)){
        printf("Duplicates found in arrayOut.\n");
    } else {
        printf("No duplicates found in arrayOut.\n");
    }

    return 0;
}

void print_array(int array[],int length){
    for(int i=0;i<length;i++){
        printf("array[%d]=%d\n",i,array[i]);
    }
}

void print_matrix(int mat[][3],int rows){
    for(int i=0;i<rows;i++){
        for(int j=0;j<3;j++){
            mat[i][j] = i*3 + j + 1;
            printf("mat[%d][%d]=%d ",i,j,mat[i][j]);
        }
        printf("\n");
    }
}

bool isValid(const int arr[],int length,int pos){
    return pos >= 0 && pos < length;
}

void remove_element(int arr[],int length,int pos){
    if(!isValid(arr,length,pos)){
        printf("Error: Position %d is out of bounds.\n",pos);
        return;
    }
    for(int i=pos;i<length-1;i++){
        arr[i] = arr[i+1];
    }
    arr[length-1] = 0;
}

void insert_element(int arr[],int length,int pos,int value){
    if(!isValid(arr,length,pos)){
        printf("Error: Position %d is out of bounds.\n",pos);
        return;
    }
    for(int i=length-1;i>pos;i--){
        arr[i] = arr[i-1];
    }
    arr[pos] = value;
}

void reshape(const int arr[],int length,int rows,int cols,int arr2d[rows][cols]){
    if(length != rows * cols){
        printf("Error: Array length does not match matrix dimensions.\n");
        return;
    }
    int k = 0;
    for(int j=0;j<cols;j++){
        for(int i=0;i<rows;i++){
            arr2d[i][j] = arr[k++];
        }
    }
}

void trans_matrix(int rows,int cols,const int mat[rows][cols],int mat_transp[cols][rows]){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            mat_transp[j][i] = mat[i][j];
        }
    }
}

bool found_duplicate(int arr[],int length){
    for(int i=0;i<length-1;i++){
        for(int j=i+1;j<length;j++){
            if(arr[i] == arr[j]){
                return true;
            }
        }
    }
    return false;
}
