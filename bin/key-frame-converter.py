#!/usr/bin/env python

import argparse
import os
import time
import json

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Convert KeyFrameTrajectory.txt to json or js')
    parser.add_argument('input', help='KeyFrameTrajectory.txt')
    parser.add_argument('output',help='Output destination')
    
    args = parser.parse_args()

    pose = []
    with open(args.input) as keyFrame:
        lines = keyFrame.readlines()
        for l in lines:
            to_float = map(lambda n: float(n), l.split())
            pose.append(to_float)
            print to_float

    with open(args.output, 'w') as js:
        json.dump(pose, js, indent=2)

