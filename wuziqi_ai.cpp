//
// Created by victor on 2018/5/8.
//

#include "wuziqi_ai.h"
#include "basic.h"
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int score_table(int number, int empty){
    if(number>=5)    return 1000000;
    else if(number==4)
    {
        if(empty==2)   return 100000;
        else if(empty==1)  return 100000;
    }
    else if(number==3)
    {
        if(empty==2)   return 50000;
        else if(empty==1)  return 100;
    }
    else if(number==2)
    {
        if(empty==2)   return 100;
        else if(empty==1)  return 10;
    }
    else if(number==1&&empty==2)   return 10;
    return 0;
}
int count_vector_score(vector<int> n, int turn){
    int score=0;
    int length=n.size();
    int i=1;
    int number=0;
    int empty=0;
    if(n[0]==0) empty=1;
    else if(n[0]==turn) number++;
    while(i<length){
        if(n[i]==turn) number++;
        else if(n[i]==0){
            if(number==0) empty=1;
            else{
                score+=score_table(number,empty+1);
                empty=1;
                number=0;
            }
        }
        else{
            score+=score_table(number,empty);
            empty=0;
            number=0;
        }
        i++;
    }
    score+=score_table(number,empty);
    return score;
}

int get_total_score(int pos[15][15], int turn){
    int score=0;
    int i,j;
    //横排
    for(i=0;i<15;i++){
        vector<int> n;
        for(j=0;j<15;j++) n.push_back(pos[i][j]);
        score+=count_vector_score(n,turn);
        n.clear();
    }
    //竖排
    for(j=0;j<15;j++){
        vector<int> n;
        for(i=0;i<15;i++) n.push_back(pos[i][j]);
        score+=count_vector_score(n,turn);
        n.clear();
    }
    //上半正斜
    for(i=0;i<15;i++){
        vector<int> n;
        int x,y;
        for(x=i,y=0;x<15 && y<15;x++,y++) n.push_back(pos[x][y]);
        score+=count_vector_score(n,turn);
        n.clear();
    }
    //下半正斜
    for(j=1;j<15;j++){
        vector<int> n;
        int x,y;
        for(x=0,y=j;x<15 && y<15;x++,y++) n.push_back(pos[x][y]);
        score+=count_vector_score(n,turn);
        n.clear();
    }
    //上半反斜
    for(i=0;i<15;i++){
        vector<int> n;
        int x,y;
        for(x=i,y=0;x>=0 && y<15;x--,y++) n.push_back(pos[x][y]);
        score+=count_vector_score(n,turn);
        n.clear();
    }
    //下半反斜
    for(j=1;j<15;j++){
        vector<int> n;
        int x,y;
        for(x=14,y=j;x>=0 && y<15;x--,y++) n.push_back(pos[x][y]);
        score+=count_vector_score(n,turn);
        n.clear();
    }
    return score;
}

bool has_near_point(int pos[15][15],int x, int y){
    int i,j;
    for(i=(x-1>0 ? x-1:0);i<=x+1&&i<15;i++){
        for(j=(y-1>0 ? y-1:0);j<y+1&&j<15;j++){
            if(i!=0||j!=0){
                if(pos[i][j]!=0) return true;
            }
        }
    }
    return false;
}

vector<pair<int,int>> available_point(int pos[15][15]){
    int i,j;
    vector<pair<int,int>> v;
    for(i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(pos[i][j]==0&&has_near_point(pos,i,j)){
                pair<int,int> point;
                point.first=i;
                point.second=j;
                v.push_back(point);
            }
        }
    }
    return v;
}

result *find_player_min(int pos[15][15],int depth,int alpha,int beta){
    const vector<pair<int,int>> av_p=available_point(pos);
    const int length=av_p.size();
    if(is_over(pos)||depth<=1){
        int temp;
        int i;
        int player_best=INT_MAX;
        result *player=new result;
        for(i=0;i<length;i++){
            pos[av_p[i].first][av_p[i].second]=1;
            temp=get_total_score(pos,2)-get_total_score(pos,1);
            if(player_best>temp){
                player_best=temp;
                player->score=player_best;
                player->point.first=av_p[i].first;
                player->point.second=av_p[i].second;
            }
            pos[av_p[i].first][av_p[i].second]=0;
        }
        return player;
    }
    int best=INT_MAX;
    int i;
    result *bestplayer=new result;
    for(i=0;i<length;i++){
        pos[av_p[i].first][av_p[i].second]=1;
        int temp=find_ai_max(pos,depth-1,alpha,beta)->score;
        pos[av_p[i].first][av_p[i].second]=0;
        if(best>temp){
            best=temp;
            bestplayer->score=best;
            bestplayer->point.first=av_p[i].first;
            bestplayer->point.second=av_p[i].second;
        }
        beta=min_of_two(beta, temp);
        if(beta<=alpha){
            break;
        }
    }
    return bestplayer;
}

result *find_ai_max(int pos[15][15],int depth,int alpha,int beta){
    const vector<pair<int,int>> av_p=available_point(pos);
    const int length=av_p.size();
    if(is_over(pos)||depth<=1){
        int temp;
        int i;
        int ai_best=INT_MIN;
        result *ai=new result;
        for(i=0;i<length;i++){
            pos[av_p[i].first][av_p[i].second]=2;
            temp=get_total_score(pos,2)-get_total_score(pos,1);
            if(ai_best<temp){
                ai_best=temp;
                ai->score=ai_best;
                ai->point.first=av_p[i].first;
                ai->point.second=av_p[i].second;
            }
            pos[av_p[i].first][av_p[i].second]=0;
        }
        return ai;
    }
    int best=INT_MIN;
    int i;
    result *bestai=new result;
    for(i=0;i<length;i++){
        pos[av_p[i].first][av_p[i].second]=2;
        int temp=find_player_min(pos,depth-1,alpha,beta)->score;
        pos[av_p[i].first][av_p[i].second]=0;
        if(best<temp){
            best=temp;
            bestai->score=best;
            bestai->point.first=av_p[i].first;
            bestai->point.second=av_p[i].second;
        }
        alpha=max_of_two(alpha,temp);
        if(beta<=alpha){
            break;
        }
    }
    return bestai;
}

pair<int,int> ai_make_move(int pos[15][15]){
    pair<int,int> ai_best_point(find_ai_max(pos,4,INT_MIN,INT_MAX)->point);
    //ai_best_point.first=find_ai_max(pos,2)->point.first;
    //ai_best_point.second=find_ai_max(pos,2)->point.second;
    return ai_best_point;
};