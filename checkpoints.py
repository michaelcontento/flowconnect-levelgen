#!/usr/bin/env python

import sys
import math
import random

def split_chars(data, n):
    return [data[i:i+n] for i in xrange(0, len(data), n)]

def conv1to2(pos, size):
    x = pos % size
    y = int(pos / size)
    return (x, y)

def conv2to1(x, y, size):
    return (y * size) +x

def move(x, y, direction):
    if direction == "l":
        x -= 1
    elif direction == "r":
        x += 1
    elif direction == "u":
        y -= 1
    elif direction == "d":
        y += 1

    return (x, y)

def process_line(line):
    # no exclamation mark? no record for us
    if not "!" in line:
        sys.stdout.write(line)
        return

    # only process lvl-records
    token, data = line.split("!")
    if token != "lvl":
        sys.stdout.write(line)
        return

    # extract some stuff
    clean_data = [x for x in data if x in ("l", "r", "d", "u")]
    size = math.sqrt(len(clean_data))

    # detect the end number
    data_spaced = data.replace("l", " l ").replace("r", " r ").replace("d", " d ").replace("u", " u ")
    numbers = [int(x) for x in data_spaced.split() if x.isdigit()]
    max_nbr = sorted(numbers)[-1]

    # detect the position of the start number
    start_pos = 0
    while True:
        try:
            start_pos = data.index("1", start_pos + 1)
        except ValueError:
            break
    for nbr in numbers:
        if nbr == 1:
            break

        if nbr >= 10:
            start_pos -= 2
        else:
            start_pos -= 1

    # validate size
    if size != int(size):
        sys.stdout.write(line)
        return
    else:
        size = int(size)

    # create empty table
    table = [dict(x=-1, y=-1, nbr=-1) for _ in xrange(len(clean_data))]
    board = split_chars(clean_data, size)

    # flag the start
    x, y = conv1to2(start_pos, size)
    table[0]["x"] = x
    table[0]["y"] = y
    table[0]["nbr"] = 1

    # build the whole table
    for idx, entry in enumerate(table):
        # ignore the last entry
        if idx == (size * size) - 1:
            continue

        direction = board[entry["y"]][entry["x"]]
        x, y = move(entry["x"], entry["y"], direction)

        table[idx + 1]["x"] = x
        table[idx + 1]["y"] = y

    # flag the end
    table[-1]["nbr"] = max_nbr

    # create random checkpoints
    checkpoints = []
    while len(checkpoints) < max_nbr - 2:
        nbr = random.randint(1, (size * size) - 2)
        if nbr not in checkpoints:
            checkpoints.append(nbr)

    # flag checkpoints
    for nbr, idx in enumerate(sorted(checkpoints), start=2):
        table[idx]["nbr"] = nbr

    # create new data
    result = []
    for entry in table:
        pos = conv2to1(entry["x"], entry["y"], size)

        token = clean_data[pos]
        if entry["nbr"] > 0:
            token = str(entry["nbr"]) + token

        result.append((pos, token))
    data_new = "".join([x[1] for x in sorted(result)])

    # and print everythin
    sys.stdout.write("lvl!")
    sys.stdout.write(data_new)

    if line[-1] == "\n":
        sys.stdout.write("\n")

for filename in sys.argv[1:]:
    with open(filename, "r") as file:
        for line in file:
            process_line(line)
