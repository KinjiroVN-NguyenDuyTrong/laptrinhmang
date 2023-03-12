#include <stdio.h>
int main()
{
  int i,n;
  scanf("%d\n",&n);
  int arr[n];
  for(i=0;i<n;i++)
  {
    scanf("%d",&arr[i]);
  }
  if(arr[0]>arr[1]) printf("0");
  for(i=0;i<n;i++)
  {
    
    if(arr[i-1]<arr[i]&&arr[i]>arr[i+1]){
      printf("%d ",i);
    }
  }
  if(arr[n-1]>arr[n-2]) printf("%d",n);
}