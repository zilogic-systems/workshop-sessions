#!/usr/bin/env python3
"""
Usage: gen-versions.py <versions.yaml> <output>

Reads a flat YAML file of `name: value` pairs and writes the pairs in the
format selected by the extension of <output>:

  *.sh    NAME_WITH_UNDERSCORES="value"   (for sourcing from bash)
  *.adoc  :name-with-hyphens: value       (for including from AsciiDoc)

Example input:

    bitbake-ver: yocto-6.0
    less-ver: 710

Names are normalised, so `less-ver` and `less_ver` are equivalent in the YAML
file. All values are read as strings, so a version such as 1.10 is not turned
into the number 1.1.
"""

import os
import shlex
import sys

import yaml


def load(filename):
    with open(filename) as fp:
        # BaseLoader keeps every scalar as a string (no 1.10 -> 1.1).
        data = yaml.load(fp, Loader=yaml.BaseLoader)

    if not isinstance(data, dict):
        sys.exit("{0}: expected a flat mapping of name: value".format(filename))

    for name, value in data.items():
        if not isinstance(value, str):
            sys.exit("{0}: value of '{1}' is not a plain string"
                     .format(filename, name))
    return data


def write_sh(fp, data):
    for name, value in data.items():
        var = name.upper().replace("-", "_")
        fp.write("{0}={1}\n".format(var, shlex.quote(value)))


def write_adoc(fp, data):
    for name, value in data.items():
        attr = name.lower().replace("_", "-")
        fp.write(":{0}: {1}\n".format(attr, value))


def main(yaml_filename, output_filename):
    data = load(yaml_filename)

    ext = os.path.splitext(output_filename)[1]
    writers = {".sh": write_sh, ".adoc": write_adoc}
    if ext not in writers:
        sys.exit("Unsupported output extension: {0}".format(ext))

    with open(output_filename, "w") as fp:
        writers[ext](fp, data)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(__doc__)
        sys.exit(1)

    main(sys.argv[1], sys.argv[2])
