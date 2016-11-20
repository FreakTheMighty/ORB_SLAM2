#!/usr/bin/env python

import argparse
import os
import time

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate frame maniest file')
    parser.add_argument('-d','--directory', help='Directory containing image sequence')
    parser.add_argument('-r','--rate', help='Frame rate')
    
    args = parser.parse_args()
    images = os.listdir(args.directory)
    basename = os.path.basename(args.directory)
    rgb_dir = os.path.dirname(args.directory)
    t = 0.0
    header = '''# color images
# file: 'rgbd_dataset_freiburg1_desk.bag'
# timestamp filename
'''    
    
    inc = 1/float(args.rate)
    with open(os.path.join(rgb_dir,'rgb.txt'), 'w') as manifest:
        manifest.write(header)
        for img in images:
            line = '%6f %s\n' % (t, os.path.join(basename, img))
            manifest.write(line)
            t += inc

