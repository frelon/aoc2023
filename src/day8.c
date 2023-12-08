#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int key(char* str) {
    return 10000 * (int)str[0] + 100 * (int)str[1] + (int)str[2];
}

typedef struct {
    char* name;
    int left;
    int right;
} node;

int part1(char *directions, node *nodes) {
    int curr = key("AAA");
    int steps = 0;
    const int end_key = key("ZZZ");
    for(int i = 0; curr != end_key; i++) {
        if(i >= strlen(directions)) {
            i = 0;
        }

        int next = directions[i] == 'L' ? nodes[curr].left : nodes[curr].right;

        curr = next;
        steps++;
    }

    return steps;
}

int walk2(char *directions, node *nodes, int start) {
    int curr = start;
    int steps = 0;
    for(int i = 0; nodes[curr].name[2] != 'Z' ; i++) {
        if(i >= strlen(directions)) {
            i = 0;
        }

        int next = directions[i] == 'L' ? nodes[curr].left : nodes[curr].right;

        /* printf("FROM %s -> '%c' -> %s\n", nodes[curr].name, directions[i], nodes[next].name); */

        curr = next;
        steps++;
    }

    return steps;
}

int part2(char *directions, node *nodes, int* starters) {
    int answer = 0;

    int steps[10] = {0};
    for(int i = 0; starters[i] != 0; i++) {
        steps[i] = walk2(directions, nodes, starters[i]);
        printf("%s takes %d steps\n", nodes[starters[i]].name, steps[i]);
    }

    // TODO: calculate LCM
    return steps[0];
}

int main() {
    FILE *inputfd;
	inputfd = fopen("./input/input8.txt", "r");
	if (inputfd == NULL) {
		printf("Error opening file!");
		return 1;
	}

	char *line, *directions;
	size_t buflen = 0, dirlen = 0;
	ssize_t read;

	int answer = 0;

    printf("Reading instructions...\n");

    read = getline(&directions, &dirlen, inputfd);
    directions[strlen(directions)-1] = '\0';

    printf("Read directions: %s\n", directions);

    getline(&line,&buflen,inputfd);

    node *nodes = (node*)malloc(sizeof(node)*1000000);
    int starters[100] = {0};
    int num_starters = 0;
    
	while ((read = getline(&line, &buflen, inputfd)) != -1) {
        int k = key(line);
        int l = key(&line[7]);
        int r = key(&line[12]);

        node n = { .name = (char*)malloc(sizeof(char[3])), .left = l, .right = r};
        memcpy(n.name, line, sizeof(char[3]));
        n.name[3] ='\0';
        nodes[k] = n;

        if(n.name[2] == 'A') {
            printf("Found starter %s\n", n.name);
            starters[num_starters] = k;
            num_starters++;
        }
    }

    printf("Parsed nodes\n");

    int p1 = part1(directions, nodes);

    printf("...\n");

    int p2 = part2(directions, nodes, starters);

    printf("Part1: %d\nPart2: %d\n", p1, p2);

    free(nodes);
	return 0;
}
