//
//  main.cpp
//  War Card Game(Better)
//
//  Created by Will Baumbach on 9/10/16.
//  Copyright © 2016 WillBaumbach. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>

using namespace std;


bool running = false;
int input;
stack<int> playerHand;
stack<int> compHand;
stack<int> playerDisc;
stack<int> compDisc;
stack<int> limbo;
int turns = 0;
vector<int> deck = {14,14,14,14,13,13,13,13,12,12,12,12,11,11,11,11,10,10,10,10,9,9,9,9,8,8,8,8,7,7,7,7,6,6,6,6,5,5,5,5,4,4,4,4,3,3,3,3,2,2,2,2};




void Setup()
{
    cout << "Welcome to the Game of War!" << endl << "1. New Game." << endl << "2. Quit" << endl;
    cin >> input;
    if (input == 1)
    {
        running = true;
    }
    else if (input == 0)
    {
        running = false;
        return;
    }
    else
    {
        cout << "That is not a valid input please try again.";
        running = false;
        return;
    }
    
    // Setting up deck and dealing cards
    random_shuffle(begin(deck), end(deck));
    for(int i = 0; i < deck.size(); i+=2)
    {
        playerHand.push(deck[i]);
        compHand.push(deck[i+1]);
    }
    
}

void PlayHand()
{
    if(playerHand.top() > compHand.top())
    {
        if(!limbo.empty())
        {
            for(int i = 0; i < limbo.size(); i++)
            {
                playerHand.push(limbo.top());
                limbo.pop();
            }
        }
        playerDisc.push(compHand.top());
        compHand.pop();
        playerDisc.push(playerHand.top());
        playerHand.pop();
    }
    else if (compHand.top() > playerHand.top())
    {
        if(!limbo.empty())
        {
            for(int i = 0; i < limbo.size(); i++)
            {
                compHand.push(limbo.top());
                limbo.pop();
            }
        }
        compDisc.push(playerHand.top());
        playerHand.pop();
        compDisc.push(compHand.top());
        compHand.pop();
    }
}

void CheckWar()
{
    int a = playerHand.top();
    int b = compHand.top();
    if(a == b)
    {
        for (int i = 0; i < 4; i++)
        {
            limbo.push(playerHand.top());
            playerHand.pop();
            limbo.push(compHand.top());
            compHand.pop();
        }
    }
}

void CheckHand()
{
    if(playerHand.empty())
    {
        if (playerDisc.empty())
        {
            running = false;
            cout << "Player Wins!! This game lasted for " << turns << " turns!" << endl << "Thanks so much for playing!";
        }
        else
        {
            for (int i = 0; i < playerDisc.size(); i++)
            {
                playerHand.push(playerDisc.top());
                playerDisc.pop();
            }
        }
    }
    else if(compHand.empty())
    {
        if (compDisc.empty())
        {
            running = false;
            cout << "Computer Wins!! This game lasted for " << turns << " turns! Better luck next time!" << endl << "Thanks so much for playing!";
        }
        else
        {
            for (int i = 0; i < compDisc.size(); i++)
            {
                compHand.push(compDisc.top());
                compDisc.pop();
            }
        }
    }
}

int main()
{
    Setup();
    while (running)
    {
        cout << turns << endl;
        turns++;
        PlayHand();
        CheckWar();
        CheckHand();
    }
}
