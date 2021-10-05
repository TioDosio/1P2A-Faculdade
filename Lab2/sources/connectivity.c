/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#include "connectivity.h"

#define DEBUG 0
unsigned long int find=0, uni=0;

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
   int i, p, q, t;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      find++;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      /* do search first */
      find+=2;
      if (id[p] == id[q]) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }
      
      /* pair has new info; must perform union */
      uni++;
      for (t = id[p], i = 0; i < N; i++) {
         uni+=2;
         if (id[i] == t) {
            uni+=2;
            id[i] = id[q];
         }
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QF: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
   return;
}


/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      find++;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      i = p;
      j = q;

      /* do search first */
      find++;
      while (i != id[i]) {
         i = id[i];
         find+=2;
      }
      find++;
      while (j != id[j]) {
         j = id[j];
         find+=2;
      }
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      id[i] = j;
      uni++;
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
}


/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      find+=2;
      for (i = p; i != id[i]; i = id[i]; find+=2);
      for (j = q; j != id[j]; j = id[j]; find+=2);

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
         uni+=6;
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
         uni+=6;
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);
}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
   int i, j, p, q, t, x;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */

   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      find+=2;
      for (i = p; i != id[i]; i = id[i]; find+=2);
      for (j = q; j != id[j]; j = id[j]; find+=2);

      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
         t = j;
         uni+=6;
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
         t = i;
         uni+=6;
      }
      links_cnt++;

      /* retrace the path and compress to the top  ISTO CONTA COMO UNION??????????*/
      for (i = p; i != id[i]; i = x) {
         x = id[i];
         id[i] = t;
      }
      for (j = q; j != id[j]; j = x) {
         x = id[j];
         id[j] = t;
      }
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of links performed is %d for %d input pairs.\n",
          links_cnt, pairs_cnt);

   return;
}
