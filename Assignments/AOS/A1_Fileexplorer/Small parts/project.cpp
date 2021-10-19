
//Author :-> Aman Izardar
#include <bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define phi 3.1415926536
#define mod 1000000007
using namespace std;

stack<string> lefts, rights;
vector<string> curr_files, curr_dir;

//Code Section : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : :

void Get_files_metadata(string cwd)
{
    curr_dir.clear();
    curr_files.clear();

    struct stat fileStat;
    DIR *dir;
    struct dirent *diread;
    
    const char * c = cwd.c_str();


    if ((dir = opendir(c)) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            stat(diread->d_name, &fileStat);

            char *dirr = (diread->d_name);
            string dirrr = dirr;

            if ((S_ISDIR(fileStat.st_mode)))
            {
                curr_dir.push_back(dirrr);
            }
            else
            {
                curr_files.push_back(dirrr);
            }
        }
        closedir(dir);
    }
}


void Print_files(int start,int end)
{
    cout << "\033[2J\033[1;1H"; // Clearing the screen;
    printf("%c[%d;%df",0x1B,0,0); // cursor at 0,0;
    cout<<"hi my name is aman\n";
}

void Normalmode(string cwd)
{
    Get_files_metadata(cwd);

    int s=0;
    int e=0;

    if(curr_dir.size()+curr_files.size()>20)
    e=20;
    else
    e=curr_dir.size()+curr_files.size();

    Print_files(s,e);

    
}

void solve()
{

    char buff[256];
    getcwd(buff, 256);
    // cout << "Current working directory: " << tmp << endl;
    string cwd = buff;
    lefts.push(cwd);
    // cout<<"Our cwd is : \n"<<cwd;

    Normalmode(cwd);
}















int main()
{

    //  ios_base::sync_with_stdio(false);
    //  cin.tie(NULL);

    ll t = 1;
    //cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}
