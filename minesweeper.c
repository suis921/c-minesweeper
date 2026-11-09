#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "co.h"


/*ゲームレベル別の固定値*/
#define Lv1 9
#define Lv2 13
#define Lv3 18
#define Lv1_bombs 10
#define Lv2_bombs 30
#define Lv3_bombs 50

int gameLv, bombs, opened_bombs = 0, leftBombs;

/*盤面表示に関する変数*/
char Cell_elements[12][6] = {"🔳", "１", "２", "３", "４", "５", "６", "７", "８", "🔲", "🚩", "💣"};

/*盤面の表示*/
void drawBoard(int board[gameLv][gameLv], int current[gameLv][gameLv], int view[gameLv][gameLv]){
    /*viewBoardに基づいて盤面表示*/
        for(int i = 0; i < gameLv; i++){
            for(int j = 0; j < gameLv; j++){
                if(current[i][j] == 1){
                    if(view[i][j] == 0){
                        printf("\x1b[42m%s", Cell_elements[9]);
                    }
                    else if(view[i][j] == 2){
                        printf("\x1b[42m%s", Cell_elements[10]);
                    }
                    else if(view[i][j] == 1){
                        printf("\x1b[42m%s", Cell_elements[board[i][j]]);
                    }

                }
                else if(current[i][j] == 2){
                    if(view[i][j] == 0){
                        printf("\x1b[41m%s", Cell_elements[9]);
                    }
                    else if(view[i][j] == 2){
                        printf("\x1b[41m%s", Cell_elements[10]);
                    }
                    else if(view[i][j] == 1){
                        printf("\x1b[41m%s", Cell_elements[board[i][j]]);
                    }

                }
                else{
                    if(view[i][j] == 0){
                        printf("\x1b[49m%s", Cell_elements[9]);
                    }
                    else if(view[i][j] == 2){
                        printf("\x1b[49m%s", Cell_elements[10]);
                    }
                    else if(view[i][j] == 1){
                        printf("\x1b[49m%s", Cell_elements[board[i][j]]);
                    }
                }
            }
            printf("\n");
        }
        printf("\x1b[49m");

    }

int main(){

    srand(time(NULL));

    int l, openTimes = 0;

    /*ゲームレベルの取得*/
    while(1){
        printf("難易度を選んでください : レベル1...%d×%d, レベル2... %d×%d, レベル3... %d×%d >>> ", Lv1, Lv1, Lv2, Lv2, Lv3, Lv3);
        scanf("%d", &l);
        if(l == 1){
            gameLv = Lv1;
            bombs = Lv1_bombs;
            break;
        }
        else if(l == 2){
            gameLv = Lv2;
            bombs = Lv2_bombs;
            break;
        }
        else if(l = 3){
            gameLv = Lv3;
            bombs = Lv3_bombs;
            break;
        }
        else{
            printf("もう一度入力してください。\n");
            }
    }

    printf("レベル%dでゲームを開始します\n", l);
    printf("お待ちください...\n");

    sleep(2);

    /*レベル別盤面の定義、初期化*/
    int gameBoard[gameLv][gameLv];
    for(int i = 0; i < gameLv; i++){
        for(int j = 0; j < gameLv; j++){
            gameBoard[i][j] = 0;
        }
    }

    /*表示用の盤面の定義*/
    int viewBoard[gameLv][gameLv];
    for(int i = 0; i < gameLv; i++){
        for(int j = 0; j < gameLv; j++){
            viewBoard[i][j] = 0;
        }
    }

    /*カーソル現在地処理の配列定義、初期位置を左上に*/
    int currentCell[gameLv][gameLv];
    for(int i = 0; i < gameLv; i++){
        for(int j = 0; j < gameLv; j++){
            currentCell[i][j] = 0;
        }
    }
    currentCell[0][0] = 1;

    /*最初の盤面を表示*/
    drawBoard(gameBoard, currentCell, viewBoard);
    printf("left bombs : %d\n", bombs);

    /*キー入力によるゲーム操作*/
    while(1){
        if(kbhit()){

            char key = getch();

            switch(key){
                case 'w':
                    /*カーソル上移動*/
                    for(int j = 0; j < gameLv; j++){
                        for(int i = 0; i < gameLv; i++){
                            if(currentCell[i][j] == 1){
                                if(i == 0){
                                    currentCell[gameLv - 1][j] = 1;
                                }
                                else{
                                    currentCell[i - 1][j] = 1;
                                }
                                currentCell[i][j] = 0;
                                break;
                            }
                        }
                    }
                    break;

                case 'a':
                    /*カーソル左移動*/
                    for(int i = 0; i < gameLv; i++){
                        for(int j = 0; j < gameLv; j++){
                            if(currentCell[i][j] == 1){
                                if(j == 0){
                                    currentCell[i][gameLv - 1] = 1;
                                }
                                else{
                                    currentCell[i][j - 1] = 1;
                                }
                                currentCell[i][j] = 0;
                                break;
                            }
                        }
                    }
                    break;

                case 's':
                    /*カーソル下移動*/
                    for(int j = 0; j < gameLv; j++){
                        for(int i = 0; i < gameLv; i++){
                            if(currentCell[i][j] == 1){
                                if(i == (gameLv - 1)){
                                    currentCell[0][j] = 1;
                                }
                                else{
                                    currentCell[i + 1][j] = 1;
                                }
                                currentCell[i][j] = 0;
                                break;
                            }
                        }
                    }
                    break;

                case 'd':
                    /*カーソル右移動*/
                    for(int i = 0; i < gameLv; i++){
                        for(int j = 0; j < gameLv; j++){
                            if(currentCell[i][j] == 1){
                                if(j == (gameLv - 1)){
                                    currentCell[i][0] = 1;
                                }
                                else{
                                    currentCell[i][j + 1] = 1;
                                }
                                currentCell[i][j] = 0;
                                break;
                            }
                        }
                    }
                    break;

                case 'o':
                    /*マスのオープン処理、最初の場合は爆弾配置*/
                    if(openTimes == 0){

                        /*オープン*/
                        for(int i = 0; i < gameLv; i++){
                            for(int j = 0; j < gameLv; j++){
                                if(currentCell[i][j] == 1)viewBoard[i][j] = 1;
                            }
                        }

                        /*爆弾配置*/
                        //たまに爆弾が増えることがある。減ることもある
                        int b;
                        int bombPlotX, bombPlotY;
                        for(b = 0; b < bombs; b++){
                            bombPlotX = rand()%(gameLv);
                            bombPlotY = rand()%(gameLv);
                            for(int i = 0; i < gameLv; i++){
                                for(int j = 0; j < gameLv; j++){
                                    if(currentCell[bombPlotX][bombPlotY] != 1){
                                        gameBoard[bombPlotX][bombPlotY] = 11;
                                    }
                                    else{
                                        b--;
                                    }
                                }
                            }
                        }

                        leftBombs = 0;
                        for(int i = 0; i < gameLv; i++){
                            for(int j = 0; j < gameLv; j++){
                                if(gameBoard[i][j] == 11)leftBombs++;
                            }
                        }

                        /*爆弾数表示設定*/
                        int countbombs;
                        for(int i = 0; i < gameLv; i++){
                            for(int j = 0; j < gameLv; j++){
                                if(gameBoard[i][j] != 11){
                                    countbombs = 0;
                                    if(i == 0 && j == 0){
                                        if(gameBoard[i][j + 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j] == 11)countbombs++;
                                        if(gameBoard[i + 1][j + 1] == 11)countbombs++;
                                    }
                                    else if(i == 0 && j == (gameLv - 1)){
                                        if(gameBoard[i][j - 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j] == 11)countbombs++;
                                    }
                                    else if(i == (gameLv - 1) && j == 0){
                                        if(gameBoard[i + 1][j] == 11)countbombs++;
                                        if(gameBoard[i + 1][j + 1] == 11)countbombs++;
                                        if(gameBoard[i][j + 1] == 11)countbombs++;
                                    }
                                    else if(i == (gameLv - 1) && j == (gameLv - 1)){
                                        if(gameBoard[i - 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i - 1][j] == 11)countbombs++;
                                        if(gameBoard[i][j - 1] == 11)countbombs++;
                                    }
                                    else if(i == 0 && j != 0 && j != (gameLv - 1)){
                                        if(gameBoard[i][j - 1] == 11)countbombs++;
                                        if(gameBoard[i][j + 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j] == 11)countbombs++;
                                        if(gameBoard[i + 1][j + 1] == 11)countbombs++;
                                    }
                                    else if(i == (gameLv - 1) && j != 0 && j != (gameLv - 1)){
                                        if(gameBoard[i - 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i - 1][j] == 11)countbombs++;
                                        if(gameBoard[i - 1][j + 1] == 11)countbombs++;
                                        if(gameBoard[i][j - 1] == 11)countbombs++;
                                        if(gameBoard[i][j + 1] == 11)countbombs++;
                                    }
                                    else if(j == 0 && i != 0 && i != (gameLv - 1)){
                                        if(gameBoard[i - 1][j] == 11)countbombs++;
                                        if(gameBoard[i - 1][j + 1] == 11)countbombs++;
                                        if(gameBoard[i][j + 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j] == 11)countbombs++;
                                        if(gameBoard[i + 1][j + 1] == 11)countbombs++;
                                    }
                                    else if(j == (gameLv - 1) && i != 0 && i != (gameLv - 1)){
                                        if(gameBoard[i - 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i - 1][j] == 11)countbombs++;
                                        if(gameBoard[i][j - 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j] == 11)countbombs++;
                                    }
                                    else{
                                        if(gameBoard[i - 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i - 1][j] == 11)countbombs++;
                                        if(gameBoard[i - 1][j + 1] == 11)countbombs++;
                                        if(gameBoard[i][j - 1] == 11)countbombs++;
                                        if(gameBoard[i][j + 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j - 1] == 11)countbombs++;
                                        if(gameBoard[i + 1][j] == 11)countbombs++;
                                        if(gameBoard[i + 1][j + 1] == 11)countbombs++;
                                    }
                                    gameBoard[i][j] = countbombs;
                                }
                            }
                        }

                        openTimes++;
                        break;
                    }

                    else{
                        for(int i = 0; i < gameLv; i++){
                            for(int j = 0; j < gameLv; j++){
                                if(currentCell[i][j] == 1)viewBoard[i][j] = 1;

                                //ゲームオーバー
                                system("clear");
                                if(currentCell[i][j] == 1 && gameBoard[i][j] == 11){
                                    for(i = 0; i < gameLv; i++){
                                        for(j = 0; j < gameLv; j++){
                                            viewBoard[i][j] = 1;
                                            if(currentCell[i][j] == 1)currentCell[i][j] = 2;
                                        }
                                    }
                                    drawBoard(gameBoard, currentCell, viewBoard);
                                    printf("Game Over\n");
                                    return 0;
                                }
                            }
                        }
                    }
                    break;

                case 'p':
                    /*旗置き・除去*/
                    for(int i = 0; i < gameLv; i++){
                        for(int j = 0; j < gameLv; j++){
                            if(currentCell[i][j] == 1){
                                if(viewBoard[i][j] == 0){
                                    viewBoard[i][j] = 2;
                                    leftBombs--;
                                }
                                else if(viewBoard[i][j] == 2){
                                    viewBoard[i][j] = 0;
                                    leftBombs++;
                                }
                            }
                        }
                    }
                    break;

                }
        }

        int judgeClear = 0;
        for(int i = 0; i < gameLv; i++){
            for(int j = 0; j < gameLv; j++){
                if(gameBoard[i][j] != 11 && viewBoard[i][j] != 1){
                    judgeClear++;
                }
            }
        }
        if(judgeClear == 0){
            for(int i = 0; i < gameLv; i++){
                for(int j = 0; j < gameLv; j++){
                    currentCell[i][j] = 0;
                    viewBoard[i][j] = 1;
                }
            }
            drawBoard(gameBoard, currentCell, viewBoard);
            printf("\n");
            printf("Game Clear!\n");
            break;
        }

        system("clear");
        drawBoard(gameBoard, currentCell, viewBoard);
        printf("\n");
        if(openTimes == 0){
            printf("WASD : 移動\np : 旗を設置\no : マスを開ける\n💣 : %d\n", bombs);
        }
        else{
            printf("WASD : 移動\np : 旗を設置\no : マスを開ける\n💣 : %d\n", leftBombs);
        }
    }

    return 0;
}