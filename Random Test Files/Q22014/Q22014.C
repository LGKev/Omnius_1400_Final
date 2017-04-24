/*
test file for the second quiz
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



int pickMax (int const * a, int const * b, int n, int *c ){
if( a == NULL || b == NULL || n<0)return -1;
else
{
  for (int i =0; i<n; i++)
  {
    if(a[i]>b[i])
    {
      c[i] = a[i];
    }
    else{
    c[i] = b[i];
    }
    printf(" %d ", c[i]);
  }
}return 0;

}

int main(void){

  int x[] = {1,3,-5,2,-5,8};
  int y[] = {12,1,-3,2,-8,7};
  int z[6];



  int error = pickMax(x, y, 6, z);
  assert(!error);

  for(int i=0; i<6; i ++){
    assert(z[i] >= x[i] && z[i] >= y[i]);
    assert(z[i]== x[i] || z[i] == y[i]);
  }
  return 0;
}
