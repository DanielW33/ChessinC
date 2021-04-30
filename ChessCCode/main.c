#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct Position{
    char Piece;
    char team;
} Tile;

typedef struct KeyPair{
    char Position[2];
    int index;
}KeyPair;

void InitTiles();
void GenerateBoard();
void PrintBoard();
void RunGame();
void KeyValuePair();
void CleanUp();
int ParseInput(char*);
void MoveGamePiece(int, int);

void* BaseBoardPosition;
void* TileList;

void init(){
    GenerateBoard();
    InitTiles();
    TileList = malloc(sizeof(KeyPair) * 64);
    KeyValuePair();
}

int main() {
    init();
    RunGame();
    CleanUp();
    return 0;
}

void RunGame(){

    char *input = malloc(sizeof(char) * 2);
    char* input2 = malloc(sizeof(char) * 2);
    char* Exit = "exit";
    int Index1, Index2;
    while(1) {

        PrintBoard();

        printf("Please enter the position of the piece you would like to move:  ");
        scanf("%s", input);

        if(strcmp(Exit, input) == 0){
            break;
        }
        printf("\nPlease enter the position where you want to move the piece to: ");
        scanf("%s", input2);
        Index1 = ParseInput(input);
        Index2 = ParseInput(input2);

        MoveGamePiece(Index1, Index2);

    }
    free(input);

}
void MoveGamePiece(int Index1, int Index2){
    Tile* Start = BaseBoardPosition + sizeof(Tile) * Index1;
    Tile* End = BaseBoardPosition + sizeof(Tile) * Index2;

    //Verify move here


    End->Piece = Start->Piece;
    Start->Piece = ' ';
}
int ParseInput(char* input){
    KeyPair* Tile;
    switch(input[0]){

        case 'A':   //0 - 7: 8 Positions
            Tile = TileList;
            break;
        case 'B':   //8 - 15: 8 Positions
            Tile = TileList + sizeof(KeyPair) * 8;
            break;
        case 'C':   //16 - 23: 8 Positions
            Tile = TileList + sizeof(KeyPair) * 16;
            break;
        case 'D':   //24 - 31: 8 Positions
            Tile = TileList + sizeof(KeyPair) * 24;
            break;
        case 'E':   //32 - 39: 8 Positions
            Tile = TileList + sizeof(KeyPair) * 32;
            break;
        case 'F':   //40 - 47: 8 Positions
            Tile = TileList + sizeof(KeyPair) * 40;
            break;
        case 'G':   //48 - 55: 8 Positions
            Tile = TileList + sizeof(KeyPair) * 48;
            break;
        default:    //56 - 63: 8 Positions
            Tile = TileList + sizeof(KeyPair) * 56;
            break;
    }
    printf("Found: %s\n", Tile->Position);
    while(Tile != NULL){
        if(Tile->Position[0] == input[0] && Tile->Position[1] == input[1]){
            break;
        }
        Tile = Tile + sizeof(KeyPair);
    }
    return Tile->index;
}
void GenerateBoard(){
    BaseBoardPosition = malloc(sizeof(Tile) * 64);
    void* End = BaseBoardPosition + sizeof(Tile) * 64;
    printf("Allocation Range: %p to %p\n", BaseBoardPosition, End);
}
void InitTiles(){
    printf("Size of tile: %d\n", sizeof(Tile));
    Tile* Ttile = BaseBoardPosition;
    Tile* Btile = BaseBoardPosition + sizeof(Tile) * 63;

    int i;
    for(i = 0; i < 16; i++){
        printf("Value of Ttile location: %p\n", Ttile);
        printf("Value of Btile location: %p\n", Btile);
        size_t s = (Ttile + sizeof(Tile)) - Ttile;
        printf("Difference: %zu\n", s);
        Ttile->team = 'A';
        Btile->team = 'B';
        if(i == 0 || i == 7){
            Ttile->Piece = 'R';
            Btile->Piece = 'R';

        }
        else if(i == 1 || i == 6){
            Ttile->Piece = 'N';
            Btile->Piece = 'N';

        }
        else if(i == 2 || i == 5){
            Ttile->Piece = 'B';
            Btile->Piece = 'B';

        }
        else if(i == 3){
            Ttile->Piece = 'K';
            Btile->Piece = 'K';

        }
        else if(i == 4){
            Ttile->Piece = 'Q';
            Btile->Piece = 'Q';

        }
        else{
            Ttile->Piece = 'P';
            Btile->Piece = 'P';

        }
        Ttile = Ttile + sizeof(Tile);
        Btile = Btile - sizeof(Tile);
    }

    Ttile = BaseBoardPosition + sizeof(struct Position) * 16;
    for(i = 16; i < 48; i++){
        if(i > 15 && i < 48){
            Ttile->Piece = ' ';
        }
        Ttile = Ttile + sizeof(Tile);
    }

}
void PrintBoard(){
    Tile* tile = ((Tile*)BaseBoardPosition);
    char myArr[64];
    int i;
    for(i = 0; i < 64; i++){
        myArr[i] = tile->Piece;
        tile = tile + sizeof(Tile);
    }
    printf("       1         2         3         4         5         6         7         8\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "A #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "B #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "C #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "D #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "E #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "F #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "G #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "H #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #    %c    #\n"
           "  #         #         #         #         #         #         #         #         #\n"
           "  #################################################################################\n",
           myArr[0],myArr[1],myArr[2],myArr[3],myArr[4],myArr[5],myArr[6],myArr[7],myArr[8],myArr[9],myArr[10],
           myArr[11],myArr[12],myArr[13],myArr[14],myArr[15],myArr[16],myArr[17],myArr[18],myArr[19],myArr[20],
           myArr[21],myArr[22],myArr[23],myArr[24],myArr[25],myArr[26],myArr[27],myArr[28],myArr[29],myArr[30],
           myArr[31],myArr[32],myArr[33],myArr[34],myArr[35],myArr[36],myArr[37],myArr[38],myArr[39],myArr[40],
           myArr[41],myArr[42],myArr[43],myArr[44],myArr[45],myArr[46],myArr[47],myArr[48],myArr[49],myArr[50],
           myArr[51],myArr[52],myArr[53],myArr[54],myArr[55],myArr[56],myArr[57],myArr[58],myArr[59],myArr[60],
           myArr[61],myArr[62],myArr[63]);

}
void KeyValuePair(){
    KeyPair* Tile = TileList;
    int i, j = 48;
    char Character = 'A';

    for(i = 0; i < 64; i++){
        if(i % 8 == 0 && i != 0){
            Character++;
            j = 48;
        }
        j++;
        Tile->Position[0] = Character;
        Tile->Position[1] = j;
        Tile->index = i;
        Tile = Tile + sizeof(KeyPair);
    }
}

void CleanUp(){
    free(BaseBoardPosition);
    free(TileList);
}