#pragma once
#ifndef COMPARATORS_H
#define COMPARATORS_H
typedef struct point_t{
    double x;
    double y;
}point;
int sort(void* ptr, int length, int dataSize, int(*comp)(const void*, const void*));
int comp_int(const void* ptr1, const void* ptr2);
int comp_double(const void* ptr1, const void* ptr2);
int comp_point(const void* ptr1, const void* ptr2);
void swap(void* a, void* b, int len);

#endif // !COMPARATORS_H