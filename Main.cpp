//Names: Nue Lopez, Alexander R., Dylan Hamilton
//Date: 1/28/2025
//Assignment: Making a Card Game with OOD Group Activity
#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

class Card {
public:
    //Constructors
    Card() : value(0) {} //Set inital deck value to zero 
    Card(const string& suit, const string& rank, int value)
        //Int card with specific suit, rank, and value
        : suit(suit), rank(rank), value(value) {}
    

    // Setters
    void set_suit(const string& suit) { //Set suit of card
        this->suit = suit; //Use this-> to make sure it doesn't modify our main variable   
    }
  
    void set_rank(const string& rank) { //Set rank of card
        this->rank = rank;
    }
 //Use this-> to make sure it doesn't modify our main variable
    void set_value(int value) { //Set value of card
        this->value = value;
    }
 //Use this-> to make sure it doesn't modify our main variable 
    //Getters 
    string get_suit() const {
        return suit; //returns the suit of the card
    }
    string get_rank() const {
        return rank; //returns the rank of the card
    }
    int get_value() const {
        return value; //returns the value of the card
    }
    // Method to print card details
    void print_card() const {
        cout << rank << " of " << suit << endl;
    }

private: //These are encapsuulated and we can't access them until we call them through the get and set methods. 
    string suit;
    string rank;
    int value;
};

//CODE ENHANCEMENT: Visual Code Upgrade: Added icons for each card suit
const string SUITS[] = {"Spades ♠", "Hearts ♥", "Diamonds ♦", "Clubs ♣"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

Card deck[52];
int currentCardIndex = 0;

void initializeDeck() {
    int deckIndex = 0;
    for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
        for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
            deck[deckIndex++] = Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
        }
    }
}

void printDeck() {
    for (int i = 0; i < 52; i++) {
        deck[i].print_card();
    }
}

void shuffleDeck() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;
        Card temp = deck[i]; // these next three lines are a swap function
        deck[i] = deck[index];
        deck[index] = temp;
    }
}

Card dealCard() { 
    return deck[currentCardIndex++]; 
}

int dealInitialPlayerCards() {
    Card card1 = dealCard();
    Card card2 = dealCard();
    cout << "Your cards: ";
    card1.print_card();
    card2.print_card();
    return card1.get_value() + card2.get_value();
}

int playerTurn(int playerTotal) {
    while (true) {
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);
        if (action == "hit") {
            Card newCard = dealCard();
            playerTotal += newCard.get_value();
            cout << "You drew a ";
            newCard.print_card();
            if (playerTotal > 21) {
                break;
            }
        } else if (action == "stand") {
            break;
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal;
}

int main() {
    initializeDeck();
    shuffleDeck();

    int playerTotal = dealInitialPlayerCards();
    cout << "The playerTotal is " << playerTotal << endl;

    playerTotal = playerTurn(playerTotal);
    if (playerTotal > 21) {
        cout << "You BUSTED! Dealer wins. 😰" << endl; //CODE ENHANCEMENT: Visual Code Upgrade: Added a customized message when you go bust and lose.
        return 0;
    }

    return 0;
}
