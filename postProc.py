#!/usr/bin/env python3
# -*- coding: utf-8 -*-

if __name__ == "__main__":
    file_a = []
    
    with open("log.txt", "r") as logFile:
        file_a = logFile.readlines();

    types = {}

    for entry in file_a:
        entry = entry.strip()

        type_a, size, val = entry.split()

        if(type_a not in types):
            types[type_a] = {}

        if(size not in types[type_a]):
            types[type_a][size] = []

        types[type_a][size].append(val)


    for entry in types:
        with open(entry + ".txt", "w") as procFile:
            for size in types[entry]:
                procFile.write(size + ", " + types[entry][size][0] + "\n");

    
