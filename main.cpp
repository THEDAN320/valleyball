#include <fstream>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;
using std::to_string;

void logs_game(int &command, int &action, int &player){
    
    ofstream log_file("logs.txt",std::ios::app);
    string action_str;
    
    if (action == 1) action_str += "attack";
    else if (action == 2)    action_str += "block";
    else if (action == 3)    action_str += "attack";
    else if (action == 4)    action_str += "error";

    string log = "The team that received the point - " + to_string(command) + ", action - " + action_str + ", player - ";

    if (player < 0) log += "None";
    else    log += to_string(player);
    
    log_file << log << endl;
    log_file.close();
}

void logs_replacement(int &command,int &who, int &by_whom){
    
    ofstream log_file("logs.txt",std::ios::app);
    
    string log = "from command - " + to_string(command) + ", player " + to_string(who) + " was replace player " + to_string(by_whom);
    log_file << log << endl;
    
    log_file.close();
}

void bd_log(int &winner_command){
    
    ofstream bd_file("bd.txt",std::ios::app);
    
    bd_file << "Winner team - " + to_string(winner_command) << endl << "Losing team commentary - ``They just got lucky...``" << endl;
    bd_file.close();
}

void command_out(int *command_A, int *command_B)
{
    cout << "first:   second:" << endl;

    for (int i = 0; i < 3; i++){
        cout << command_A[i] << " ";
    } cout << "    ";
    
    for (int i = 0; i < 3; i++){
        cout << command_B[i] << " ";
    } cout << endl;
    
    for (int i = 5; i > 2; i--){
        cout << command_A[i] << " ";
    } cout << "    ";
    
    for (int i = 5; i > 2; i--){
        cout << command_B[i] << " ";
    } cout << endl;
}

void permutation(int *command)
{
    int num = command[5];

    for (int i = 5; i > 0; i--){
        command[i] = command[i - 1];
    } command[0] = num;
}

void replacement(int *command,int command_number)
{
    int whom, by_whom, i;
    bool player = true;
    char choice;

    do{
        cout << "Whom do you want to replace? - ";
        cin >> whom;

        for (i = 0; i < 6; i++){
            if (command[i] == whom){
                player = false;
                break;
            }
        }
        
        if (player) cout << "Invalid player!" << endl;
        
    } while (player);

    cout << "By whom do you want to replace? - ";
    cin >> by_whom;
    cout << "Confirm?[E or N] - ";
    cin >> choice;

    if (choice == 'E'){
        
        command[i] = by_whom;
        logs_replacement(command_number,whom,by_whom);
        cout << endl;
    }
}

void game(int *command_A, int *command_B, int &A_win, int &B_win){
    while (A_win < 3 and B_win < 3){
        
        int A_score = 0, B_score = 0, last_win, who_win, action;

        while ((A_score < 25 and B_score < 25) or !(A_score - B_score > 1 or B_score - A_score > 1)){
            
            int player_number = -1;
            cout << "score - " << A_win << "(" << A_score << ") - " << B_win << "(" << B_score << ")" << endl;
            command_out(command_A, command_B);
            cout << "Enter the winning team[1 or 2]\nreplacement player[3] - ";
            cin >> who_win;
            cout << endl;

            if (who_win == 3){
                
                int command = 0;

                cout << "what command? - ";
                cin >> command;

                if (command == 1) replacement(command_A,1);
                else replacement(command_B,2);
                continue;
            }

            cout << "Enter action:\n1 - attack\n2 - block\n3 - serving\n4 - error\n - ";
            cin >> action;
            cout << endl;

            if (action != 4){
                bool ok = true;
                do{
                    
                    cout << "Which player? - ";
                    cin >> player_number;

                    if (who_win == 1){
                        for (int i = 0; i < 6; i++){
                            if (command_A[i] == player_number){
                                ok = false;
                                break;
                            }
                        }
                    } else {
                        for (int i = 0; i < 6; i++){
                            if (command_B[i] == player_number){
                                ok = false;
                                break;
                            }
                        }
                    }
                    
                    if (ok) cout << "invalid player!" << endl;
                } while (ok);
                
                cout << endl;
            }
            
            logs_game(who_win, action, player_number);
            
            if (last_win != who_win){
                if (who_win == 1){
                    A_score++;
                    permutation(command_A);
                    
                } else{
                    permutation(command_B);
                    B_score++;
                }
                last_win = who_win;
                
            } else{
                if (who_win = 1) A_score++;
                else B_score++;
            }
        }
        
        if (A_score > B_score) A_win++;
        else B_win++;
    }
    if(A_win > B_win) bd_log(A_win);
    else bd_log(B_win);
}

int main(){
    int command_A[6] = {1, 2, 3, 4, 5, 6};
    int command_B[6] = {11, 12, 13, 14, 15, 16};
    int A_win = 0, B_win = 0;
    game(command_A, command_B, A_win, B_win);
}
