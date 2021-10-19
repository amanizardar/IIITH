
//Author :-> Aman Izardar
#include <bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include<pwd.h>
#include <grp.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define phi 3.1415926536
#define mod 1000000007
using namespace std;

stack<string> lefts, rights;
vector<struct dirent> curr_files;

//Code Section : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : :

void Get_files_metadata(string cwd)
{
    // curr_dir.clear();
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
                curr_files.push_back(*diread);
            }
            else
            {
                curr_files.push_back(*diread);
            }
        }
        closedir(dir);
    }
}


void Print_Details(struct dirent *myfile)
{
    struct passwd *pw;
    struct group *gp;
    struct stat fileStat;
    char *c;
    int i;
    stat(myfile->d_name,&fileStat);  
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); 
    printf(" ");
    printf("%ld ",fileStat.st_nlink);
    pw=getpwuid(fileStat.st_uid);
    printf("%s ",pw->pw_name);
    gp=getgrgid(fileStat.st_gid);
    printf("%s  ",gp->gr_name);
    c=ctime(&fileStat.st_mtime);
    for(i=4;i<=15;i++)
      printf("%c",c[i]);
    printf("  ");
    printf("%-8ld%-8s\n",fileStat.st_size,myfile->d_name);
    
}

void Print_files_caller(int start,int end)
{
    cout << "\033[2J\033[1;1H"; // Clearing the screen;
    printf("%c[%d;%df",0x1B,0,0); // cursor at 0,0;
    
    // cout<<"hi my name is aman\n";
    for(int i=start;i<end ;i++)
    {
        Print_Details(&curr_files[i]);
    }
}

void Raw_Mode()
{
    printf("%c[%d;%df",0x1B,0,0); // cursor at 0,0;
    // int curr_cursor=0;
    // cout<<"We are in Raw mode";

}

void Normalmode(string cwd)
{
    Get_files_metadata(cwd);

    int s=0;
    int e=0;

    if(curr_files.size()>=20)
    e=20;
    else
    e=curr_files.size();

    Print_files_caller(s,e);

    Raw_Mode();

    
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
