#include <iostream>
#include <vector>
#include "wuziqi_ai.h"
#include "basic.h"
using namespace std;

int main() {
    int position[15][15];
    int i,j;
    int player_row=0;
    int player_column=0;
    int ai_row=0;
    int ai_column=0;
    char input[3];
    int choice=1;
    for(i=0;i<15;i++) for (j=0;j<15;j++) position[i][j]=0;
    while(choice!=0){
        cout<<"your turn: ";
        cin>>input;
        while(!check_input(input)||!is_taken(position,input)){
            if(!check_input(input)) cout<<"Input invalid! Please input again!"<<endl;
            if(!is_taken(position,input)) cout<<"The place is taken! Please input again!"<<endl;
            cin>>input;
        }
        player_row=get_row(input);
        player_column=get_column(input);
        position[player_row][player_column]=1;
        pair<int,int> ai_point(ai_make_move(position));
        ai_row=ai_point.first;
        ai_column=ai_point.second;
        position[ai_row][ai_column]=2;
        print_canvas(position);
        if(is_over(position)==1){
            cout<<"You win!"<<endl;
            break;
        }
        else if(is_over(position)==2){
            cout<<"You lose!"<<endl;
            break;
        }
        else {
            cout<<"Do you want to continue?"<<endl;
            cin>>choice;
        }
    }
    getchar();
    return 0;
}