import sys


def get_word(line):
    while line and line[0].isspace():
        line = line[1:]
    if not line:
        return None
    i, c = 0, 0
    while i < len(line) and not line[i].isspace():
        i += 1

    return line[c:i], line[i:]


def is_a_good_rule_sym(word):
    return word and word[0].isupper() and\
        all(c.isupper() or c == '_' for c in word)


def parse_grammar_line(line):

    gen_wrd, line = get_word(line)
    if not gen_wrd or not is_a_good_rule_sym(gen_wrd):
        return None, []

    wrd, line = get_word(line)
    if wrd != '::=':
        return None, []

    parts = []
    while line and not line.isspace():
        wrd, line = get_word(line)
        if not wrd:
            break
        parts.append(wrd)

    if not parts:
        return None, []

    return gen_wrd, [p for p in parts if is_a_good_rule_sym(p)]


def is_symbol(part):
    return part and part[0].isupper()


def check_grammar_and_report(grammar_file):
    with open(grammar_file, 'r') as f:
        lines = [(i, l) for (i, l) in enumerate(f.readlines()) if l.strip()]

    all_symbols, symbols_with_rules = set(), set(["EMPTY"])
    for line_no, line in lines:
        sym, parts = parse_grammar_line(line)
        if not sym:
            print "Error in line numbered", (line_no + 1)
            return

        all_symbols.add(sym)
        if sym in symbols_with_rules:
            print line_no + 1, sym, "has already a generating rule"

        symbols_with_rules.add(sym)

        for part in parts:
            if is_symbol(part):
                all_symbols.add(part)

    for sym in all_symbols.difference(symbols_with_rules):
        print sym, "has no generating rule"


def main():
    check_grammar_and_report(sys.argv[1])


if __name__ == '__main__':
    main()
