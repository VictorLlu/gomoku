#include <iostream>
#include <vector>
#include <cstring>
#include "wuziqi_ai.h"
#include "basic.h"
using namespace std;
const char NO[3]="no";
const char YES[4]="yes";
const char UNDO[5]="undo";

int main() {
    char tryagain[4]="yes";
    while(strcmp(tryagain,YES)==0){
        int choice_turn;
        cout<<"Who take first turn?"<<endl<<"1. player"<<endl<<"2. ai"<<endl;
        cin>>choice_turn;
        while(choice_turn!=1&&choice_turn!=2){
            cout<<"Wrong input! Who take first turn?"<<endl<<"1. player"<<endl<<"2. ai"<<endl;
            cin>>choice_turn;
        }
        if(choice_turn==1){
            int position[15][15];
            int i,j;
            int player_row=0;
            int player_column=0;
            int ai_row=0;
            int ai_column=0;
            char input[3];
            char choice[3]="1";
            for(i=0;i<15;i++) for (j=0;j<15;j++) position[i][j]=0;
            print_canvas(position);
            while(strcmp(choice,NO)!=0){
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
                cout<<"ai:"<<char(ai_row+97)<<ai_column+1<<endl;
                if(is_over(position)==1){
                    cout<<"You win!"<<endl;
                    break;
                }
                else if(is_over(position)==2){
                    cout<<"You lose!"<<endl;
                    break;
                }
                else {
                    cout<<"Do you want to continue?(yes/no) If you want to withdraw the move, input undo."<<endl;
                    cin>>choice;
                }
                if(strcmp(choice,UNDO)==0){
                    position[player_row][player_column]=0;
                    position[ai_row][ai_column]=0;
                    print_canvas(position);
                    strcpy(choice,YES);
                }
            }
            cout<<"Do you want to try again?(yes/no)"<<endl;
            cin>>tryagain;
        }
        else if(choice_turn==2){
            int position[15][15];
            int i,j;
            int player_row=0;
            int player_column=0;
            int ai_row=0;
            int ai_column=0;
            char input[3];
            char choice[3]="1";
            for(i=0;i<15;i++) for (j=0;j<15;j++) position[i][j]=0;
            pair<int,int> ai_first_point(ai_init());
            ai_row=ai_first_point.first;
            ai_column=ai_first_point.second;
            position[ai_row][ai_column]=2;
            print_canvas(position);
            while(strcmp(choice,NO)!=0){
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
                cout<<"ai:"<<char(ai_row+97)<<ai_column+1<<endl;
                if(is_over(position)==1){
                    cout<<"You win!"<<endl;
                    break;
                }
                else if(is_over(position)==2){
                    cout<<"You lose!"<<endl;
                    break;
                }
                else {
                    cout<<"Do you want to continue?(yes/no) If you want to withdraw the move, input undo."<<endl;
                    cin>>choice;
                }
                if(strcmp(choice,UNDO)==0){
                    position[player_row][player_column]=0;
                    position[ai_row][ai_column]=0;
                    print_canvas(position);
                    strcpy(choice,YES);
                }
            }
            cout<<"Do you want to try again?(yes/no)"<<endl;
            cin>>tryagain;
        }
    }
    return 0;
}