#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import OrderedDict
import math

if __name__ == "__main__":
    file_a = []
    
    with open("log.txt", "r") as logFile:
        file_a = logFile.readlines();

    types = {}

    for entry in file_a:
        entry = entry.strip()

        type_a, size, val = entry.split()

        if(type_a not in types):
            types[type_a] = OrderedDict()

        if(size not in types[type_a]):
            types[type_a][size] = val

    for entry in types:
        with open(entry + ".txt", "w") as procFile:
            for size in types[entry]:
                val = int(size)
                val = int(math.sqrt(val))
                
                procFile.write(str(val) + ", " + types[entry][size] + "\n");

    
