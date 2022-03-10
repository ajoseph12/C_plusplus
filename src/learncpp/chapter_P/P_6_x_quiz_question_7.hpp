//
//  trails.hpp
//  src
//
//  Created by allwyn joseph on 2/19/20.
//  Copyright © 2020 allwyn joseph. All rights reserved.
//

#include <iostream>

using namespace std;

// Global constant expressions
constexpr int cardsInADeck{ 52 };
constexpr int cardInASuit{ 13 };
constexpr int blackJack{ 21 };
constexpr int maxDealerValue{ 17 };

enum class CardRank
{
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
    
    max_rank
};


enum class CardSuits
{
    clubs,
    diamonds,
    hearts,
    spades,
    
    max_suits
};


struct Card
{
    CardRank rank{};
    CardSuits suit{};
};

struct Player
{
    int score { 0 };
    int ace_count { 0 };
};

/**
 * Returns a char indicating the rank of the card
 *
 * @param rank the rank of a card
 */
char getCardRank(CardRank rank)
{
    switch(rank)
    {
        case CardRank::two:
            return '2';
        case CardRank::three:
            return '3';
        case CardRank::four:
            return '4';
        case CardRank::five:
            return '5';
        case CardRank::six:
            return '6';
        case CardRank::seven:
            return '7';
        case CardRank::eight:
            return '8';
        case CardRank::nine:
            return '9';
        case CardRank::ten:
            return 'T';
        case CardRank::jack:
            return 'J';
        case CardRank::queen:
            return 'Q';
        case CardRank::king:
            return 'K';
        case CardRank::ace:
            return 'A';
        default:
            return '0';
    }
}


/**
 * Returns a char indicating the suit of the card
 *
 * @param suit the suit of a card
 */
char getCardSuit(CardSuits suit)
{
    switch(suit)
    {
        case CardSuits::spades:
            return 'S';
        case CardSuits::hearts:
            return 'H';
        case CardSuits::diamonds:
            return 'D';
        case CardSuits::clubs:
            return 'C';
        default:
            return 'Z';
    }
}

/**
 * Creates a deck of cards.
 */
auto createDeck()
{
    static Card arr[cardsInADeck];
    
    for(int s{0}; s < static_cast<int>(CardSuits::max_suits); s++)
    {
        for(int r{0}; r < static_cast<int>(CardRank::max_rank); r++)
        {
            arr[(s*cardInASuit) + r].suit = static_cast<CardSuits>(s);
            arr[(s*cardInASuit) + r].rank = static_cast<CardRank>(r);
        }
    }
    return arr;
}

/**
 * Returns value of card passed as an argument.
 *
 * @param card a struct holding card rank and suit
 */
int getCardValue(const Card card)
{
    switch(card.rank)
    {
        case CardRank::two:
            return 2;
        case CardRank::three:
            return 3;
        case CardRank::four:
            return 4;
        case CardRank::five:
            return 5;
        case CardRank::six:
            return 6;
        case CardRank::seven:
            return 7;
        case CardRank::eight:
            return 8;
        case CardRank::nine:
            return 9;
        case CardRank::ten:
        case CardRank::jack:
        case CardRank::queen:
        case CardRank::king:
            return 10;
        case CardRank::ace:
            return 11;
        default:
            assert(false && "should never happen");
            return '0';
    }
}

/**
 * Returns user's desire to hit or stay.
 */
char getUserResponse()
{
    char hit_or_stay;
    do
    {
        cout << "\n\t[UserInput] - Do you want to hit? (y/n): ";
        cin >> hit_or_stay;
        cin.ignore(32767, '\n');
    }
    while (hit_or_stay != 'y' && hit_or_stay != 'n');
    
    return hit_or_stay;
}

void displayPlayerScore(int total, bool dealerIsPlaying = false)
{
    if (dealerIsPlaying)
        cout << "\n\t[INFO] - dealer's score: " << total;
    else
        cout << "\n\t[INFO] - player's score: " << total;
}


/**
 * Updates player score and ace count
 *
 * @param player a struct holding player score and ace count information
 * @param card an enum holding rank and suit of the dealt card
 */
void checkAcesUpdatePlayer(Player &player, Card &card)
{
    // Update player score and ace count
    player.score += getCardValue(card);
    if (getCardRank(card.rank) == 'A')
        player.ace_count += 1;
    
    // Check if player score is greater than 21, if so decrease score by
    // 10 and ace_count by 1
    if (player.score > 21 and player.ace_count > 0)
    {
        player.ace_count -= 1;
        player.score -= 10;
    }
}

/**
 * Returns total score of cards drawn by dealer or player.
 *
 * @param deck an array of structs holding different cards and the rank and suit
 *      they belong to
 * @param dealerIsPlaying a bool indicating if the dealer or player is playing
 */
int play(Card deck[], bool dealerIsPlaying = false)
{
    // Initialize player
    Player player;
    
    // Keep track of deck index and re-initialize if value reachess 51
    static int deck_index{ 0 };
    if (deck_index == 52)
        deck_index = 0;
    
    // If dealer, pick one card from deck, else pick two cards
    checkAcesUpdatePlayer(player, deck[deck_index]);
    if (not dealerIsPlaying)
        ++deck_index;
    checkAcesUpdatePlayer(player, deck[deck_index]);
    displayPlayerScore(player.score, dealerIsPlaying);
    
    bool keepPlaying{ 1 };
    
    // Run play until player/dealer has gone bust or decides to stop
    while (keepPlaying)
    {
        // If dealer is playing, keep hitting until bust or `maxDealerValue`
        if (dealerIsPlaying)
        {
            if (player.score < maxDealerValue)
            {
                checkAcesUpdatePlayer(player, deck[deck_index]);
                displayPlayerScore(player.score, dealerIsPlaying);
            }
            else
                keepPlaying = 0;
        }
        // iF player is playing, keep hitting until player decides to stay or
        // he/she has exceeded or equalled `blackJack`
        else
        {
            if (player.score < blackJack)
            {
                if (getUserResponse() == 'y')
                {
                    checkAcesUpdatePlayer(player, deck[deck_index]);
                    displayPlayerScore(player.score, dealerIsPlaying);
                }
                else
                    keepPlaying = 0;
            }
            else
                keepPlaying = 0;
        }
        ++deck_index;
        
    }
    return player.score;
}
