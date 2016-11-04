/*
 * File: Battleship.c
 * Author: Benlong Huang
 * Purpose: Defines the game.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

int main(){
    int check[5] = {0,0,0,0,0};
    // create a gameboard and fill O in all the blank space.
    int row, col;
    char gameboard [10] [10];
    for(row =0; row < 10; row++){
        for(col = 0; col < 10 ; col ++){
            gameboard [row] [col] = 'O';
        }
    }
    // determine the format of input, one char and four int. Then scan it out.
    char shiptype;
    int x1,y1,x2,y2;
    int i;//j;
    // loop begin to search for error.
    for(i = 0; i < 5 ; i++){
    int input = scanf(" %c %d %d %d %d", &shiptype, &x1 , &y1, &x2, &y2 );
    // Error 1: determine whether the input value is enough. If it's less than 5 then it wrong.
    if(input < 5){
        fprintf(stderr, "Input error: not enough values (read %d values out of 5)\n",input);
        return 1;
    }

    // Error 2: determine whether the first place is char, means whether it's a ship or not.
    if(!isalpha(shiptype)){
        fprintf(stderr,"ERROR: Unrecognized ship type %c\n",shiptype);
        return 1;
    }
    // Error 3: determine whether the ship is parallel.
    if((x1 != x2)&&(y1 != y2)){
        fprintf(stderr,"Illegal placement: invalid coordinates: (%d, %d), (%d, %d)\n", x1,y1,x2,y2);
        return 1;
    }
    
    // Error 4: determine whether the ship is out of gameboard.
    if(x1 >= 10 || y1 >= 10 || x2 >= 10 || y2 >= 10){
        fprintf(stderr,"Illegal placement: invalid coordinates: (%d, %d), (%d, %d)\n", x1,y1,x2,y2);
        return 1;
    }
    // Error 5: determine whether the ship has the correct size related to the type of ship
    int shiplength = 0;
    if(x1 == x2){
        shiplength = max(y1,y2) - min(y1,y2) + 1;
    }
    if(y1 == y2){
        shiplength = max(x1,x2) - min(x1,x2) + 1;
    }
    if(shiptype == 'A'){
        if(shiplength != 5 ){
            fprintf(stderr,"Illegal placement: Incorrect length %d for shiptype = %c\n", shiplength, shiptype);
            return 1;
        }
    }
    if(shiptype == 'B'){
        if(shiplength != 4 ){
            fprintf(stderr,"Illegal placement: Incorrect length %d for shiptype = %c\n", shiplength, shiptype);
            return 1;
        }
    }
    if(shiptype == 'S'){
        if(shiplength != 3 ){
            fprintf(stderr,"Illegal placement: Incorrect length %d for shiptype = %c\n", shiplength, shiptype);
            return 1;
        }
    }
    if(shiptype == 'D'){
        if(shiplength != 3 ){
            fprintf(stderr,"Illegal placement: Incorrect length %d for shiptype = %c\n", shiplength, shiptype);
            return 1;
        }
    }
    if(shiptype == 'P'){
        if(shiplength != 2 ){
            fprintf(stderr,"Illegal placement: Incorrect length %d for shiptype = %c\n", shiplength, shiptype);
            return 1;
        }
    }
    
    // Error 6: determine whether the ship is overlapping with others.
    int maxy = max(y1,y2);
    int miny = min(y1,y2);
    int maxx = max(x1,x2);
    int minx = min(x1,x2);
    // if the x coordinate is the same, means they are perpendicular with each other. then check every point below, check whether every point is fill a 'O'.
    if(x1 == x2){
    while(maxy >= miny){
        if( gameboard [maxy - miny] [x1] != 'O'){
            fprintf(stderr, "Illegal placement: overlap at (%d,%d)\n", maxy-miny,x1);
            return 1;
             }
        maxy--;
    }
}
    else{
    while(maxx >= minx){
        if( gameboard [y1] [maxx - minx] != 'O'){
            fprintf(stderr, "Illegal placement: overlap at (%d,%d)\n", y1, maxx - minx);
            return 1;
        }
        maxx--;
    }
}
    // Error 7: determine whether the ship is the exact ship contains in this game. Only A B S D P means the specific ship, others are not.
    if(shiptype != 'A' && shiptype != 'B' && shiptype != 'S' && shiptype != 'D' && shiptype != 'P'){
        fprintf(stderr, "ERROR: Unrecognized ship type %c\n", shiptype);
        return 1;
    }
        int a;
    // if the value pass all the values then pass it in.
    if(x1 == x2){
        for(a = miny;a <= max(y1,y2);a++){
            gameboard[a][x1] = shiptype;
            
    }
        // Error 8: determine whether the ship is repeatly placed.
        
        if(shiptype == 'A')
            check[0] = 1;
        if(shiptype == 'B')
            check[1] = 1;
        if(shiptype == 'S')
            check[2] = 1;
        if(shiptype == 'D')
            check[3] = 1;
        if(shiptype == 'P')
            check[4] = 1;
}
    if(y1 == y2){
        for(a = minx;a <= max(x1,x2); a++){
            gameboard[y1][a] = shiptype;
    }
        // Error 8: determine whether the ship is repeatly placed.
        
        if(shiptype == 'A')
            check[0] = 1;
        if(shiptype == 'B')
            check[1] = 1;
        if(shiptype == 'S')
            check[2] = 1;
        if(shiptype == 'D')
            check[3] = 1;
        if(shiptype == 'P')
            check[4] = 1;
}
        
    
    
}
    // if there is one of the shiptype is 0, then it means not all the ship type be placed.
    if (check[0]!=1||check[1]!=1||check[2]!=1||check[3]!=1||check[4]!=1) {
        fprintf(stderr, "Error: not all ship types placed\n");
        return 1;
    }
    int result = 0;

// BEGIN TO GUESS
    int A = 0, B = 0, S = 0, D = 0, P = 0;
    int input1 = 0, input2 = 0;
    int number = 0;
    // 5 is the size of A, 4 is the size of B, 3 is the size of S and D, 2 is the size of P.
    int shipsize[5] = {5,4,3,3,2};
    while((number = scanf("%d %d",&input1,&input2)) != EOF){
        // Error 1: determine whether the number of input is enough or not.
        if(number != 2){
            fprintf(stderr,"error: illegal input character(s)\n");
            return 1;
        }
        // Error 2: determine whether the value of input is in range.
        if(input1 > 9 || input2 > 9 || input1 < 0 || input2 < 0){
            fprintf(stderr,"error: illegal guess (%d, %d)\n",input2,input1);
            result = 1;
            continue;
        }
        // if the gameboard is still full with O means, the guess missed. else it means it hit.
        if(gameboard[input2][input1]=='O'){
            printf("miss\n");
        }
        // if the input is equal to A B S D or P, then the size of the ship decrease, then the size become to 0, then the ship sunk.
        else{
            if(gameboard[input2][input1]=='A'){
                shipsize[0]--;
            }
            if(gameboard[input2][input1]=='B'){
                shipsize[1]--;
            }
            if(gameboard[input2][input1]=='S'){
                shipsize[2]--;
            }
            if(gameboard[input2][input1]=='D'){
                shipsize[3]--;
            }
            if(gameboard[input2][input1]=='P'){
                shipsize[4]--;
            }
            
            
            if(shipsize[0]== 0 && A == 0){
                printf("A sunk\n");
                A = 1;
            }
            else if(shipsize[1]== 0 && B == 0){
                B = 1;
                printf("B sunk\n");
            }
            else if(shipsize[2]== 0 && S == 0){
                printf("S sunk\n");
                S = 1;
            }
            else if(shipsize[3]== 0 && D == 0){
                printf("D sunk\n");
                D = 1;
            }
            else if(shipsize[4]== 0 && P == 0){
                printf("P sunk\n");
                P = 1;
            }
            else
                printf("hit\n");
            // if all the ship size become 0, then all the ship sunk, game is over.
            if(shipsize[0]== 0 && shipsize[1]== 0 && shipsize[2]== 0 && shipsize[3]== 0 && shipsize[4]== 0){
                printf("all ships sunk: game over\n");
                break;
            }
            
        }
        
    }
    
    return result;
}
    
    


    
    
    

