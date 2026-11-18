#include <cstdio>

// writes everything it reads from the standard input to the standard output
int main()
{
    char buffer[256];
    size_t count;
    while ((count = std::fread(buffer, 1, sizeof buffer, stdin)) > 0)
        std::fwrite(buffer, 1, count, stdout);
    return 0;
}
