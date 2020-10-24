#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;



Game::Game()
{
    srand(time(NULL));
    first_score=0;
    second_score=0;
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            first_grid[i][j]='0';
            second_grid[i][j]='0';
            first_shots[i][j]='0';
            second_shots[i][j]='0';
        }
    }
    for(int i=0; i<5; i++)
    {
        first_ships[i]=0;
        second_ships[i]=0;
    }
    cout<<"Welcome to the game of Battleships!"<<endl;
    choose_mode();
    cout<<endl;
    setup();
    take_turns();
};

void Game::choose_mode()
{
    char mode;
    cout<<"Choose your game mode:"<<endl;
    cout<<"[1]-Player vs Computer\t[2]-Player vs Player"<<endl;
    cout<<"Choice: ";
    cin>>mode;
    if(mode=='2')
    {
        first_player="Player 1";
        second_player="Player 2";
    }
    else
    {
        first_player="Player";
        choose_diff();
    }
}

void Game::choose_diff()
{

    cout<<endl;
    char diff;
    cout<<"Choose computer difficulty:"<<endl;
    cout<<"[1]-Easy\t[2]-Hard"<<endl;
    cout<<"Choice: ";
    cin>>diff;
    if(diff=='2' || diff=='H' || diff=='h')
    {
        second_player="Computer(hard)";
    }
    else
    {
        second_player="Computer(easy)";
    }
}

void Game::setup()
{
    system("CLS");
    display_grid(1);
    cout<<first_player<<" set up your battleships!"<<endl<<"[1]-Random setup\t[2]-Manual setup"<<endl<<"Choice: ";
    char choice;
    cin>>choice;
    if(choice=='2' || choice=='M' || choice=='m')
    {
        player_setup(1);
    }
    else
    {
        random_setup(1);
    }

    if(first_player=="Player")  //PVE
    {
        random_setup(2);
    }
    else        //PVP
    {
        system("CLS");
        display_grid(2);
        cout<<second_player<<" set up your battleships!"<<endl<<"[1]-Random setup\t[2]-Manual setup"<<endl<<"Choice: ";
        char choice;
        cin>>choice;
        if(choice=='2' || choice=='M' || choice=='m')
        {
            player_setup(2);
        }
        else
        {
            random_setup(2);
        }
    }
}

void Game::player_setup(int player)
{
    ship_setup("Carrier",5,player);
    ship_setup("Battleship",4,player);
    ship_setup("Cruiser",3,player);
    ship_setup("Submarine",3,player);
    ship_setup("Destroyer",2,player);
    system("CLS");
    display_grid(player);
    Sleep(3000);
}

void Game::random_setup(int player)
{
    ship_random(5,player);
    ship_random(4,player);
    ship_random(3,player);
    ship_random(3,player);
    ship_random(2,player);
}

void Game::ship_random(int length, int player)
{
    while(1)
    {
        int x=rand()%10+1;
        int y=rand()%10+1;
        int direction=rand()%4;
        if((player==1 && (first_grid[y][x]!='0' || first_grid[y][x-1]!='0' || first_grid[y-1][x-1]!='0' ||
                          first_grid[y-1][x]!='0' || first_grid[y-1][x+1]!='0' || first_grid[y][x+1]!='0' ||
                          first_grid[y+1][x+1]!='0' || first_grid[y+1][x]!='0' || first_grid[y+1][x-1]!='0'))
                || (player==2 && (second_grid[y][x]!='0' || second_grid[y][x-1]!='0' || second_grid[y-1][x-1]!='0' ||
                                  second_grid[y-1][x]!='0' || second_grid[y-1][x+1]!='0' || second_grid[y][x+1]!='0' ||
                                  second_grid[y+1][x+1]!='0' || second_grid[y+1][x]!='0' || second_grid[y+1][x-1]!='0')))
        {
            continue;
        }

        bool pass=true;
        if(direction==0)
        {
            for(int i=1; i<length; i++)
            {
                if(x-i<1
                        || (player==1 && (first_grid[y][x-i]!='0' || first_grid[y][x-i-1]!='0' || first_grid[y-1][x-i-1]!='0' || first_grid[y+1][x-i-1]!='0'))
                        || (player==2 && (second_grid[y][x-i]!='0' || second_grid[y][x-i-1]!='0' || second_grid[y-1][x-i-1]!='0' || second_grid[y+1][x-i-1]!='0'))  )
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=0; i<length; i++)
                {
                    update_grid(x-i,y,player,'S');
                }
                break;
            }
        }

        else if(direction==1)
        {
            for(int i=1; i<length; i++)
            {
                if(y-i<1
                        || (player==1 && (first_grid[y-i][x]!='0' || first_grid[y-i-1][x-1]!='0' || first_grid[y-i-1][x]!='0' || first_grid[y-i-1][x+1]!='0'))
                        || (player==2 && (second_grid[y-i][x]!='0' || second_grid[y-i-1][x-1]!='0' || second_grid[y-i-1][x]!='0' || second_grid[y-i-1][x+1]!='0')))
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=0; i<length; i++)
                {
                    update_grid(x,y-i,player,'S');
                }
                break;
            }
        }

        else if(direction==2)
        {
            for(int i=1; i<length; i++)
            {
                if(x+i>10
                        || (player==1 && (first_grid[y][x+i]!='0' || first_grid[y-1][x+i+1]!='0' || first_grid[y][x+i+1]!='0' || first_grid[y+1][x+i+1]!='0'))
                        || (player==2 && (second_grid[y][x+i]!='0' || second_grid[y-1][x+i+1]!='0' || first_grid[y][x+i+1]!='0' || second_grid[y+1][x+i+1]!='0'))  )
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=0; i<length; i++)
                {
                    update_grid(x+i,y,player,'S');
                }
                break;
            }
        }

        else if(direction==3)
        {
            for(int i=1; i<length; i++)
            {
                if(y+i>10
                        || (player==1 && (first_grid[y+i][x]!='0' || first_grid[y+i+1][x-1]!='0' || first_grid[y+i+1][x]!='0' || first_grid[y+i+1][x+1]!='0'))
                        || (player==2 && (second_grid[y+i][x]!='0' || second_grid[y+i+1][x-1]!='0' || second_grid[y+i+1][x]!='0' || second_grid[y+i+1][x+1]!='0')))
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=0; i<length; i++)
                {
                    update_grid(x,y+i,player,'S');
                }
                break;
            }
        }

    }
}


void Game::ship_setup(string name, int length, int player)
{
    system("CLS");
    display_grid(player);
    string coordinates;
    char choice;
    cout<<"Set up your "<<name<<" ("<<length<<"x1 ship)."<<endl<<"Choose starting point of the ship by typing coordinates."<<endl<<"Choice: ";
    cin.ignore();
    getline(cin,coordinates);
    int y=find_y(coordinates);
    int x=find_x(coordinates);

    while(x<1 || x>10 || y<1 || y>10
            || (player==1 && (first_grid[y][x]!='0' || first_grid[y][x-1]!='0' || first_grid[y-1][x-1]!='0' ||
                              first_grid[y-1][x]!='0' || first_grid[y-1][x+1]!='0' || first_grid[y][x+1]!='0' ||
                              first_grid[y+1][x+1]!='0' || first_grid[y+1][x]!='0' || first_grid[y+1][x-1]!='0'))
            || (player==2 && (second_grid[y][x]!='0' || second_grid[y][x-1]!='0' || second_grid[y-1][x-1]!='0' ||
                              second_grid[y-1][x]!='0' || second_grid[y-1][x+1]!='0' || second_grid[y][x+1]!='0' ||
                              second_grid[y+1][x+1]!='0' || second_grid[y+1][x]!='0' || second_grid[y+1][x-1]!='0')))
    {
        system("CLS");
        display_grid(player);
        cout<<"Set up your "<<name<<" ("<<length<<"x1 ship)."<<endl;
        cout<<"Wrong coordinates. Type a letter from A to J followed by a number from 1 to 10."<<endl<<"Remember that ships can't be adjacent."<<endl<<"Choice: ";
        getline(cin,coordinates);
        y=find_y(coordinates);
        x=find_x(coordinates);
    }
    update_grid(x,y,player,'S');
    system("CLS");
    display_grid(player);
    cout<<"Choose direction of your "<<name<<" ("<<length<<"x1 ship)."<<endl<<"[1]-left    [2]-up    [3]-right    [4]-down    [5]-go back"<<endl<<"Choice: ";
    cin>>choice;
    bool pass=false;
    while(!pass)
    {
        pass=true;
        if(choice=='1' || choice=='l' || choice=='L')
        {
            for(int i=1; i<length; i++)
            {
                if(x-i<1
                        || (player==1 && (first_grid[y][x-i]!='0' || first_grid[y][x-i-1]!='0' || first_grid[y-1][x-i-1]!='0' || first_grid[y+1][x-i-1]!='0'))
                        || (player==2 && (second_grid[y][x-i]!='0' || second_grid[y][x-i-1]!='0' || second_grid[y-1][x-i-1]!='0' || second_grid[y+1][x-i-1]!='0'))  )
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=1; i<length; i++)
                {
                    update_grid(x-i,y,player,'S');
                }
            }
        }

        else if(choice=='2' || choice=='u' || choice=='U')
        {
            for(int i=1; i<length; i++)
            {
                if(y-i<1
                        || (player==1 && (first_grid[y-i][x]!='0' || first_grid[y-i-1][x-1]!='0' || first_grid[y-i-1][x]!='0' || first_grid[y-i-1][x+1]!='0'))
                        || (player==2 && (second_grid[y-i][x]!='0' || second_grid[y-i-1][x-1]!='0' || second_grid[y-i-1][x]!='0' || second_grid[y-i-1][x+1]!='0')))
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=1; i<length; i++)
                {
                    update_grid(x,y-i,player,'S');
                }
            }
        }

        else if(choice=='3' || choice=='r' || choice=='R')
        {
            for(int i=1; i<length; i++)
            {
                if(x+i>10
                        || (player==1 && (first_grid[y][x+i]!='0' || first_grid[y-1][x+i+1]!='0' || first_grid[y][x+i+1]!='0' || first_grid[y+1][x+i+1]!='0'))
                        || (player==2 && (second_grid[y][x+i]!='0' || second_grid[y-1][x+i+1]!='0' || second_grid[y][x+i+1]!='0' || second_grid[y+1][x+i+1]!='0'))  )
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=1; i<length; i++)
                {
                    update_grid(x+i,y,player,'S');
                }
            }
        }

        else if(choice=='4' || choice=='d' || choice=='D')
        {
            for(int i=1; i<length; i++)
            {
                if(y+i>10
                        || (player==1 && (first_grid[y+i][x]!='0' || first_grid[y+i+1][x-1]!='0' || first_grid[y+i+1][x]!='0' || first_grid[y+i+1][x+1]!='0'))
                        || (player==2 && (second_grid[y+i][x]!='0' || second_grid[y+i+1][x-1]!='0' || second_grid[y+i+1][x]!='0' || second_grid[y+i+1][x+1]!='0')))
                {
                    pass=false;
                    break;
                }
            }
            if(pass)
            {
                for(int i=1; i<length; i++)
                {
                    update_grid(x,y+i,player,'S');
                }
            }
        }

        else        //go back
        {
            update_grid(x,y,player,'0');
            ship_setup(name,length,player);
            pass=true;
        }
        if(!pass)
        {
            system("CLS");
            display_grid(player);
            cout<<"Impossible choice. Remember that ships can't be adjacent."<<endl<<"Choose direction of your "<<name<<" ("<<length<<"x1 ship)."<<endl<<"[1]-left    [2]-up    [3]-right    [4]-down    [5]-go back"<<endl<<"Choice: ";
            cin>>choice;
        }
    }

}

int Game::find_x(string coordinates)
{
    int x=100;//error
    for(int i=0; i<=coordinates.length(); i++)
    {
        if(coordinates[i]=='1' && coordinates[i+1]=='0')
        {
            x=10;
            break;
        }
        else if(coordinates[i]>48 && coordinates[i]<58)
        {
            x=coordinates[i]-48;
            break;
        }
    }
    return x;
}
int Game::find_y(string coordinates)
{
    int y=100;//error
    for(int i=0; i<=coordinates.length(); i++)
    {
        if(coordinates[i]>64 && coordinates[i]<75)
        {
            y=coordinates[i]-64;
            break;
        }
        else if(coordinates[i]>96 && coordinates[i]<107)
        {
            y=coordinates[i]-96;
            break;
        }
    }
    return y;
}

bool Game::update_grid(int x, int y, int grid, char symbol)          //grid: 1-player1 grid,   2-player2 grid,   3-player1 shot, 4-player2 shot
{
    if(x<1 || x>10 || y<1 || y>10)
    {
        return false;
    }

    if(grid==1 && first_grid[y][x]!=symbol)
    {
        first_grid[y][x]=symbol;
    }
    else if(grid==1)
        return false;

    else if(grid==2 && second_grid[y][x]!=symbol)
    {
        second_grid[y][x]=symbol;
    }
    else if(grid==2)
        return false;

    else if(grid==3) //TO DO    shooting
    {
        first_shots[y][x]=symbol;

    }
    else if(grid==4) //TO DO    shooting
    {
        second_shots[y][x]=symbol;

    }
    return true;
}

void Game::take_turns()
{
    cin.ignore();
    if(first_player=="Player")   //PVE
    {
        while(1)
        {
            player_turn(1);
            if(is_over())
                break;
            computer_turn();
            if(is_over())
                break;
        }
    }

    else            //PVP
    {
        while(1)
        {
            player_turn(1);
            if(is_over())
                break;
            player_turn(2);
            if(is_over())
                break;
        }

    }

    reset();
}

void Game::player_turn(int player)
{
    system("CLS");
    if(player==1)
    {
        cout<<"\t\t    It's your turn "<<first_player<<"."<<endl<<endl;
        display_board(1);
        cout<<"Shoot at enemy ships by typing coordinates."<<endl<<"Choice: ";
        string coordinates;
        getline(cin,coordinates);
        int y=find_y(coordinates);
        int x=find_x(coordinates);
        while(x<1 || x>10 || y<1 || y>10 || first_shots[y][x]!='0')
        {
            system("CLS");
            cout<<"\t\t    It's your turn "<<first_player<<"."<<endl<<endl;
            display_board(1);
            cout<<"Shoot at enemy ships by typing coordinates."<<endl<<"Choice: ";
            cout<<"Wrong coordinates. Type a letter from A to J followed by a number from 1 to 10."<<endl<<"Choice: ";
            string coordinates;
            getline(cin,coordinates);
            y=find_y(coordinates);
            x=find_x(coordinates);
        }
        if(second_grid[y][x]=='S')
        {
            update_grid(x,y,2,'x');
            update_grid(x,y,3,'x');  //hit
            is_sunk(x,y,player);
        }
        else
        {
            update_grid(x,y,2,'o');
            update_grid(x,y,3,'o');  //miss
        }
    }

    else        //player 2      TO DO
    {
        cout<<"\t\t    It's your turn "<<second_player<<"."<<endl<<endl;
        display_board(2);
        cout<<"Shoot at enemy ships by typing coordinates."<<endl<<"Choice: ";
        string coordinates;
        getline(cin,coordinates);
        int y=find_y(coordinates);
        int x=find_x(coordinates);
        while(x<1 || x>10 || y<1 || y>10 || second_shots[y][x]!='0')
        {
            system("CLS");
            cout<<"\t\t    It's your turn "<<second_player<<"."<<endl<<endl;
            display_board(2);
            cout<<"Shoot at enemy ships by typing coordinates."<<endl<<"Choice: ";
            cout<<"Wrong coordinates. Type a letter from A to J followed by a number from 1 to 10."<<endl<<"Choice: ";
            string coordinates;
            getline(cin,coordinates);
            y=find_y(coordinates);
            x=find_x(coordinates);
        }
        if(first_grid[y][x]=='S')
        {
            update_grid(x,y,1,'x');
            update_grid(x,y,4,'x');  //hit
            is_sunk(x,y,player);
        }
        else
        {
            update_grid(x,y,1,'o');
            update_grid(x,y,4,'o');  //miss
        }
    }
};

void Game::computer_turn()
{
    if(second_player=="Computer(easy)")
    {
        computer_easy();
    }

    else if(second_player=="Computer(hard)")
    {
        computer_hard();
    }
};

void Game::computer_easy()
{
    int x;
    int y;
    while(1)
    {
        x=rand()%10+1;
        y=rand()%10+1;
        if( second_shots[y][x]!='0')
        {
            continue;
        }
        break;
    }
    if(first_grid[y][x]=='S')
    {
        update_grid(x,y,1,'x');
        update_grid(x,y,4,'x');  //hit
        is_sunk(x,y,2);
    }
    else
    {
        update_grid(x,y,1,'o');
        update_grid(x,y,4,'o');  //miss
    }
}


int Game::count_empty(int x, int y)
{
    int vert=1;
    int horizon=1;
    for(int i=1; i<5; i++)
    {

        if(second_shots[y][x-i]!='0' || (x-i)<1)
        {
            break;
        }
        horizon++;
    }
    for(int i=1; i<5; i++)
    {
        if(second_shots[y][x+i]!='0' || (x+i)>10)
        {
            break;
        }
        horizon++;
    }
    for(int i=1; i<5; i++)
    {
        if(second_shots[y-i][x]!='0' || (y-i)<1)
        {
            break;
        }
        vert++;
    }
    for(int i=1; i<5; i++)
    {
        if(second_shots[y+i][x]!='0' || (y+i)>10)
        {
            break;
        }
        vert++;
    }
    if(vert>horizon)
        return vert;
    else
        return horizon;

}

void Game::computer_hard()
{
    int x;
    int y;
    bool no_x=false;
    for(int i=1; i<11; i++)
    {
        for(int j=1; j<11; j++)
        {
            if(second_shots[i][j]=='x' && ((second_shots[i][j-1]=='0' && j-1>=1) || (second_shots[i-1][j]=='0' && i-1>=1)
                                           || (second_shots[i][j+1]=='0' && j+1<=10) || (second_shots[i+1][j]=='0' && i+1<=10)))
            {
                y=i;
                x=j;
                no_x=true;
            }
            if(second_shots[i][j]=='X')
            {
                if(second_shots[i][j-1]=='0')
                    update_grid(j-1,i,4,'o');
                if(second_shots[i-1][j-1]=='0')
                    update_grid(j-1,i-1,4,'o');
                if(second_shots[i-1][j]=='0')
                    update_grid(j,i-1,4,'o');
                if(second_shots[i-1][j+1]=='0')
                    update_grid(j+1,i-1,4,'o');
                if(second_shots[i][j+1]=='0')
                    update_grid(j+1,i,4,'o');
                if(second_shots[i+1][j+1]=='0')
                    update_grid(j+1,i+1,4,'o');
                if(second_shots[i+1][j]=='0')
                    update_grid(j,i+1,4,'o');
                if(second_shots[i+1][j-1]=='0')
                    update_grid(j-1,i+1,4,'o');
            }
        }
    }

    if(!no_x)   //there is no ship hit
    {
        system("CLS");


        int length=2;
        if(first_ships[4]==1)
        {
            length=3;
            if(first_ships[3]==1 && first_ships[2]==1)
            {
                length=4;
                if(first_ships[1]==1)
                {
                    length=5;
                }
            }
        }
        for(int i=1; i<11; i++)
        {
            for(int j=1; j<11; j++)
            {
                if(second_shots[i][j]=='0')
                {
                    if(count_empty(j,i)<length)
                        update_grid(j,i,4,'o');
                }
            }
        }

        while(1)
        {
            x=rand()%10+1;
            y=rand()%10+1;
            if( second_shots[y][x]!='0')
            {
                continue;
            }
            break;
        }
        if(first_grid[y][x]=='S')
        {
            update_grid(x,y,1,'x');
            update_grid(x,y,4,'x');  //hit
            if(second_shots[y-1][x-1]=='0')
                update_grid(x-1,y-1,4,'o');
            if(second_shots[y-1][x+1]=='0')
                update_grid(x+1,y-1,4,'o');
            if(second_shots[y+1][x+1]=='0')
                update_grid(x+1,y+1,4,'o');
            if(second_shots[y+1][x-1]=='0')
                update_grid(x-1,y+1,4,'o');
            is_sunk(x,y,2);
        }
        else
        {
            update_grid(x,y,1,'o');
            update_grid(x,y,4,'o');  //miss
        }
    }

    else    //there is a ship hit
    {
        int shoot;
        while(1)
        {
            int choice=rand()%4;
            if(choice==0 && second_shots[y][x-1]=='0' && x-1>=1)
            {
                shoot=0;
                break;
            }
            else if(choice==1 && second_shots[y-1][x]=='0' && y-1>=1)
            {
                shoot=1;
                break;
            }
            else if(choice==2 && second_shots[y][x+1]=='0' && x+1<=10)
            {
                shoot=2;
                break;
            }
            else if(choice==3 && second_shots[y+1][x]=='0' && y+1<=10)
            {
                shoot=3;
                break;
            }
            else if(second_shots[y][x-1]=='0' && x-1>=1)
            {
                shoot=0;
                break;
            }
            else if(second_shots[y-1][x]=='0' && y-1>=1)
            {
                shoot=1;
                break;
            }
            else if(second_shots[y][x+1]=='0' && x+1<=10)
            {
                shoot=2;
                break;
            }
            else if(second_shots[y+1][x]=='0' && y+1<=10)
            {
                shoot=3;
                break;
            }
            else if(second_shots[y][x-1]=='x' && x-1>=1)
            {
                x=x-1;
                continue;
            }
            else if(second_shots[y-1][x]=='x' && y-1>=1)
            {
                y=y-1;
                continue;
            }
            else if(second_shots[y][x+1]=='x' && x+1<=10)
            {
                x=x+1;
                continue;
            }
            else if(second_shots[y+1][x]=='x' && y+1<=10)
            {
                y=y+1;
                continue;
            }
        }

        if(shoot==0)
        {
            if(first_grid[y][x-1]=='S')
            {
                update_grid(x-1,y,1,'x');
                update_grid(x-1,y,4,'x');  //hit
                if(second_shots[y-1][x-2]=='0')
                    update_grid(x-2,y-1,4,'o');
                if(second_shots[y-1][x]=='0')
                    update_grid(x,y-1,4,'o');
                if(second_shots[y+1][x]=='0')
                    update_grid(x,y+1,4,'o');
                if(second_shots[y+1][x-2]=='0')
                    update_grid(x-2,y+1,4,'o');
                is_sunk(x-1,y,2);
            }
            else
            {
                update_grid(x-1,y,1,'o');
                update_grid(x-1,y,4,'o');  //miss
            }
        }

        if(shoot==1)
        {
            if(first_grid[y-1][x]=='S')
            {
                update_grid(x,y-1,1,'x');
                update_grid(x,y-1,4,'x');  //hit
                if(second_shots[y-2][x-1]=='0')
                    update_grid(x-1,y-2,4,'o');
                if(second_shots[y-2][x+1]=='0')
                    update_grid(x+1,y-2,4,'o');
                if(second_shots[y][x+1]=='0')
                    update_grid(x+1,y,4,'o');
                if(second_shots[y][x-1]=='0')
                    update_grid(x-1,y,4,'o');
                is_sunk(x,y-1,2);
            }
            else
            {
                update_grid(x,y-1,1,'o');
                update_grid(x,y-1,4,'o');  //miss
            }
        }

        if(shoot==2)
        {
            if(first_grid[y][x+1]=='S')
            {
                update_grid(x+1,y,1,'x');
                update_grid(x+1,y,4,'x');  //hit
                if(second_shots[y-1][x]=='0')
                    update_grid(x,y-1,4,'o');
                if(second_shots[y-1][x+2]=='0')
                    update_grid(x+2,y-1,4,'o');
                if(second_shots[y+1][x+2]=='0')
                    update_grid(x+2,y+1,4,'o');
                if(second_shots[y+1][x]=='0')
                    update_grid(x,y+1,4,'o');
                is_sunk(x+1,y,2);
            }
            else
            {
                update_grid(x+1,y,1,'o');
                update_grid(x+1,y,4,'o');  //miss
            }
        }

        if(shoot==3)
        {
            if(first_grid[y+1][x]=='S')
            {
                update_grid(x,y+1,1,'x');
                update_grid(x,y+1,4,'x');  //hit
                if(second_shots[y][x-1]=='0')
                    update_grid(x-1,y,4,'o');
                if(second_shots[y][x+1]=='0')
                    update_grid(x+1,y,4,'o');
                if(second_shots[y+2][x+1]=='0')
                    update_grid(x+1,y+2,4,'o');
                if(second_shots[y+2][x-1]=='0')
                    update_grid(x-1,y+2,4,'o');
                is_sunk(x,y+1,2);
            }
            else
            {
                update_grid(x,y+1,1,'o');
                update_grid(x,y+1,4,'o');  //miss
            }
        }
    }
}

void Game::reset()
{
    display_scores();
    cout<<"Do you want to play again?"<<endl;
    char play;
    cout<<"[1]-PLAY AGAIN\t[2]-CHANGE GAME MODE\t[3]-EXIT"<<endl;
    cout<<"Choice: ";
    cin>>play;
    if(play=='1' || play=='Y' || play=='y' || play=='P' || play=='p')
    {
        for(int i=0; i<12; i++)
        {
            for(int j=0; j<12; j++)
            {
                first_grid[i][j]='0';
                second_grid[i][j]='0';
                first_shots[i][j]='0';
                second_shots[i][j]='0';
            }
        }
        for(int i=0; i<5; i++)
        {
            first_ships[i]=0;
            second_ships[i]=0;
        }
        system("CLS");
        setup();
        take_turns();
    }
    else if(play=='2' || play=='C' || play=='c')
    {
        system("CLS");
        Game();
    }
    else
    {
        cout<<endl<<"Thanks for playing! Goodbye!";
    }
};

void Game::is_sunk(int x, int y, int player)
{
    if(player==1)
    {
        int counter=1;
        bool sunk=true;
        for(int i=1; i<5; i++)
        {
            if(second_grid[y-i][x]=='x')
                counter++;
            else if(second_grid[y-i][x]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        for(int i=1; i<5; i++)
        {
            if(second_grid[y+i][x]=='x')
                counter++;
            else if(second_grid[y+i][x]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        for(int i=1; i<5; i++)
        {
            if(second_grid[y][x-i]=='x')
                counter++;
            else if(second_grid[y][x-i]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        for(int i=1; i<5; i++)
        {
            if(second_grid[y][x+i]=='x')
                counter++;
            else if(second_grid[y][x+i]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        if(sunk)
        {
            update_grid(x,y,2,'X');
            update_grid(x,y,3,'X');
            for(int i=1; i<5; i++)
            {
                if(second_grid[y-i][x]=='x')
                {
                    update_grid(x,y-i,2,'X');
                    update_grid(x,y-i,3,'X');
                }
                else
                    break;
            }

            for(int i=1; i<5; i++)
            {
                if(second_grid[y+i][x]=='x')
                {
                    update_grid(x,y+i,2,'X');
                    update_grid(x,y+i,3,'X');
                }
                else
                    break;
            }

            for(int i=1; i<5; i++)
            {
                if(second_grid[y][x-i]=='x')
                {
                    update_grid(x-i,y,2,'X');
                    update_grid(x-i,y,3,'X');
                }
                else
                    break;
            }

            for(int i=1; i<5; i++)
            {
                if(second_grid[y][x+i]=='x')
                {
                    update_grid(x+i,y,2,'X');
                    update_grid(x+i,y,3,'X');
                }
                else
                    break;
            }
            system("CLS");
            cout<<"\t\t    It's your turn "<<first_player<<"."<<endl<<endl;
            display_board(1);
            if(counter==2)
            {
                cout<<endl<<"You have sunk an enemy Destroyer."<<endl;
                second_ships[4]=1;
            }
            else if(counter==3)
            {
                if(second_ships[2]==1)
                {
                    cout<<endl<<"You have sunk an enemy Submarine."<<endl;
                    second_ships[3]=1;
                }
                else if(second_ships[3]==1)
                {
                    cout<<endl<<"You have sunk an enemy Cruiser."<<endl;
                    second_ships[2]=1;
                }
                else
                {
                    int ship=rand()% 2;
                    if(ship==0)
                    {
                        cout<<endl<<"You have sunk an enemy Submarine."<<endl;
                        second_ships[3]=1;
                    }
                    else
                    {
                        cout<<endl<<"You have sunk an enemy Cruiser."<<endl;
                        second_ships[2]=1;
                    }
                }
            }
            else if(counter==4)
            {
                cout<<endl<<"You have sunk an enemy Battleship."<<endl;
                second_ships[1]=1;
            }
            else
            {
                cout<<endl<<"You have sunk an enemy Carrier."<<endl;
                second_ships[0]=1;
            }
            Sleep(3000);
        }
    }
    else    //player 2
    {
        int counter=1;
        bool sunk=true;
        for(int i=1; i<5; i++)
        {
            if(first_grid[y-i][x]=='x')
                counter++;
            else if(first_grid[y-i][x]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        for(int i=1; i<5; i++)
        {
            if(first_grid[y+i][x]=='x')
                counter++;
            else if(first_grid[y+i][x]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        for(int i=1; i<5; i++)
        {
            if(first_grid[y][x-i]=='x')
                counter++;
            else if(first_grid[y][x-i]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        for(int i=1; i<5; i++)
        {
            if(first_grid[y][x+i]=='x')
                counter++;
            else if(first_grid[y][x+i]=='S')
            {
                sunk=false;
                break;
            }
            else
                break;
        }

        if(sunk)
        {
            update_grid(x,y,1,'X');
            update_grid(x,y,4,'X');
            for(int i=1; i<5; i++)
            {
                if(first_grid[y-i][x]=='x')
                {
                    update_grid(x,y-i,1,'X');
                    update_grid(x,y-i,4,'X');
                }
                else
                    break;
            }

            for(int i=1; i<5; i++)
            {
                if(first_grid[y+i][x]=='x')
                {
                    update_grid(x,y+i,1,'X');
                    update_grid(x,y+i,4,'X');
                }
                else
                    break;
            }

            for(int i=1; i<5; i++)
            {
                if(first_grid[y][x-i]=='x')
                {
                    update_grid(x-i,y,1,'X');
                    update_grid(x-i,y,4,'X');
                }
                else
                    break;
            }

            for(int i=1; i<5; i++)
            {
                if(first_grid[y][x+i]=='x')
                {
                    update_grid(x+i,y,1,'X');
                    update_grid(x+i,y,4,'X');
                }
                else
                    break;
            }
            if(second_player=="Player 2")
            {
                system("CLS");
                cout<<"\t\t    It's your turn "<<second_player<<"."<<endl<<endl;
                display_board(2);
            }
            if(counter==2)
            {
                if(second_player=="Player 2")
                    cout<<endl<<"You have sunk an enemy Destroyer."<<endl;
                first_ships[4]=1;
            }
            else if(counter==3)
            {
                if(first_ships[2]==1)
                {
                    if(second_player=="Player 2")
                        cout<<endl<<"You have sunk an enemy Submarine."<<endl;
                    first_ships[3]=1;
                }
                else if(first_ships[3]==1)
                {
                    if(second_player=="Player 2")
                        cout<<endl<<"You have sunk an enemy Cruiser."<<endl;
                    first_ships[2]=1;
                }
                else
                {
                    int ship=rand()% 2;
                    if(ship==0)
                    {
                        if(second_player=="Player 2")
                            cout<<endl<<"You have sunk an enemy Submarine."<<endl;
                        first_ships[3]=1;
                    }
                    else
                    {
                        if(second_player=="Player 2")
                            cout<<endl<<"You have sunk an enemy Cruiser."<<endl;
                        first_ships[2]=1;
                    }
                }
            }
            else if(counter==4)
            {
                if(second_player=="Player 2")
                    cout<<endl<<"You have sunk an enemy Battleship."<<endl;
                first_ships[1]=1;
            }
            else
            {
                if(second_player=="Player 2")
                    cout<<endl<<"You have sunk an enemy Carrier."<<endl;
                first_ships[0]=1;
            }
            if(second_player=="Player 2")
                Sleep(3000);
        }
    }
}

bool Game::is_over()
{
    if(second_ships[0]==1 && second_ships[1]==1 && second_ships[2]==1 && second_ships[3]==1 && second_ships[4]==1)
    {
        system("CLS");
        cout<<first_player<<" won! Congratulations!"<<endl<<endl;
        first_score++;
        return true;
    }
    if(first_ships[0]==1 && first_ships[1]==1 && first_ships[2]==1 && first_ships[3]==1 && first_ships[4]==1)
    {
        system("CLS");
        if(second_player!="Player 2")
            cout<<second_player<<" won"<<endl<<endl;
        else
            cout<<second_player<<" won! Congratulations!"<<endl<<endl;
        second_score++;
        return true;
    }
    return false;

};

void Game::display_grid(int player)
{
    cout<<"  ";
    for(int i=1; i<11; i++)
    {
        cout<<" "<<i;
    }
    cout<<endl<<"  "<<"---------------------";
    for(int i=1; i<11; i++)
    {
        cout<<endl;
        if(i==1)
            cout<<"A";
        else if(i==2)
            cout<<"B";
        else if(i==3)
            cout<<"C";
        else if(i==4)
            cout<<"D";
        else if(i==5)
            cout<<"E";
        else if(i==6)
            cout<<"F";
        else if(i==7)
            cout<<"G";
        else if(i==8)
            cout<<"H";
        else if(i==9)
            cout<<"I";
        else
            cout<<"J";
        cout<<"| ";
        for(int j=1; j<11; j++)
        {
            if(player==1)
            {
                if(first_grid[i][j]!='0')
                    cout<<first_grid[i][j];
                else
                    cout<<" ";
            }
            else
            {
                if(second_grid[i][j]!='0')
                    cout<<second_grid[i][j];
                else
                    cout<<" ";
            }
            cout<<" ";
        }
    }
    cout<<endl<<endl;
}

void Game::display_board(int player)
{
    cout<<"       ENEMY SHIPS                            YOUR SHIPS"<<endl;
    cout<<"  ";
    for(int i=1; i<11; i++)
    {
        cout<<" "<<i;
    }
    cout<<"                 ";
    for(int i=1; i<11; i++)
    {
        cout<<" "<<i;
    }
    cout<<endl<<"  "<<"---------------------"<<"                 "<<"---------------------";
    for(int i=1; i<11; i++)
    {
        cout<<endl;
        if(i==1)
            cout<<"A";
        else if(i==2)
            cout<<"B";
        else if(i==3)
            cout<<"C";
        else if(i==4)
            cout<<"D";
        else if(i==5)
            cout<<"E";
        else if(i==6)
            cout<<"F";
        else if(i==7)
            cout<<"G";
        else if(i==8)
            cout<<"H";
        else if(i==9)
            cout<<"I";
        else
            cout<<"J";
        cout<<"| ";
        for(int j=1; j<11; j++)
        {
            if(player==1)
            {
                if(first_shots[i][j]!='0')
                    cout<<first_shots[i][j];
                else
                    cout<<" ";
            }
            else
            {
                if(second_shots[i][j]!='0')
                    cout<<second_shots[i][j];
                else
                    cout<<" ";
            }
            cout<<" ";
        }
        cout<<"               ";
        if(i==1)
            cout<<"A";
        else if(i==2)
            cout<<"B";
        else if(i==3)
            cout<<"C";
        else if(i==4)
            cout<<"D";
        else if(i==5)
            cout<<"E";
        else if(i==6)
            cout<<"F";
        else if(i==7)
            cout<<"G";
        else if(i==8)
            cout<<"H";
        else if(i==9)
            cout<<"I";
        else
            cout<<"J";
        cout<<"| ";
        for(int j=1; j<11; j++)
        {
            if(player==1)
            {
                if(first_grid[i][j]!='0')
                    cout<<first_grid[i][j];
                else
                    cout<<" ";
            }
            else
            {
                if(second_grid[i][j]!='0')
                    cout<<second_grid[i][j];
                else
                    cout<<" ";
            }
            cout<<" ";
        }

    }
    cout<<endl<<endl;
};

void Game::display_scores()
{
    cout<<"Scores: "<<endl<<first_player<<": "<<first_score<<"\t"<<second_player<<": "<<second_score<<endl;

};
