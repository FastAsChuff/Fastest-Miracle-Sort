#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// gcc miraclesort.c -o miraclesort.bin -O3 -march=native -Wall

#define MIRACLESORT_UNSORTEDMSG "Not Sorted Yet!"
#define MIRACLESORT_MEMALLOCFAILMSG "Failed To Allocate Memory!"
#define MIRACLESORT_INPUTINCALIDMSG "Input Invalid!"
#define MIRACLESORT_MAXARRAYSIZE 255

_Bool setissorted(int32_t *array, uint64_t arraysize) {
  int32_t prev = array[0];
  for (uint64_t i=1; i<arraysize; i++) {
    if (array[i] < prev) return false;
    prev = array[i];
  }
  return true;
}

void miraclesorti32(int32_t *arraytosort, uint64_t arraysize) {
  _Bool issorted = setissorted(arraytosort, arraysize);    
  while (!issorted) {
    sleep(10);
    issorted = setissorted(arraytosort, arraysize);    
    if (!issorted) printf("%s\n", MIRACLESORT_UNSORTEDMSG);
  }
}

void die(char* msg) {
  printf("%s\n", msg);
  exit(1);
}

int main(int32_t argc, char* argv[]) {  
  printf("Welcome to Miracle Sort!!\n");
  printf("Please enter number of 32 bit signed integers to sort, Max 255.\n");
  int64_t arraysize = 0;
  if (scanf("%li", &arraysize) != 1) {
    die(MIRACLESORT_INPUTINCALIDMSG);
  }
  if ((arraysize <= 0) || (arraysize > MIRACLESORT_MAXARRAYSIZE)) {
    die(MIRACLESORT_INPUTINCALIDMSG);
  }
  int32_t *arraytosort = malloc(arraysize*sizeof(int32_t));
  if (arraytosort == NULL) die(MIRACLESORT_MEMALLOCFAILMSG);
  printf("Please enter integers to sort, one by one.\n");
  for (uint64_t i=0; i<arraysize; i++) {
    if (scanf("%i", &arraytosort[i]) != 1) {
      die(MIRACLESORT_INPUTINCALIDMSG);
    }    
  }
  printf("Sorting. Please wait...\n");
  miraclesorti32(arraytosort, arraysize);
  printf("List is sorted!\n");
  printf("%i", arraytosort[0]);
  for (uint64_t i=1; i<arraysize; i++) {
    printf(", %i", arraytosort[i]);
  }
  printf("\n");
  free(arraytosort);
}
