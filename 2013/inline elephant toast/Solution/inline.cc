#include<iostream>
#include<cstring>

using namespace std;

long long C[60][60];
long long blank;

long long comb(int n, int k)
{
    if(k==0)
        return 1;
    if(n==k)
        return 1;
        
    if(C[n][k]==blank)
        C[n][k] = comb(n-1,k-1) + comb(n-1,k);
    
    return C[n][k];
}

int main(int argc, char** argv)
{
    int N;

    memset(C,0x1f,sizeof(C));
    blank=C[0][0];

    while(true)
    {
        cin>>N;

        if(N==0)
            break;

        cout<<comb(N,N/2)/(N/2+1)<<endl;
    }

    return 0;
}
