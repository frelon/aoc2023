package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Mapping struct {
	source int
	dest   int
	length int
}

type Map []Mapping

func main() {
	data, err := os.ReadFile("./input/input5.txt")
	if err != nil {
		fmt.Printf("ERROR reading input!")
		return
	}

	str := string(data)
	mappings := strings.Split(str, "\n\n")

	maps := []Map{}
	for _, mapping := range mappings[1:] {
		m := Map{}

		map_split := strings.Split(mapping, "\n")
		for _, r := range map_split[1:] {
			if r == "" {
				break
			}
			split := strings.Split(r, " ")
			dest, err := strconv.Atoi(split[0])
			if err != nil {
				panic(err)
			}
			source, err := strconv.Atoi(split[1])
			if err != nil {
				panic(err)
			}
			length, err := strconv.Atoi(split[2])
			if err != nil {
				panic(err)
			}
			m = append(m, Mapping{
				source: source,
				dest:   dest,
				length: length,
			})
		}

		maps = append(maps, m)
	}

	seed_split := strings.Split(mappings[0][7:], " ")
	seeds := make([]int, len(seed_split))
	for i, s := range seed_split {
		seed, err := strconv.Atoi(s)
		if err != nil {
			panic(err)
		}
		seeds[i] = seed
	}

	lowest := 10000000000

	for _, seed := range seeds {
		transformed := transform(seed, maps)
		if transformed < lowest {
			lowest = transformed
		}
	}

	fmt.Printf("Part1: %d\n", lowest)

	lowest = 10000000000
	for i := 0; i < len(seeds); i += 2 {
		for j := seeds[i]; j < seeds[i]+seeds[i+1]; j++ {
			transformed := transform(j, maps)
			if transformed < lowest {
				lowest = transformed
			}
		}
	}

	fmt.Printf("Part2: %d\n", lowest)
}

func transform(start int, maps []Map) int {
	n := start

	for _, m := range maps {
		for _, mapping := range m {
			if n >= mapping.source && n < mapping.source+mapping.length {
				n = mapping.dest + (n - mapping.source)
				break
			}
		}
	}

	return n
}
