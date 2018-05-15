//
// Created by victor on 2018/5/9.
//

#include "basic.h"
void print_canvas(int pos[15][15]){
    int i,j;
    cout<<" 1   2   3   4   5   6   7   8   9   "
        <<"10  11  12  13  14  15"<<endl;
    for(i=0;i<14;i++){
        cout<<char(i+97);
        for(j=0;j<14;j++){
            if(pos[i][j]==0) cout<<"+---";
            else if(pos[i][j]==1) cout<<"x---";
            else if(pos[i][j]==2) cout<<"o---";
        }
        if(pos[i][j+1]==0) cout<<"+"<<endl<<" ";
        else if(pos[i][j+1]==1) cout<<"x"<<endl<<" ";
        else if(pos[i][j+1]==2) cout<<"o"<<endl<<" ";
        for(j=0;j<14;j++){
            cout<<"|   ";
        }
        cout<<"|"<<endl;
    }
    i=14;
    cout<<char(i+97);
    for(j=0;j<14;j++){
        if(pos[i][j]==0) cout<<"+---";
        else if(pos[i][j]==1) cout<<"x---";
        else if(pos[i][j]==2) cout<<"o---";
    }
    if(pos[i][14]==0) cout<<"+"<<endl<<" ";
    else if(pos[i][14]==1) cout<<"x"<<endl<<" ";
    else if(pos[i][14]==2) cout<<"o"<<endl<<" ";
}

int get_row(char *input){
    return int(input[0])-97;
}

int get_column(char *input){
    char temp[2];
    temp[0]=input[1];
    temp[1]=input[2];
    return atoi(temp)-1;
}

bool check_input(char *input){
    if(int(input[0])>111||int(input[0]<97)) return false;
    else if(int(input[1])>57||int(input[1]<48)) return false;
    else{
        if(get_column(input)<0||get_column(input)>14) return false;
        else{
            return true;
        }
    }
}

bool is_taken(int pos[15][15],char *input){
    int row=get_row(input);
    int column=get_column(input);
    if(pos[row][column]==0) return true;
    else return false;
}

int is_over(int pos[15][15]){
    int i,j;
    //横排
    for(i=0;i<15;i++){
        vector<int> n;
        for(j=0;j<15;j++) n.push_back(pos[i][j]);
        if(count_five(n,1)) return 1;
        else if(count_five(n,2)) return 2;
        n.clear();
    }
    //竖排
    for(j=0;j<15;j++){
        vector<int> n;
        for(i=0;i<15;i++) n.push_back(pos[i][j]);
        if(count_five(n,1)) return 1;
        else if(count_five(n,2)) return 2;
        n.clear();
    }
    //上半正斜
    for(i=0;i<15;i++){
        vector<int> n;
        int x,y;
        for(x=i,y=0;x<15 && y<15;x++,y++) n.push_back(pos[x][y]);
        if(count_five(n,1)) return 1;
        else if(count_five(n,2)) return 2;
        n.clear();
    }
    //下半正斜
    for(j=1;j<15;j++){
        vector<int> n;
        int x,y;
        for(x=0,y=j;x<15 && y<15;x++,y++) n.push_back(pos[x][y]);
        if(count_five(n,1)) return 1;
        else if(count_five(n,2)) return 2;
        n.clear();
    }
    //上半反斜
    for(i=0;i<15;i++){
        vector<int> n;
        int x,y;
        for(x=i,y=0;x>=0 && y<15;x--,y++) n.push_back(pos[x][y]);
        if(count_five(n,1)) return 1;
        else if(count_five(n,2)) return 2;
        n.clear();
    }
    //下半反斜
    for(j=1;j<15;j++){
        vector<int> n;
        int x,y;
        for(x=14,y=j;x>=0 && y<15;x--,y++) n.push_back(pos[x][y]);
        if(count_five(n,1)) return 1;
        else if(count_five(n,2)) return 2;
        n.clear();
    }
    return 0;
}

bool count_five(vector<int> n, int turn) {
    int number = 0;
    int i = 0;
    int length = n.size();
    while (i < length) {
        if (n[i] == turn) {
            number++;
            if (number >= 5) return true;
        } else number = 0;
        i++;
    }
    return false;
}