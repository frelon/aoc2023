#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const int NUM_RACES = 1;

int race(long time, long distance) {
	int wins = 0;
	for(long i = 1; i < time; i++) {
		long time_left = time-i;
		if(i * time_left >= distance) {
			wins++;
		}
	}
	return wins;
}

int main() {
	FILE *inputfd;
	inputfd = fopen("input6.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line;
	size_t buflen = 0;

	printf("Calculating speeds...\n");

	long times[4] = {0};
	int t = 0;
	getline(&line, &buflen, inputfd);
	for(int i = 0; i < buflen; i++) {
		if(!isdigit(line[i])) {
			continue;
		}

		times[t] = atol(line+i);
		t++;

		while(isdigit(line[i])) i++;
	}

	printf("Times: %ld %ld %ld %ld\n", times[0], times[1], times[2], times[3]);

	long distances[4] = {0};
	t = 0;
	getline(&line, &buflen, inputfd);
	for(int i = 0; i < buflen; i++) {
		if(!isdigit(line[i])) {
			continue;
		}

		distances[t] = atol(line+i);
		t++;

		while(isdigit(line[i])) i++;
	}

	printf("Distances: %ld %ld %ld %ld\n", distances[0], distances[1], distances[2], distances[3]);

	int wins[4] = {0};
	for(int i = 0; i<NUM_RACES; i++) {
		printf("Race %d\n", i);
		wins[i] = race(times[i], distances[i]);
	}

	printf("Wins: %d %d %d %d\n", wins[0], wins[1], wins[2], wins[3]);

	int answer = 1;
	for(int i = 0; i < NUM_RACES; i++) {
		answer*=wins[i];
	}

    printf("Answer: %d\n", answer);

	return 0;
}
