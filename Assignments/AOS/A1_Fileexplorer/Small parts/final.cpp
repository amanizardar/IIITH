
//Author :-> Aman Izardar
#include <bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <termios.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define phi 3.1415926536
#define mod 1000000007
using namespace std;


// Function Declaratiom
void Normalmode(string);

// 


stack<string> lefts; 
stack<string> rights;
vector<struct dirent> curr_files;

//Code Section : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : :
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68
#define ENTER_KEY 13
#define BACKSPACE 127
#define HOME 72
#define KEY_ESC 27

int getch(void)
{
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= static_cast<unsigned int>(~(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void Get_files_metadata(string cwd)
{
    // curr_dir.clear();
    curr_files.clear();

    struct stat fileStat;
    DIR *dir;
    struct dirent *diread;

    const char *c = cwd.c_str();

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
    stat(myfile->d_name, &fileStat);
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");
    printf("%ld ", fileStat.st_nlink);
    pw = getpwuid(fileStat.st_uid);
    printf("%s ", pw->pw_name);
    gp = getgrgid(fileStat.st_gid);
    printf("%s  ", gp->gr_name);
    c = ctime(&fileStat.st_mtime);
    for (i = 4; i <= 15; i++)
        printf("%c", c[i]);
    printf("  ");
    printf("%-8ld%-8s\n", fileStat.st_size, myfile->d_name);
}

void Print_files_caller(int start, int end)
{
    cout << "\033[2J\033[1;1H";      // Clearing the screen;
    printf("%c[%d;%df", 0x1B, 0, 0); // cursor at 0,0;

    // cout<<"hi my name is aman\n";
    for (int i = start; i < end; i++)
    {
        Print_Details(&curr_files[i]);
    }
}

struct termios org;

void die(const char *s)
{
    perror(s);
    exit(1);
}

void backtocanonical()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &org) == -1)
        die("tcsetattr");
}

void noncanonicalmode()
{
    struct termios temp;
    if (tcgetattr(STDIN_FILENO, &org) == -1)
        die("tcgetattr");

    temp = org;
    temp.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    temp.c_iflag &= ~(IXON | ICRNL);
    temp.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &temp) == -1)
        die("tcsetattr");
    atexit(backtocanonical);
}

void Raw_Mode(int vstart, int vend, int s, int e)
{

    noncanonicalmode();
    printf("%c[%d;%df", 0x1B, 0, 0); // cursor at 0,0;
    int curr_cursor = 0;

    int ch;

    while (true)
    {
        ch = getch();

        if (ch == KEY_UP)
        {
            if (curr_cursor != 0)
            {
                printf("%c[%d;%df", 0x1B, curr_cursor - 1, 0); // cursor at 0,0;
                curr_cursor--;
            }
        }

        else if (ch == KEY_DOWN)
        {
            if (curr_cursor != e)
            {
                printf("%c[%d;%df", 0x1B, curr_cursor + 1, 0); // cursor at 0,0;
                curr_cursor++;
            }
        }

        else if (ch == 'k' or ch == 'K')
        {
            if (s != 0)
            {
                s--;
                e--;
                curr_cursor--;
                Print_files_caller(s, e);
            }
        }
        else if (ch == 'l' or ch == 'L')
        {
            if (e != vend)
            {
                s++;
                e++;
                curr_cursor++;
                Print_files_caller(s, e);
            }
        }
        

        else if (ch == ENTER_KEY)
        {
            struct stat fileStat;
            struct dirent *myfile;
            myfile = &curr_files[curr_cursor-1];
            stat(myfile->d_name, &fileStat);

            string cwf=lefts.top();
            cwf+="/";
            string filename=myfile->d_name;
            cwf+=filename;
            // cout<<cwf<<"\n";

            if (!(S_ISDIR(fileStat.st_mode))) //This is a file
            {
                pid_t pid = fork();
                if (pid == 0)
                {
                    // child process
                    execlp("/usr/bin/xdg-open","xdg-open", cwf.c_str(), (char *)0);
                    _exit(127);
                };
            }

            else // This is a Directory
            {
                lefts.push(cwf);
                Normalmode(cwf);

            }
        }

        else if(ch==BACKSPACE)
        {
            string cwd=lefts.top();
            while(!lefts.empty())
            lefts.pop();
            while(!rights.empty())
            rights.pop();

            
            while(cwd[cwd.length()-1]!='/')
            {
                cwd.pop_back();
            }
            cwd.pop_back();

            // cout<<cwd;
            
            lefts.push(cwd);
            // Normalmode(cwd);   //Problem Here
        }


        else if (ch == KEY_LEFT)
        {
            if(lefts.size()>1)
            {
                rights.push(lefts.top());
                lefts.pop();
                Normalmode(lefts.top());
            }
        }



        else if (ch == KEY_RIGHT)
        {
            if(rights.size()>1)
            {
                lefts.push(rights.top());
                rights.pop();
                Normalmode(lefts.top());
            }   
        }

        else if(ch==HOME)
        {
            string home="/home";
            lefts.push(home);
            Normalmode(home);
        }

        else if(ch==':')
        {
            cout<<"WE are in cmd mode";
        }


        
       
    }
}

void Normalmode(string cwd)
{
    Get_files_metadata(cwd);

    int s = 0;
    int e = 0;

    if (curr_files.size() >= 20)
        e = 20;
    else
        e = curr_files.size();

    Print_files_caller(s, e);

    Raw_Mode(0, curr_files.size(), s, e);
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

