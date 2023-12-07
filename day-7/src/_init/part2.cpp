/*
--- Day 7: Camel Cards Part 2 ---

To make things a little more interesting, the Elf introduces one additional rule.
Now, J cards are jokers - wildcards that can act like whatever card would make the hand the strongest type possible.

To balance this, J cards are now the weakest individual cards, weaker even than 2.
The other cards stay in the same order: A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, J.

J cards can pretend to be whatever card is best for the purpose of determining hand type; for example, QJJQ2 is now considered four of a kind.
However, for the purpose of breaking ties between two hands of the same type, J is always treated as J, not the card it's pretending to be: JKKK2 is weaker than QQQQ2 because J is weaker than Q.

Now, the above example goes very differently:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

    32T3K is still the only one pair; it doesn't contain any jokers, so its strength doesn't increase.
    KK677 is now the only two pair, making it the second-weakest hand.
    T55J5, KTJJT, and QQQJA are now all four of a kind! T55J5 gets rank 3, QQQJA gets rank 4, and KTJJT gets rank 5.

With the new joker rule, the total winnings in this example are 5905.

Using the new joker rule, find the rank of every hand in your set.
What are the new total winnings?
*/

#include "../../include/_init/part1.hpp"
#include "../../include/util/string_util.hpp"

enum Cards
{
    J, // Is a wildcard and considered the weakest card
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
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

std::vector<Cards> _read_hand(std::string hand_string)
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

HandType _get_hand_type(std::vector<Cards> hand)
{
    std::vector<int> card_counts(13, 0);
    for (size_t i = 0; i < hand.size(); i++)
        card_counts[hand[i]]++;

    int three_of_a_kind_count = 0;
    int pair_count = 0;
    int joker_count = card_counts[J];

    for (size_t i = 1; i < card_counts.size(); i++)
    {
        if (card_counts[i] + joker_count == 5 || joker_count >= 4)
            return FIVE_OF_A_KIND;
        if (card_counts[i] + joker_count == 4)
            return FOUR_OF_A_KIND;
        else if (card_counts[i] + joker_count == 3)
            three_of_a_kind_count++;
        else if (card_counts[i] + joker_count == 2)
            pair_count++;
    }

    if ((three_of_a_kind_count == 1 && pair_count == 1) || (three_of_a_kind_count == 2 && joker_count == 1))
        return FULL_HOUSE;
    if ((three_of_a_kind_count == 1) || (three_of_a_kind_count == 3 && joker_count >= 1))
        return THREE_OF_A_KIND;
    if (pair_count == 2)
        return TWO_PAIR;
    if ((pair_count == 1) || (pair_count == 4 && joker_count >= 1))
        return ONE_PAIR;
    return HIGH_CARD;
}

int part2(std::string input_file_path)
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
        hand.cards = _read_hand(split_line[0]);
        hand.bid = std::stoi(split_line[1]);
        hand.type = _get_hand_type(hand.cards);
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
