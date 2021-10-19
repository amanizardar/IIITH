
//Author :-> Aman Izardar
#include <bits/stdc++.h>
#include <filesystem>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
void backtocanonical();

//
string root;
stack<string> lefts;
stack<string> rights;
vector<struct dirent> curr_files;
vector<string> cmd;

//Code Section : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : : :
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68
#define ENTER_KEY 13
#define BACKSPACE 127
#define HOME 72
#define KEY_ESC 27

// This is The cmd mode

bool searchfun(string cwd, string filename)
{

    const char *c = cwd.c_str();
    struct stat s;

    DIR *dir;
    struct dirent *diread;

    if ((dir = opendir(c)) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            // if (filename == diread->d_name)
            // {
            //     return true;
            // }

            if (strcmp(diread->d_name, filename.c_str()) == 0)
            {
                return true;
            }

            // if(diread->d_name=="." or diread->d_name=="..")
            // {
            //     cout<<". aaya re \n";
            //     continue;
            // }

            if (strcmp(diread->d_name, ".") == 0)
            {
                continue;
            }
            if (strcmp(diread->d_name, "..") == 0)
            {
                continue;
            }

            string newdir = cwd + "/" + diread->d_name;
            const char *path = newdir.c_str();

            if (stat(path, &s) == 0)
            {
                if (s.st_mode & S_IFDIR)
                {
                    // string newdir=cwd+"/"+diread->d_name;
                    // cout<<"Dir hai "<<newdir<<"\n";
                    if (searchfun(newdir, filename))
                        return true;
                }
                else
                {
                    // cout<<"file hai "<<diread->d_name<<"\n";
                }
            }
        }
        closedir(dir);
    }
    return false;
}

bool search(string filename)
{
    string cwd = lefts.top();
    return searchfun(cwd, filename);
}

void rename1(string source, string dest)
{
    string sfp;
    string dfp;

    if (source[0] == '/')
    {
        sfp = source;
    }
    else if (source[0] == '~')
    {
        source.erase(0, 1);
        sfp = root + "/" + source;
    }
    else
    {
        if (source[0] == '.')
        {
            source.erase(0, 1);
        }

        sfp = lefts.top() + "/" + source;
    }

    if (dest[0] == '/')
    {
        dfp = dest;
    }
    else if (dest[0] == '~')
    {
        dest.erase(0, 1);
        dfp = root + "/" + dest;
    }
    else
    {
        if (dest[0] == '.')
        {
            dest.erase(0, 1);
        }

        dfp = lefts.top() + "/" + dest;
    }

    const char *oldpath = sfp.c_str();
    const char *newpath = dfp.c_str();

    rename(oldpath, newpath);
}

void Commandmode()
{

    cout << "\033[2J\033[1;1H"; // Clearing the screen;
    backtocanonical();
    cout << "\033[9999;1H"; //Set Cursor to bottom left

    string s;
    while (1)
    {

        getline(cin, s);
        // cout << "\033[2J\033[1;1H";      // Clearing the screen;
        // cout << "\033[9999;1H";//Set Cursor to bottom left

        if (s == "q")
        {
            exit(0);
        }

        else if (s[0] == 27)
        {
            Normalmode(lefts.top());
            return;
        }
        else
        {
            cmd.clear();
            string word;
            stringstream ss(s);

            while (ss >> word)
                cmd.push_back(word);

            if (cmd.size() == 0)
            {
                continue;
            }

            else if (cmd[0] == "search")
            {
                if (cmd.size() > 2)
                {
                    cout << "Please Enter a valid file/Dir Name";
                    continue;
                }
                else
                {
                    if (search(cmd[1]))
                        cout << "True\n";
                    else
                        cout << "False\n";
                }
            }

            else if (cmd[0] == "goto")
            {
                if (cmd.size() > 2)
                {
                    cout << "Please Enter a valid Command";
                    continue;
                }
                else
                {
                    if (cmd[1][0] == '/') //Goto absolute path
                    {
                        lefts.push(cmd[1]);
                    }
                    else //Goto Relative Path
                    {
                        string cwd = lefts.top();
                        cwd += "/";
                        cwd += cmd[1];

                        lefts.push(cwd);
                    }
                }
            }

            else if (cmd[0] == "mydir") //Extra cmd to print cwd
            {
                cout << lefts.top() << "\n";
            }

            else if (cmd[0] == "create_file")
            {
                if (cmd.size() != 3)
                {
                    cout << "Please Provide a Valid Cmd\n";
                }
                else
                {
                    //cmd[1] ==> filename
                    //cmd[2] ==> path

                    string filename = cmd[1];
                    string path = cmd[2];

                    if (cmd[2][0] == '/')
                    {
                        path += "/" + filename;
                        const char *p = path.c_str();
                        creat(p, O_CREAT);
                    }
                    else if (cmd[2][0] == '~')
                    {
                        path.erase(0, 1);
                        string fullpath = root + "/" + path + "/" + filename;
                        const char *p = fullpath.c_str();
                        creat(p, O_CREAT);
                    }
                    else
                    {
                        string cwd = lefts.top();
                        string fullpath = cwd + "/" + path + "/" + filename;
                        const char *p = fullpath.c_str();
                        creat(p, O_CREAT);
                    }
                }
            }

            else if (cmd[0] == "create_dir")
            {
                if (cmd.size() != 3)
                {
                    cout << "Please Provide a Valid Cmd\n";
                }
                else
                {
                    //cmd[1] ==> Dir name
                    //cmd[2] ==> path

                    string filename = cmd[1];
                    string path = cmd[2];

                    if (cmd[2][0] == '/')
                    {
                        path += "/" + filename;
                        const char *p = path.c_str();
                        mkdir(p, O_CREAT);
                    }
                    else if (cmd[2][0] == '~')
                    {
                        path.erase(0, 1);
                        string fullpath = root + "/" + path + "/" + filename;
                        const char *p = fullpath.c_str();
                        mkdir(p, O_CREAT);
                    }
                    else
                    {
                        string cwd = lefts.top();
                        string fullpath = cwd + "/" + path + "/" + filename;
                        const char *p = fullpath.c_str();
                        mkdir(p, O_CREAT);
                    }
                }
            }

            else if (cmd[0] == "rename")
            {
                if (cmd.size() != 3)
                {
                    cout << "Please Enter a Valid Command\n";
                }
                else
                {
                    string source = cmd[1];
                    string dest = cmd[2];

                    rename1(source, dest);
                }
            }

            
        }

        //  cout << "\033[2J\033[1;1H";      // Clearing the screen;
        //  cout << "\033[9999;1H";//Set Cursor to bottom left
    }
}

// End Of Cmd Mode

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
            // stat(diread->d_name, &fileStat);

            // char *dirr = (diread->d_name);
            // string dirrr = dirr;
            curr_files.push_back(*diread);
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
    printf("\t");

    printf("%ld ", fileStat.st_nlink);

    pw = getpwuid(fileStat.st_uid);
    if (pw)
        printf("%s ", pw->pw_name);
    else
        printf("%s", "NA");

    gp = getgrgid(fileStat.st_gid);
    if (gp)
        printf("%s  ", gp->gr_name);
    else
        printf("%s", "NA");

    printf("\t");

    c = ctime(&fileStat.st_mtime);
    if (c)
        for (i = 4; i <= 10; i++)
            printf("%c", c[i]);
    else
        printf("%s", "NA");

    printf("\t");

    double totsize = fileStat.st_size;
    int cc = 0;
    while (totsize > 1024)
    {
        totsize = totsize / 1024;
        cc++;
    }
    if (cc == 0)
    {
        printf("%10.1f B", totsize);
    }
    else if (cc == 1)
    {
        printf("%10.1f KB", totsize);
    }
    else if (cc == 2)
    {
        printf("%10.1f MB", totsize);
    }
    else if (cc == 3)
    {
        printf("%10.1f GB", totsize);
    }
    else
    {
        printf("%10.1f B", 0.0);
    }

    printf("\t");

    string name = myfile->d_name;
    if (name.length() > 14)
    {
        name = name.substr(0, 14);
        // name+="---";
    }
    printf(" %s\n", name.c_str());
}

void Print_files_caller(int start, int end)
{
    cout << "\033[2J\033[1;1H";      // Clearing the screen;
    printf("%c[%d;%df", 0x1B, 0, 0); // cursor at 0,0;

    // cout<<"hi my name is aman\n";
    for (int i = start; i <= end; i++)
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
    cout << "\033[2J\033[1;1H"; // Clearing the screen;
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
    printf("%c[%d;%df", 0x1B, 1, 0); // cursor at 0,0;
    int curr_cursor = 1;

    int ch;
    int flag = 1;
    while (flag)
    {
        ch = getch();

        if (ch == KEY_UP)
        {
            if (curr_cursor != s)
            {
                curr_cursor--;
                printf("%c[%d;%df", 0x1B, curr_cursor, 0);
            }
        }

        else if (ch == KEY_DOWN)
        {
            if (curr_cursor != e + 1)
            {
                curr_cursor++;
                printf("%c[%d;%df", 0x1B, curr_cursor, 0);
                // cout<<"cursor at "<<curr_cursor;
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

            struct dirent *myfile;
            myfile = &curr_files[curr_cursor - 1];

            string cwf = lefts.top();
            cwf += "/";
            string filename = myfile->d_name;
            cwf += filename;
            const char *path = cwf.c_str();
            // cout<<cwf<<"\n";

            struct stat s;
            if (stat(path, &s) == 0)
            {
                if (s.st_mode & S_IFDIR)
                {
                    lefts.push(cwf);
                    flag = 0;
                    Normalmode(cwf);
                }
                else if (s.st_mode & S_IFREG)
                {
                    pid_t pid = fork();
                    if (pid == 0)
                    {
                        // child process
                        execlp("/usr/bin/xdg-open", "xdg-open", cwf.c_str(), (char *)0);
                        _exit(127);
                    };
                }
                else
                {
                    cout << "Anything else";
                }
            }
            else
            {
                cout << "Error";
            }
        }

        else if (ch == BACKSPACE)
        {
            string cwd = lefts.top();
            while (!lefts.empty())
                lefts.pop();
            while (!rights.empty())
                rights.pop();

            while (cwd[cwd.length() - 1] != '/')
            {
                cwd.pop_back();
            }
            cwd.pop_back();

            // cout<<cwd;

            lefts.push(cwd);
            Normalmode(cwd); //Problem Here
        }

        else if (ch == KEY_LEFT)
        {
            if (lefts.size() > 1)
            {
                rights.push(lefts.top());
                lefts.pop();
                Normalmode(lefts.top());
            }
        }

        else if (ch == KEY_RIGHT)
        {
            if (rights.size() > 1)
            {
                lefts.push(rights.top());
                rights.pop();
                Normalmode(lefts.top());
            }
        }

        else if (ch == 'q')
        {
            exit(0);
        }

        else if (ch == HOME)
        {
            string home = "/home";
            lefts.push(home);
            Normalmode(home); //Problem
        }

        else if (ch == ':')
        {
            Commandmode();
        }
    }
}

void Normalmode(string cwd)
{
    Get_files_metadata(cwd);

    int s = 0;
    int e = 0;

    if (curr_files.size() >= 20)
        e = 19;
    else
        e = curr_files.size() - 1;

    Print_files_caller(s, e);

    Raw_Mode(0, curr_files.size() - 1, s, e);
}

void solve()
{

    char buff[256];
    getcwd(buff, 256);
    // cout << "Current working directory: " << tmp << endl;
    string cwd = buff;
    root = cwd;
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
