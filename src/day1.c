#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strtodigit(char *str) {
    const static char *digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    char cmp[10];

    for(int i=0; i<9; i++) {
        int len = strlen(digits[i]);
        strncpy(cmp, str, len);
        cmp[len] = '\0';

        if(strcmp(cmp, digits[i]) == 0) {
            return i+1;
        }
    }

    return 0;
}

int part1() {
	FILE *inputfd;
	inputfd = fopen("input/input1.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line;
	size_t buflen = 0;
	ssize_t read;
	int sum = 0;

    printf("Reading calibration values...\n");

	while ((read = getline(&line, &buflen, inputfd)) != -1) {
		int len = strlen(line);

		int num1, num2;
		for(uint i = 0; i < len-1; i++) {
			num1 = line[i] - '0';
			if(num1 >= 0 && num1 <= 9) {
				break;
			}
		}

		for(uint i = len-1; i >= 0; i--) {
            num2 = line[i] - '0';
			if(num2 >= 0 && num2 <= 9) {
				break;
			}
        }

		sum += (num1*10)+num2;
	}

    printf("Calculating trebuchet trajectories...\n");

    return sum;
}

int part2() {
	FILE *inputfd;
	inputfd = fopen("input1.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line;
	size_t buflen = 0;
	ssize_t read;
	int sum = 0;

    printf("Scrumming calibration values twice...\n");

	while ((read = getline(&line, &buflen, inputfd)) != -1) {
		int len = strlen(line);

		int num1, num2;
		for(uint i = 0; i < len-1; i++) {
			num1 = line[i] - '0';
			if(num1 >= 0 && num1 <= 9) {
				break;
			}

			num1 = strtodigit(&line[i]);
            if(num1 != 0) {
        	    break;
            }
		}

		for(uint i = len-1; i >= 0; i--) {
            num2 = line[i] - '0';
			if(num2 >= 0 && num2 <= 9) {
				break;
			}

            num2 = strtodigit(&line[i]);
            if(num2 != 0) {
                break;
            }
        }

		sum += (num1*10)+num2;
	}

    printf("All done!\n");

    return sum;
}

int main() {
	printf("Solving day1!\n");
    
    int sum1 = part1();
    int sum2 = part2();

	printf("Part1: %d\nPart2: %d\n", sum1, sum2);
	return 0;
}

