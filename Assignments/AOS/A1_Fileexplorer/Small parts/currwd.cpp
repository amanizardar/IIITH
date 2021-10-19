
//Author :-> Aman Izardar
#include<bits/stdc++.h>
#include <filesystem>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define phi 3.1415926536
#define mod 1000000007
using namespace std;

#include <unistd.h>


//Code Section : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : :




void solve()
{



char buff[256];
    getcwd(buff, 256);
    // cout << "Current working directory: " << tmp << endl;
    string cwd = buff;

     while(cwd[cwd.length()-1]!='/')
            {
                cwd.pop_back();
            }
            // cwd.pop_back();

    cout<<cwd<<"\n";




}









int main()
{

 ios_base::sync_with_stdio(false);
 cin.tie(NULL);
//  #ifndef ONLINE_JUDGE
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
//  #endif
ll t=1;
//cin>>t;
while(t--)
{
    solve();
}
return 0;
}
