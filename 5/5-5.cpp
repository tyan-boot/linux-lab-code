#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sys/time.h>


using std::vector;
using std::string;

int main()
{
    FILE *file, *result;
    vector<string> lines;
    timeval tv1{}, tv2{};

    file = fopen("File1.txt", "r");
    result = fopen("File1-result.txt", "w+");

    if (file == nullptr)
    {
        perror("Unable open file");
        exit(1);
    }

    char *line = (char *) calloc(32, sizeof(char));
    size_t size = 32;

    while (getline(&line, &size, file) != -1)
    {
        lines.emplace_back(string{line});
    }

    gettimeofday(&tv1, nullptr);

    std::sort(lines.begin(), lines.end());

    gettimeofday(&tv2, nullptr);

    auto time_spend = tv2.tv_usec - tv1.tv_usec;

    printf("time spend = %ld ms\n", time_spend);

    for (auto &sorted_line : lines)
    {
        fwrite(sorted_line.data(), sizeof(char),
               sorted_line.length(), result);
    }

    fclose(file);
    fclose(result);

    return 0;
}