/******************************************************************************
* Sample solution for the Subway problem in NWERC'03
* Runs in O(N), based on calculating a hash code for a tree, based on it's structure
* Author: Jimmy Mårdell
******************************************************************************/

int h[9999];
char s[9999],t[9999],*p;

int hash(int j)
{
  int sum=h[j+5000];
  while (*p && *p++=='0')
    sum=(sum+h[j]*hash(j+1)) % 19001;
  return ((sum*sum) % 19001);
}

main() {
	int i,j,N;
	scanf("%d",&N);
	while (N--) {						
		scanf("%s%s",s,t);
		
		for(j=0;j<10;j++)	{
			for(i=0;i<9999;i++) h[i]=rand()%19001+3;
			p=s; i=hash(0);	p=t;
			if (i!=hash(0)) break;
		}
		printf("%s\n",j==10?"same":"different");
	}
}
