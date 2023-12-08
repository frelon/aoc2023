#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1() {
	FILE *inputfd;
	inputfd = fopen("./input/input4.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line;
	size_t buflen = 0;
	ssize_t read;

	int answer = 0;

    printf("Reading cards...\n");

	while ((read = getline(&line, &buflen, inputfd)) != -1) {
		int len = strlen(line);
		if(len < 2) {
			break;
		}

		int winners[100] = {0};

		char *card = strchr(line, ':');
        char *mid = strchr(card, '|');

        int start = (int)(card-line);
        int middle = (int)(mid-card);

        char tmp[3];
        tmp[2]='\0';
        for(int i = 1; i < middle; i+=3) {
            strncpy(tmp, card+i, 3);
            int winner = atoi(tmp);
            winners[winner] = 1;
            if(winner == 0) break;
        }

        int points = 0;
        for(int i = middle+1; i < strlen(card); i+=3) {
            strncpy(tmp, card+i, 3);
            int card = atoi(tmp);
            if(card == 0) break;

            if(winners[card] != 0) {
                if(points == 0) points++;
                else points *= 2;
            }
        }

        answer += points;
	}

    return answer;
}

int part2() {
	FILE *inputfd;
	inputfd = fopen("./input/input4.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line;
	size_t buflen = 0;
	ssize_t read;

	int answer = 0;

    printf("Shuffling cards...\n");

    int cards[200] = {0};
    int n = 0;

	while ((read = getline(&line, &buflen, inputfd)) != -1) {
		int len = strlen(line);
		if(len < 2) {
			break;
		}

        cards[n] += 1;

        for(int j = cards[n]; j > 0; j--) {
            int winners[100] = {0};

            /* printf("Line: %s", line); */
            char *card = strchr(line, ':');
            char *mid = strchr(card, '|');

            int start = (int)(card-line);
            int middle = (int)(mid-card);

            char tmp[3];
            tmp[2]='\0';
            for(int i = 1; i < middle; i+=3) {
                strncpy(tmp, card+i, 3);
                int winner = atoi(tmp);
                winners[winner] = 1;
                if(winner == 0) break;
            }

            int matches = 0;
            for(int i = middle+1; i < strlen(card); i+=3) {
                strncpy(tmp, card+i, 3);
                int card = atoi(tmp);
                if(card == 0) break;

                if(winners[card] != 0) matches++;
            }

            for(int i = 1; i <= matches; i++) {
                cards[n+i] += 1;
            }
        }

        n++;
	}

    int sum = 0;
    for(int i = 0; i < 200; i++) {
        if(cards[i] == 0) break;
        sum += cards[i];

    }

    return sum;
}

int main() {
    int answer1 = part1();
    int answer2 = part2();
	printf("Part1: %d\nPart2: %d\n", answer1, answer2);
	return 0;
}
