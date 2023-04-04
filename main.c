#include "stdio.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"

#define LINE_LENGTH_LIMIT 100

int main(int argc, char * argv[])
{
    assert(argc == 4);
    char* from = argv[1];
    char* to = argv[2];
    char* homeserver = argv[3];
    char* line = (char*)malloc(LINE_LENGTH_LIMIT * sizeof(char));
    char* replace = (char*)"    \"default_server_name\": \0";
    char* replace_by = (char*)malloc(strlen(replace) + strlen(homeserver) + strlen("\"\",\n\0") + 1);
    strcat(replace_by, replace);
    strcat(replace_by, "\"");
    strcat(replace_by, homeserver);
    strcat(replace_by, "\",\n\0");
    FILE* fin = fopen(from, "r");
    FILE* fout = fopen(to, "w+");
    while (!feof(fin))
    {
        fgets(line, LINE_LENGTH_LIMIT, fin);
        if (feof(fin)) break;
        if (memcmp(line, replace, sizeof replace) == 0)
        {
            fputs(replace_by, fout);
        }
        else
        {
            fputs(line, fout);
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
