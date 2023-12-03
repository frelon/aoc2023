#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int issymbol(char c) {
	return !isdigit(c) && c != '.' && c != '\n';
}

void map_symbols(char *schematic, char *symbols) {
	int len = (int)(strchr(schematic, '\n') - schematic);

	for(int i = 0; i < strlen(schematic)-1; i++) {
		if(schematic[i] == '\n') {
			symbols[i] = '\n';
			continue;
		}

		if(issymbol(schematic[i])) {
			if(i > len) {
				memset(symbols+i-2-len, schematic[i], 3);
			}
			
			memset(symbols+i-1, schematic[i], 3);

			if(i < (len*(len))) {
				memset(symbols+i+len, schematic[i], 3);
			}
		}
	}
}

int part1(char *schematic, char *symbols) {
	char tmp[4];
	int answer = 0;
	for(int i = 0; i < strlen(schematic); i++) {
		if(!isdigit(schematic[i])) {
			continue;
		}

		int len = (int)(strchr(schematic+i, '.') - (schematic+i));
		if(len > 3) len = 3;

		strncpy(tmp, schematic+i, len);
		tmp[len] = '\0';

		int num = atoi(tmp);

		for(int j = 0; j < len; j++) {
			if(issymbol(symbols[i+j])) {
				answer += num;
				break;
			}
		}

		i += len-1;
	}

	return answer;
}

// getnum gets the number at index i, it will check backwards to find the whole
// number.
int getnum(char *schematic, int i) {
    if(!isdigit(schematic[i])) {
        return 0;
    }

    char tmp[4];
    int start = i;
    while(isdigit(schematic[start-1])) start--;
    int len = (int)(strchr(schematic+start, '.') - (schematic+start));
    if(len > 3) len = 3;

    strncpy(tmp, schematic+start, len);
    tmp[len] = '\0';

    return atoi(tmp);
}

int factor(int nums[8]) {
    int num1=0, num2=0, count = 0;
    for(int i = 0; i < 8; i++) {
        if(nums[i] != 0) {
            if(count == 0) {
                num1 = nums[i];
                count++;
                continue;
            }

            if(count == 1 && num1 == nums[i]) {
                continue;
            }

            if(count == 1) {
                num2 = nums[i];
                count++;
                continue;
            }

            printf("WTF(%d, %d)\n", num1, num2);
        }
        
    }
    
    return num1*num2;
}

void printgear(int nums[8]) {
    for(int i = 0; i < 8; i++) {
        printf("%d, ", nums[i]);
    }
    printf(" (%d)\n", factor(nums));
}

int part2(char *schematic) {
    int answer = 0;
	int len = (int)(strchr(schematic, '\n') - schematic);

    int i = 0;
    while(1) {
        i = (int)(strchr(schematic+i+1, '*') - schematic);
        if(i<0 || i > strlen(schematic)) {
            break;
        }


        int nums[8];
        nums[0] = getnum(schematic, i-len-2);
        nums[1] = getnum(schematic, i-len-1);
        nums[2] = getnum(schematic, i-len);
        nums[3] = getnum(schematic, i-1);
        nums[4] = getnum(schematic, i+1);
        nums[5] = getnum(schematic, i+len);
        nums[6] = getnum(schematic, i+len+1);
        nums[7] = getnum(schematic, i+len+2);


        int fact = factor(nums);
        answer += fact;

        printf("Found gear at idx %d, factor %d\n", i, fact);
        printgear(nums);
    }

    return answer;
}

int main() {
	FILE *inputfd;
	inputfd = fopen("input3.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	if(fseek(inputfd, 0, SEEK_END) != 0) {
		printf("Error seeking EOF!");
		return 2;
	}

	long file_size = ftell(inputfd);
	rewind(inputfd);

	char *buffer = (char*)malloc(file_size + 1);
	char *symbols = (char*)malloc(file_size + 1);

	memset(symbols, '.', file_size);

	fread(buffer, file_size, 1, inputfd);

	if(fclose(inputfd) != 0) {
		printf("Error closing file!");
		return 3;
	}

	int len = (int)(strchr(buffer, '\n') - buffer);

	printf("Map:\n%s", buffer);

	map_symbols(buffer, symbols);

	int answer1 = part1(buffer, symbols);
	int answer2 = part2(buffer);

	printf("Part1: %d\nPart2: %d\n", answer1, answer2);

	free(buffer);
	free(symbols);
	return 0;
}
