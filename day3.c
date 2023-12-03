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

int walk(char *schematic, char *symbols) {
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
				printf("Found engine part %d\n", num);
				answer += num;
				break;
			}
		}

		i += len-1;
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

	printf("Found a %d %d buffer\n", len, len);
	printf("Map:\n%s", buffer);

	map_symbols(buffer, symbols);

	printf("\nSymbols:\n%s", symbols);

	int answer = walk(buffer, symbols);

	printf("The answer is %d\n", answer);

	free(buffer);
	free(symbols);
	return 0;
}
