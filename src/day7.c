#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, 2
int getval(char c) {
    switch (c) {
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'T': return 10;
        case 'J': return 1;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
        default: return -1;
    };
}


int type(char hand[5]) {
    int num_uniq = 0;
    int max_count = 0;

    int counts[15] = {0};

    for(int i = 0; i<5; i++) {
        int val = getval(hand[i]);

        if(counts[val] == 0) {
            num_uniq++;
        }

        counts[val]++;

        if(counts[val] > max_count && val != 1) {
            max_count = counts[val];
        }
    }

    if(counts[1] > 0 && counts[1] < 5) {
        num_uniq--;
        max_count+=counts[1];
        printf("found %d jokers; %d, %d!\n", counts[1], num_uniq, max_count);
    }

    // Five of a kind
    if(num_uniq == 1) {
        return 7;
    }

    // Four of a kind
    if(max_count == 4) {
        return 6;
    }

    // Full house
    if(max_count == 3 && num_uniq == 2) {
        return 5;
    }

    // Three of a kind
    if(max_count == 3) {
        return 4;
    }

    // Two pair
    if(max_count == 2 && num_uniq == 3) {
        return 3;
    }

    // One pair
    if(max_count == 2) {
        return 2;
    }

    // Highcard
    if(num_uniq == 5) {
        return 1;
    }
 
    return -1;
}

typedef struct {
    char* cards;
    int bid;
    int type;
} hand;

int sort_func (const void *a, const void *b) {
    hand *ha = (hand*)a;
    hand *hb = (hand*)b;

    int cmp = ha->type - hb->type;

    if(cmp != 0) {
        return cmp;
    }

    for(int i=0; i < 5; i++) {
        if(ha->cards[i] == hb->cards[i]) continue;
        return getval(ha->cards[i]) - getval(hb->cards[i]);
    }

    return 0;
}

int main() {
    FILE *inputfd;
	inputfd = fopen("./input/input7.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line;
	size_t buflen = 0;
	ssize_t read;
	int sum = 0;

    printf("Reading camel hands...\n");

    hand hands[1003];
    int num_hands = 0;

	while ((read = getline(&line, &buflen, inputfd)) != -1) {
		int len = strlen(line);

        printf("Parsing: %s", line);

        hand h = {.cards = (char*)malloc(sizeof(char[5])) };
        memcpy(h.cards, line, sizeof(char[5]));
        h.cards[5] = '\0';

        h.type = type(h.cards);
        h.bid = atoi(&line[6]);

        hands[num_hands] = h;

        num_hands++;
    }

    printf("Parsing done!\n");

    for(int i = 0; i < num_hands; i++) {
        printf("%s, %d, %d\n", hands[i].cards, hands[i].bid, hands[i].type);
    }

    qsort(hands, num_hands, sizeof(hand), sort_func);

    printf("Sorted:\n");

    int answer = 0;
    for(int i = 0; i < num_hands; i++) {
        printf("%s, %d\n", hands[i].cards, hands[i].type);
        answer += hands[i].bid * (i+1);
    }

    printf("Answer: %d\n", answer);

	return 0;
}
