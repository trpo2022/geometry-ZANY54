#include <ctype.h>
#include <stdio.h>
#include <string.h>

int check_line();
int isCorrect(char* str);
int size=100;
int main()
{
    char str[size];

    int lines = check_line();

    FILE* file = fopen("input.txt", "r");
    for (int line = 0; line < lines; line++) {
        fgets(str, size, file);
        str[strlen(str) - 1] = '\0';

        if (isCorrect(str))
            printf("Correct\n");
        printf("\n");
    }

    fclose(file);
    return 0;
}

int check_line()
{
    FILE* file = fopen("input.txt", "r");
    int lines = 0;

    while (!feof(file))
        if (fgetc(file) == '\n')
            lines++;

    fclose(file);
    return lines;
}

int isCorrect(char* str)
{
    int check = 1;

    int open = 0, close = 0;
    int open_brackets, close_braket; // position
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            open++;
            open_brackets = i + 1;
        }
        if (str[i] == ')') {
            close++;
            close_braket = i - 1;
        }
    }
    if (open != close) {
        check = 0;
        int position = strlen(str);
        printf("%s\n", str);
        for (int i = 0; i < (position - 1); i++)
            printf(" ");
        printf("^\nError at column %ld: expected ')'\n", strlen(str));
        return check;
    }

    int k = 0;
    for (int i = open_brackets; i <= close_braket; i++)
        if (isalpha(str[i])) {
            k = i;
            break;
        }
    if (k != 0) {
        check = 0;
        printf("%s\n", str);
        for (int i = 0; i < k; i++)
            printf(" ");
        printf("^\nError at column %d: expected '<double>'\n", k);
        return check;
    }

    int j = 0, i = 0;
    char object[10];
    while (str[i] != '(') {
        if (str[i] != ' ') {
            object[j] = tolower(str[i]);
            j++;
        }
        i++;
    }

    if (strstr(object, "triangle") == NULL
        && strstr(object, "circle") == NULL) {
        check = 0;
        printf("%s\n^\nError at column 0: expected 'circle' or 'triangle'\n",
               str);
        return check;
    }

    if (strlen(str) > close_braket + 2) {
        check = 0;
        printf("%s\n", str);
        for (int i = 0; i <= (close_braket + 2); i++)
            printf(" ");
        printf("^\nError at column %d: unexpected token\n", close_braket + 3);
    }

    return check;
}