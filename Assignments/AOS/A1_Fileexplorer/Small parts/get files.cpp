#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

vector<string> curr_dir,files;
int main() {

        struct stat fileStat;
        stat("/",&fileStat); 

    DIR *dir; struct dirent *diread;
    

    if ((dir = opendir(".")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            stat(diread->d_name,&fileStat);
             char * dirr = (diread->d_name);
            string dirrr=dirr;
            if( (S_ISDIR(fileStat.st_mode)))
            {
                curr_dir.push_back(dirrr);
            }
            else{
            files.push_back(dirrr);
            }
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return EXIT_FAILURE;
    }

    cout<<"Directories are:\n";
    for(auto i:curr_dir)
    {
        cout<<i<<" ";
    }
    cout<<"\n";
    cout<<"files are:\n";
    for(auto i:files)
    {
        cout<<i<<" ";
    }
    cout<<"\n";

    return EXIT_SUCCESS;
}
