// #include <curses.h>
#include <iostream>
#include<termios.h>
#include <unistd.h>
using namespace std;

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

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


int main()
{
    int ch;

    
while(true)
{
    ch = getch();

    cout<<ch<<" ";
    
    // switch(ch)
    // {
        // case KEY_UP:{
        //     cout<<"up\n";
        //             break;
        // }           
            
        // case KEY_DOWN:{
        //     cout<<"down\n";
        //             break;
        // }
        // case KEY_LEFT:{
        //     cout<<"Left\n";
        //             break;
        // }
        // case KEY_RIGHT:{
        //     cout<<"Right\n";
        //             break;
        // }

        // case('q'):
        // {
        //     cout<<"You presses q\n";
        //     break;
        // }

        // default:
        // {
        //     cout<<ch<<"\n";
        // }

            
            
        // case ESC:
        //     break;
    // }
}
cout<<"\n";

    return 0;
}