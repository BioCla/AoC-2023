/*
--- Day 7: Camel Cards Part 1 ---

Your all-expenses-paid trip turns out to be a one-way, five-minute ride in an airship.
(At least it's a cool airship!) It drops you off at the edge of a vast desert and descends back to Island Island.

"Did you bring the parts?"

You turn around to see an Elf completely covered in white clothing, wearing goggles, and riding a large camel.

"Did you bring the parts?" she asks again, louder this time.
You aren't sure what parts she's looking for; you're here to figure out why the sand stopped.

"The parts! For the sand, yes! Come with me; I will show you." She beckons you onto the camel.

After riding a bit across the sands of Desert Island, you can see what look like very large rocks covering half of the horizon.
The Elf explains that the rocks are all along the part of Desert Island that is directly above Island Island, making it hard to even get there.
Normally, they use big machines to move the rocks and filter the sand,
but the machines have broken down because Desert Island recently stopped receiving the parts they need to fix the machines.

You've already assumed it'll be your job to figure out why the parts stopped when she asks if you can help.
You agree automatically.

Because the journey will take a few days, she offers to teach you the game of Camel Cards.
Camel Cards is sort of similar to poker except it's designed to be easier to play while riding a camel.

In Camel Cards, you get a list of hands, and your goal is to order them based on the strength of each hand.
A hand consists of five cards labeled one of A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2.
The relative strength of each card follows this order, where A is the highest and 2 is the lowest.

Every hand is exactly one type.
From strongest to weakest, they are:

    Five of a kind, where all five cards have the same label: AAAAA
    Four of a kind, where four cards have the same label and one card has a different label: AA8AA
    Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
    Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
    Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
    One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
    High card, where all cards' labels are distinct: 23456

Hands are primarily ordered based on type; for example, every full house is stronger than any three of a kind.

If two hands have the same type, a second ordering rule takes effect.
Start by comparing the first card in each hand.
If these cards are different, the hand with the stronger first card is considered stronger.
If the first card in each hand have the same label, however, then move on to considering the second card in each hand.
If they differ, the hand with the higher second card wins; otherwise, continue with the third card in each hand, then the fourth, then the fifth.

So, 33332 and 2AAAA are both four of a kind hands, but 33332 is stronger because its first card is stronger.
Similarly, 77888 and 77788 are both a full house, but 77888 is stronger because its third card is stronger (and both hands have the same first and second card).

To play Camel Cards, you are given a list of hands and their corresponding bid (your puzzle input).
For example:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

This example shows five hands; each hand is followed by its bid amount.
Each hand wins an amount equal to its bid multiplied by its rank, where the weakest hand gets rank 1, the second-weakest hand gets rank 2, and so on up to the strongest hand.
Because there are five hands in this example, the strongest hand will have rank 5 and its bid will be multiplied by 5.

So, the first step is to put the hands in order of strength:

    32T3K is the only one pair and the other hands are all a stronger type, so it gets rank 1.
    KK677 and KTJJT are both two pair.
    Their first cards both have the same label, but the second card of KK677 is stronger (K vs T), so KTJJT gets rank 2 and KK677 gets rank 3.
    T55J5 and QQQJA are both three of a kind.
    QQQJA has a stronger first card, so it gets rank 5 and T55J5 gets rank 4.

Now, you can determine the total winnings of this set of hands by adding up the result of multiplying each hand's bid with its rank (765 * 1 + 220 * 2 + 28 * 3 + 684 * 4 + 483 * 5).
So the total winnings in this example are 6440.

Find the rank of every hand in your set.
What are the total winnings?
*/

#include "../../include/_init/part1.hpp"
#include "../../include/util/string_util.hpp"

enum Cards
{
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    J,
    Q,
    K,
    A
};

enum HandType
{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

struct Hand
{
    std::vector<Cards> cards;
    HandType type;
    int bid;
};

std::vector<Cards> read_hand(std::string hand_string)
{
    std::vector<Cards> hand;
    for (size_t i = 0; i < hand_string.size(); i++)
    {
        switch (hand_string[i])
        {
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            hand.push_back((Cards)(hand_string[i] - '2' + TWO));
            break;
        case 'T':
            hand.push_back(TEN);
            break;
        case 'J':
            hand.push_back(J);
            break;
        case 'Q':
            hand.push_back(Q);
            break;
        case 'K':
            hand.push_back(K);
            break;
        case 'A':
            hand.push_back(A);
            break;
        }
    }
    return hand;
}

HandType get_hand_type(std::vector<Cards> hand)
{
    std::vector<int> card_counts(13, 0);
    for (size_t i = 0; i < hand.size(); i++)
        card_counts[hand[i]]++;

    int three_of_a_kind_count = 0;
    int pair_count = 0;

    for (size_t i = 0; i < card_counts.size(); i++)
    {
        if (card_counts[i] == 5)
            return FIVE_OF_A_KIND;
        if (card_counts[i] == 4)
            return FOUR_OF_A_KIND;
        else if (card_counts[i] == 3)
            three_of_a_kind_count++;
        else if (card_counts[i] == 2)
            pair_count++;
    }

    if (three_of_a_kind_count == 1 && pair_count == 1)
        return FULL_HOUSE;
    if (three_of_a_kind_count == 1)
        return THREE_OF_A_KIND;
    if (pair_count == 2)
        return TWO_PAIR;
    if (pair_count == 1)
        return ONE_PAIR;
    return HIGH_CARD;
}

int part1(std::string input_file_path)
{
    std::vector<std::string> document;
    std::fstream document_file(input_file_path, std::ios_base::in);
    std::vector<Hand> hands;
    while (!document_file.eof())
    {
        std::string line;
        std::getline(document_file, line);
        std::vector<std::string> split_line = split(line, " ");
        if (split_line.size() != 2)
            continue;
        Hand hand;
        hand.cards = read_hand(split_line[0]);
        hand.bid = std::stoi(split_line[1]);
        hand.type = get_hand_type(hand.cards);
        hands.push_back(hand);
    }

    std::sort(hands.begin(), hands.end(), [](Hand a, Hand b)
              {
        if (a.type != b.type)
            return a.type < b.type;
        for (size_t i = 0; i < a.cards.size(); i++)
            if (a.cards[i] != b.cards[i])
                return a.cards[i] < b.cards[i];
        return false; });

    int total_winnings = 0;
    for (size_t i = 0; i < hands.size(); i++)
        total_winnings += hands[i].bid * (i + 1);
    return total_winnings;
}
