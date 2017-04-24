#include<stdlib.h>
#include<stdio.h>
#include<assert.h>


/*
int Fib(int * fib, int n){
  if(fib == NULL) return -1;
  if(n<=0) return -1;
  else
  {
  int  fib[n];
  int  i =2;
  int * f = fib; // pointers

    * f = 1;
    *(f+1) = 1;

    while(i < n){
      *(f+i) = *(f+1+i) + *(f-2+i);
      i++;
    }
    printf("fib returns : %d \n", *(f+n));
    return 1;
  }
}
*/


int main(void){
  int n = 5;
  int fib[n];

  fib[0]=1;
  fib[1]=1;
  for(int i=2; i<n; i++){
    fib[i]=fib[i-1] + fib[i-2];
    printf("fib[i]= %d,", fib[i]);
  }



/*
  int n =4;
  int fib[n];
  int * f = fib;

  *f = 1;
  *(f+1) = 1;
  int i =2;
  while(i<n){
    *(f+i) = *(f+i-1)+ *(f+i-2);
    i++;
  }
  printf("%d  " , *(f+i-1));
  */
}
