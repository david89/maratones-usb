/******************************************************************************
* Sample solution for the Subway problem in NWERC'03
* Author: Andreas Björklund
******************************************************************************/
#include <stdio.h>
#include <string.h>

#define MAX_STRLEN (3002)

char buf1[MAX_STRLEN],buf2[MAX_STRLEN];
char strs[MAX_STRLEN*MAX_STRLEN];

char *ptrs[2*MAX_STRLEN];

char* sort(char *pbuf,char **pptrs)
{

  int i,cnt=0;
  pptrs[cnt++]=pbuf;

  while (*pbuf && *pbuf++ =='0')
  {
    pbuf=sort(pbuf, &pptrs[cnt]);
    pbuf++;
    pptrs[cnt++]=pbuf;
  }
  
  // Cut out the strings
  for (i=0;i<cnt-1;i++)
  {
    int j=0;
    pbuf=pptrs[i];
    while (pbuf!=pptrs[i+1])
    {
      strs[i*MAX_STRLEN+j]=*pbuf++;
      j++;
    }
    strs[i*MAX_STRLEN+j]=0;
  }
  
  // Sort them
  qsort(strs,cnt-1,MAX_STRLEN,strcmp);
  
  // Put them back
  pbuf=pptrs[0];
  for (i=0;i<cnt-1;i++)
  {
    int j=0;
    
    while (strs[i*MAX_STRLEN+j])
    {
      *pbuf++ = strs[i*MAX_STRLEN+j];
      j++;
    }
  }
  return pptrs[cnt-1];
}

int main(void)
{
  int n;
  scanf("%d",&n);
  gets(buf1);
  while(n--)
  {
    gets(buf1);
    gets(buf2);
    sort(buf1,ptrs);
    sort(buf2,ptrs);
    if (strcmp(buf1,buf2)==0) printf("same\n"); else printf("different\n");
  }
  return 0;
}
  