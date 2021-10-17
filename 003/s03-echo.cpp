#include <iostream>
#include <string>
#include <string.h>

int main(int argc, char *argv[])
{
    int s = 0;
    bool n, r, l;
    n = r = l = false;

    for (int i = 1; i <= 3; i++)
    {
        if(strcmp(argv[i], "-n") == 0) {
                n = true;
        } else if(strcmp(argv[i], "-r") == 0) {
                r = true;
        } else if(strcmp(argv[i], "-l") == 0) {
                l = true;
        }
    }

    if(n) s++;
    if(r) s++;
    if(l) s++;
    
    if(r) {
        for (int i = argc - 1; i > s; i--)
        {
            std::cout << argv[i];
            if((i == s + 1 && !n) || i != s + 1 && l) std::cout << '\n';
        }
    } else {
        for (int i = 1 + s; i < argc; i++)
        {
            std::cout << argv[i];
            if((i == argc - 1 && !n) || i != argc - 1 && l) std::cout << '\n';
        }
    }
    
    return 0;
}
