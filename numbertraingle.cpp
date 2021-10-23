#include <iostream>  
using namespace std;  
int main()  
{  
int i,j,k,l,n;    
cout<<"Enter the Range=";    
cin>>n;    
for(i=1;i<=n;i++)    
{    
for(j=1;j<=n-i;j++)    
{    
cout<<" ";    
}    
for(k=1;k<=i;k++)    
{    
cout<<k;    
}    
for(l=i-1;l>=1;l--)    
{    
cout<<l;    
}    
cout<<"\n";    
}    
return 0;  
}  
