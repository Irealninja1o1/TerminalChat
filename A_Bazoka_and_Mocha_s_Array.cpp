#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<climits>
#include<cmath>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t!=0)
    {
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        vector<int> x=arr;
        sort(x.begin(),x.end());
        string ans="No";
        if(x==arr){ans="Yes";}
        else
        {
            int i=0;
            while(arr[i]>=arr[n-1])
            {
                int f=arr[i];
                for(int j=0;j<n-1;j++)
                {
                    arr[j]=arr[j+1];
                }
                arr[n-1]=f;
                if(arr==x){ans="Yes";break;}
            }
            
        }
        cout<<ans<<endl;
        

        t--;
    }
}
