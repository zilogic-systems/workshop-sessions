#!/usr/bin/env python
"""
Usage: split.py <filename>

Splits the file into parts and stores them under a directory called
`filename` (the input filename with extension stripped).

Each part to be split should be delimited by patterns shown below.

### START: part-filename
...
content
...
### END: part-filename

The `content` will be stored within the directory in a file called
`part-filename`.
"""

from __future__ import print_function

import re
import sys
import os
import os.path


start_regex = re.compile("### START: ([-.a-z0-9]*)")
end_regex = re.compile("### END: ([-.a-z0-9]*)")


def get_starts_ends(script):
    starts = {}
    ends = {}

    for lineno, line in enumerate(script):
        match = start_regex.search(line)
        if match:
            filename = match.group(1)
            starts[filename] = lineno

        match = end_regex.search(line)
        if match:
            filename = match.group(1)
            ends[filename] = lineno

    return (starts, ends)


def write_part(part_filename, script, start_lineno, end_lineno):
    with open(part_filename, "w") as fp:
        for line in range(start_lineno + 1, end_lineno):
            text = script[line]
            if not (start_regex.search(text) or end_regex.search(text)):
                fp.write(script[line])
                

def split(script_filename, script):
    starts, ends = get_starts_ends(script)

    start_filenames = set(starts.keys())
    end_filenames = set(ends.keys())

    if start_filenames != end_filenames:
        print("Unmatched START and END:",
              start_filenames ^ end_filenames)
        sys.exit(1)

    root, ext = os.path.splitext(script_filename)
    if os.path.exists(root):
        if not os.path.isdir(root):
            print("File {0} is in the way".format(root))
            sys.exit(1)
    else:
        os.mkdir(root)

    for filename in start_filenames:
        start_lineno = starts[filename]
        end_lineno = ends[filename]
        write_part(os.path.join(root, filename),
                   script, start_lineno, end_lineno)


def main(script_filename):
    with open(script_filename) as fp:
        script = fp.readlines()

    split(script_filename, script)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(__doc__)
    
    main(sys.argv[1])
