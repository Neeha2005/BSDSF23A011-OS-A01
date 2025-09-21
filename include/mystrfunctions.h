#ifndef MYSTRFUNCTIONS_H
#define MYSTRFUNCTIONS_H

// Calculate length of string s
int mystrlen(const char* s);

// Copy src into dest
int mystrcpy(char* dest, const char* src);

// Copy at most n chars from src into dest
int mystrncpy(char* dest, const char* src, int n);

// Concatenate src to dest
int mystrcat(char* dest, const char* src);

#endif // MYSTRFUNCTIONS_H
