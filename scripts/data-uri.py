#!/usr/bin/env python
"""Command line script to convert a file, usually an image, into a data URI
for use on the web."""

import base64
import os
import sys


class FileNotFoundError(Exception):
    pass


def img_to_data(mime, path):
    """Convert a file (specified by a path) into a data URI."""
    if not os.path.exists(path):
        raise FileNotFoundError
    with open(path, 'rb') as fp:
        data = fp.read()
        data64 = u''.join(base64.encodestring(data).splitlines())
        return u'data:%s;base64,%s' % (mime, data64)


def usage(argv):
    print 'Usage: %s <mime-type> <path-to-file>' % argv[0]


if __name__ == '__main__':
    try:
        mimetype = sys.argv[1]
        path = sys.argv[2]
    except IndexError:
        usage(sys.argv)
        sys.exit(1)

    try:
        print img_to_data(mimetype, path)
    except FileNotFoundError:
        print 'File not found!'
        sys.exit(2)
