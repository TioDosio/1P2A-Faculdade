/**************************************************************************
 *
 * File Name: p2.c
 *	      (c) 2021 AED
 * Author:    AED Team
 * Revision:  12 October 2021
 *
 * NAME
 *     p2.c - Test code for P2 of the Lab for Individual Evaluation (LAI, LAB04)
 *
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
 *     #include <string.h>
 *
 * DESCRIPTION
 *     Test for P2 of the LAI
 *
 * DIAGNOSTICS
 *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**************************************************************************
 * check_property()
 *
 * Arguments: vec - pointer to integer vector
 %            iL, iR - index of starting and end point of vector
 * Returns: number of levels in which property is tested
 * Side-Effects: none
 *
 * Description:
 *
 *************************************************************************/
int iR;
int check_property(int * vec, iR) {
   int result, *k,*l;
   result = vec[2][k]
   /* compute required property, store in result */
   /*vou fazer o exemplo da preparação*/
   for(l=0; l<iR; l++){
      for(k=0; k<iR; k++){
         if ((vec[2][k])<(vec[2][k+1])){
            result[l]=vec[2][k+1];
         }
      }
   }
   return(result);
}



/************************************************************************
 * Main code
 ************************************************************************/

int main(int argc, char *argv[]) {
   FILE *fp;
   int i, j, N, result = 0, **vec;

   if (argc < 2) {
      fprintf(stderr, "usage: %s <filename>\n", argv[0]);
      exit(1);
   }

   /* open filename if possible */
   fp = fopen(argv[1], "r");
   if (fp == ((FILE*) NULL))  {
      fprintf(stderr, "error: cannot open file %s\n", argv[1]);
      exit(1);
   }

   result = fscanf(fp, "%d", &N);
   if (result != 1)  {
      fprintf(stderr, "error: cannot read integer size\n");
      exit(1);
   }

   /* allocate memory, read in the array and print it */
   vec = (int) malloc(result*sizeof(int));
   

   for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
         fscanf(fp, "\%d", &vec[i][j]);

#ifdef DEBUG
   printf("\nOriginal array:\n ");
   for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++)
         printf("\%d ", vec[i][j]);
      printf("\n");
   }
#endif

   /* Now process array; example below sends each row at a time */
   for (i = 0; i < N; i++) {
      result = check_property(vec[i], 0, N-1);
      printf("result[line %d]: %d\n", i, result);
   }

   /* free memory */
   free(vec);

   exit(0);
}