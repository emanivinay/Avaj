from sys import argv

def main():
    with open(argv[1]) as f:
        lines = [l[:-1] for l in f.readlines()]
        lines = ["#pragma once"] + lines[2:-1]

    with open(argv[1], 'w') as f:
        f.writelines([l + "\n" for l in lines])

if __name__ == '__main__':
    main()
