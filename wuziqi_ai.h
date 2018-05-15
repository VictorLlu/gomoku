//
// Created by victor on 2018/5/8.
//
#include <iostream>
#include <vector>
#include "basic.h"
#include <climits>
using namespace std;
#ifndef WUZIQI_WUZIQI_AI_H
#define WUZIQI_WUZIQI_AI_H
struct result{
    int score;
    pair<int, int> point;
};
struct bool_result{
    bool torf;
    pair<int,int> point;
};
int score_table(int nubmer, int empty);
int count_vector_score(vector<int> n, int turn);
int get_total_score(int position[15][15], int turn);
bool has_near_point(int pos[15][15],int x, int y);
vector<pair<int,int>> available_point(int pos[15][15]);
result *find_player_min(int pos[15][15],int depth,int alpha,int beta);
result *find_ai_max(int pos[15][15],int depth,int alpha,int beta);
bool_result *is_bisheng(int pos[15][15],int turn);
bool singlefive(vector<int>n,int turn);
bool singlefour(vector<int>n,int turn);
pair<int,int> ai_make_move(int pos[15][15]);
pair<int,int> ai_init();
#endif //WUZIQI_WUZIQI_AI_H
