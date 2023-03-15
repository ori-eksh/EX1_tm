#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

struct AdptArray_
{
   int ArrSize;
   PElement *pElemArr;
   DEL_FUNC delFunc;
   COPY_FUNC copyFunc;
   PRINT_FUNC printFunc;
};

PAdptArray
CreateAdptArray(COPY_FUNC copy_, DEL_FUNC del_, PRINT_FUNC print_)
{
   PAdptArray pArr = (PAdptArray)malloc(sizeof(struct AdptArray_));
   if (pArr == NULL)
      return NULL;
   pArr->ArrSize = 0;
   (pArr->pElemArr) = NULL;
   pArr->delFunc = del_;
   pArr->copyFunc = copy_;
   pArr->printFunc = print_;
   return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
   PElement *newpElemArr;
   if (pArr == NULL)
      return FAIL;

   if (idx >= pArr->ArrSize)
   {

      // Extend Array
      if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
         return FAIL;
      memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
      free(pArr->pElemArr);
      pArr->pElemArr = newpElemArr;
   }

   // Delete Previous Elem
   if (((pArr->pElemArr)[idx]) != NULL)
   {
      pArr->delFunc((pArr->pElemArr)[idx]);
   }
   (pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
   // Update Array Size
   pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;

   return SUCCESS;
}
// C.

void DeleteAdptArray(PAdptArray pArr)
{
   int i;
   if (pArr == NULL)
      return;
   for (i = 0; i < pArr->ArrSize; ++i)
   {
      if ((pArr->pElemArr)[i] != NULL)
         pArr->delFunc((pArr->pElemArr)[i]);
   }
   free(pArr->pElemArr);
   free(pArr);
}

PElement GetAdptArrayAt(PAdptArray p, int x)
{
   if (p == NULL || p->pElemArr[x] == NULL || x < 0)
   {
      return NULL;
   }

   return p->copyFunc(p->pElemArr[x]);
}

int GetAdptArraySize(PAdptArray p)
{
   if (p == NULL)
      return -1;
   return p->ArrSize;
}

void PrintDB(PAdptArray p)
{

   if (p == NULL)
      return;

   for (int i = 0; i < p->ArrSize; i++)
   {
      if (p->pElemArr[i] != NULL)
         p->printFunc(p->pElemArr[i]);
   }
}