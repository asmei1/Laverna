#ifndef UTILS_H
#define UTILS_H

int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);
int multiply(const char* number1, const char* number2, char** result);
int validate(const char *number);
int compare(const char* number1, const char* number2);
char* reverse(const char * number);
int get_value(char c);
int trim(char* number);
int validate_expression(const char *expr);
int is_one_of(const char, char*);
int calculate(const char* expr, char **result);

#endif