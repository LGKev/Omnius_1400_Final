/* quiz from 2014 number 5*/
/*
Write the alst element of array a to the location pointed by e and remove that element from a, return 0 if good and 01 if not

general thoughts is i'm using the array library
i can use Arrayget and then change the capacity with resize. here. we go.

*/
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
int arrayPopBack( array a, void ** e){
  arrayGet(a, e);
  size = a -> capacity;
  resizeArray(a, size -1);
}

//well the above was wrong as f. first off we use in use and not capacity
//ten we need to check that a is not null and e is also not null
//we dont need to get the element jsut not suse it.
//resizeArra(a, a->inuse -1) is the correct resizing

//also need to check if in use is 0

int arrayPopBack(array a, void ** e){
  if(!a || !e)return -1;
  if(a -> inuse == 0){
    return -1;
  }
  resizeArray(a, a->inuse - 1)
}
