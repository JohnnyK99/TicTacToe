#include <iostream>

using namespace std;

//10 - 'X'
//11 - 'O'
//00 - empty field

void show(int board){

    for(int i = 0; i < 16; i++){

        switch (board & 0b11){
            case 0:{
                cout<<"- ";
                break;
            }
            case 2:{
                cout<<"X ";
                break;
            }
            case 3:{
                cout<<"O ";
                break;
            }
            default:
                cout<<"E ";
        }
        board >>= 2;

        if(i % 4 == 3)
            cout<<endl;
    }
}

bool full(int board){

    for(int i = 0; i < 16; i++){
        if((board & 0b11) == 0)
            return false;
        board >>= 2;
    }
    return true;
}

bool free(int board, int place){

    return (((board >> (2*place-2)) & 0b11) == 0);
}


void put(int* board, int place, int sign){

    sign <<= (2*place-2);
    *board += sign;

}

bool win(int board){

    //checking rows
    for(int i = 0; i <= 24; i += 8){
        if((board>>i & 0b11) != 0  && ((board>>i & 0b11) == (board>>(i+2) & 0b11)) && ((board>>i & 0b11) == (board>>(i+4) & 0b11)) && ((board>>i & 0b11) == (board>>(i+6) & 0b11)))
            return true;
    }

    //checking columns
    for(int i = 0; i <= 6; i += 2){
        if((board>>i & 0b11) != 0  && ((board>>i & 0b11) == (board>>(8+i) & 0b11)) && ((board>>i & 0b11) == (board>>(16+i) & 0b11)) && ((board>>i & 0b11) == (board>>(24+i) & 0b11)))
            return true;
    }

    //checking the  right diagonal
    if((board & 0b11) != 0  && ((board & 0b11) == (board>>10 & 0b11)) && ((board & 0b11) == (board>>20 & 0b11)) && ((board & 0b11) == (board>>30 & 0b11)))
        return true;

    //checking the left diagonal
    if((board>>6 & 0b11) != 0  && ((board>>6 & 0b11) == (board>>12 & 0b11)) && ((board>>6 & 0b11) == (board>>18 & 0b11)) && ((board>>6 & 0b11) == (board>>24 & 0b11)))
        return true;

    return false;
}

int getPosition(int board){

    int tmp;
    do{
        cin>>tmp;
        if(tmp < 1 || tmp > 16)
            cout<<"Invalid number, enter a different value:";
        else if(!free(board, tmp))
            cout<<"This field is taken, enter a different value:";
    } while (!free(board, tmp) || tmp < 1 || tmp > 16);

    return tmp;
}

int main() {

    int board = 0;

    cout<<"Field numbers: \n1  | 2  | 3  | 4\n5  | 6  | 7  | 8\n9  | 10 | 11 | 12\n13 | 14 | 15 | 16\n";
    show(board);

    while(true){
        //player O move
        cout<<"Player O: ";
        put(&board, getPosition(board), 0b11);
        show(board);
        if(win(board)){
            cout<<"PLAYER O WINS!\n";
            return 0;
        }
        if(full(board)){
            cout<<"DRAW\n";
            return 0;
        }

        //player X move
        cout<<"Player X: ";
        put(&board, getPosition(board), 0b10);
        show(board);
        if(win(board)){
            cout<<"PLAYER X WINS!\n";
            return 0;
        }
        if(full(board)){
            cout<<"DRAW\n";
            return 0;
        }
    }

}

