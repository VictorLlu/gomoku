//
// Created by victor on 2018/5/9.
//
#include <iostream>
#include <vector>
using namespace std;
#ifndef WUZIQI_BASIC_H
#define WUZIQI_BASIC_H
void print_canvas(int pos[15][15]);
int get_row(char *input);
int get_column(char *input);
bool check_input(char *input);
bool is_taken(int pos[15][15],char *input);
int is_over(int pos[15][15]);
bool count_five(vector<int> n, int turn);
inline int max_of_two(int a, int b){
    return a>b ? a:b;
}
inline int min_of_two(int a, int b){
    return a<b? a:b;
}
#endif //WUZIQI_BASIC_H
