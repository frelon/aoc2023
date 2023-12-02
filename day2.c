#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* enum color { red = 1, green = 2, blue = 3}; */

int strtocolor(char *str) {
    const static char *colors[3] = {"red", "green", "blue"};

    char cmp[10];

    printf("parsing %s\n", str);

    for(int i=0; i<3; i++) {
        int len = strlen(colors[i]);
        strncpy(cmp, str, len);
        cmp[len] = '\0';

        if(strcmp(cmp, colors[i]) == 0) {
            return i+1;
        }
    }

    return 0;
}

int main() {
	FILE *inputfd;
	inputfd = fopen("input2.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line;
	size_t buflen = 0;
	ssize_t read;

	int answer = 0;

    printf("Reading games...\n");

	while ((read = getline(&line, &buflen, inputfd)) != -1) {
		int len = strlen(line);

		int id, possible=1,red=0, green=0, blue=0, curr=0, what=0;
		char delim[] = " ";
		
		char *ptr = strtok(line, delim);
		
		// Throw away "Game" 
		ptr = strtok(NULL, delim);

		// Parse ID
		id = atoi(ptr);
		printf("Parsing game '%d'\n", id);

		while(ptr != NULL)
		{
			ptr = strtok(NULL, delim);
			if(ptr == NULL) {
                answer += id;
				break;
			}

			if (what == 0) {
				what = 1;

				curr = atoi(ptr);
				continue;
			}

			int ptrlen;
			if((ptrlen = strlen(ptr)) < 3) {
				break;
			}

			what = 0;
			int col = strtocolor(ptr);
			if(col == 0) {
				break;
			}
			switch (col) {
				case 1:
					red += curr;
					break;
				case 2:
					green += curr;
					break;
				case 3:
					blue += curr;
					break;
			}

		    // only 12 red cubes, 13 green cubes, and 14 blue cubes per hand
            if(red > 12 || green > 13 || blue > 14) {
                printf("Game %d had impossible numbers\n", id);
                break;
            }

            if(strstr(ptr, ";")) {
                printf("resetting");
                red = 0;
                green = 0;
                blue = 0;
            }
		}
	}

	printf("Catching cheaters...\n");

	printf("Part1: %d", answer);

	return 0;
}
