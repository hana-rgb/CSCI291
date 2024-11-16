#include<stdio.h>
#define INITIAL_BALANCE 1000
#define MAX_TRANSACTIONS 10
void process_transactions(int transactions[],int length);
int main(){
    int transactions[]={200,-150,-500,-400,-50,-200,300};
    int length=sizeof(transactions)/sizeof(transactions[0]);
    process_transactions(transactions,length);
    return 0;
}
void process_transactions(int transactions[],int length){
    int balance=INITIAL_BALANCE;
    int tobeprocessed[MAX_TRANSACTIONS];
    int tobeprocessed_count=0;
    for(int i=0;i<length;i++){
        int transaction=transactions[i];
        if(transaction<0&&-transaction>balance){
            printf("Transaction %d (withdrawal of %d AED) is invalid due to insufficient balance.\n",i+1,-transaction);
            tobeprocessed[tobeprocessed_count++]=transaction;
            continue;
        }
        balance+=transaction;
        if(balance==0){
            printf("Balance reached zero. No further transactions will be processed.\n");
            tobeprocessed[tobeprocessed_count++]=transaction;
            for(int j=i+1;j<length;j++){
                tobeprocessed[tobeprocessed_count++]=transactions[j];
            }
            break;
        }
    }
    printf("\nFinal balance: %d AED\n",balance);
    printf("Unprocessed transactions: ");
    for(int i=0;i<tobeprocessed_count;i++){
        printf("%d ",tobeprocessed[i]);
    }
    printf("\n");
}
