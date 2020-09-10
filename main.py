from laverna import parser, analyzer


# testing usage
# anl = analyzer.Analyzer()
# parse_unit_a = parser.ParseUnit("examples/plagiarisms/1.c")
# parse_unit_b = parser.ParseUnit("examples/plagiarisms/1p.c")
#
# parse_unit_a.parse()
# parse_unit_b.parse()
# print(parse_unit_a.get_cursors_kind())
# print(parse_unit_b.get_cursors_kind())
# A = ' '.join(str(node)for node in parse_unit_a.get_cursors_kind())
# B = ' '.join(str(node)for node in parse_unit_b.get_cursors_kind())
#
# score = difflib.SequenceMatcher(a=A, b=B).ratio()
# print(score)

def compute_similarity_score(file_a, file_b):
    parse_unit_a = parser.ParseUnit(file_a)
    parse_unit_b = parser.ParseUnit(file_b)

    parse_unit_a.parse()
    parse_unit_b.parse()

    return analyzer.Analyzer().compute_similarity_ratio(parse_unit_a, parse_unit_b)


def compute_ab_and_ba_sim(title, file_a, file_b):
    ab = compute_similarity_score(file_a, file_b)
    ba = compute_similarity_score(file_b, file_a)
    print(title, "AB", ab, "BA", ba)

parse_unit_a = parser.ParseUnit("examples/main.c")
parse_unit_a.parse()

print(parse_unit_a.dump())

compute_ab_and_ba_sim("Example 1:", "examples/plagiarisms/1/1.c", "examples/plagiarisms/1/1p.c")
# compute_ab_and_ba_sim("Example 2:", "examples/plagiarisms/2/2.c", "examples/plagiarisms/2/2b.c")
# compute_ab_and_ba_sim("Example 3:", "examples/plagiarisms/3/3.c", "examples/plagiarisms/3/3b.c")
# compute_ab_and_ba_sim("Example 4:", "examples/plagiarisms/4/4.c", "examples/plagiarisms/4/4b.c")
# compute_ab_and_ba_sim("Example 5:", "examples/plagiarisms/5/5.c", "examples/plagiarisms/5/B/main.c")
# compute_ab_and_ba_sim("Example 6:", "examples/plagiarisms/6/6.c", "examples/plagiarisms/6/6b.c")
# compute_ab_and_ba_sim("Example 7:", "examples/plagiarisms/7/7.c", "examples/plagiarisms/7/B/main.c")
# compute_ab_and_ba_sim("Example 8:", "examples/plagiarisms/8/8.c", "examples/plagiarisms/8/8b.c")
# compute_ab_and_ba_sim("Example 9:", "examples/plagiarisms/9/A/6.29.c", "examples/plagiarisms/9/B/6.29.c")
# compute_ab_and_ba_sim("Example 10:", "examples/plagiarisms/10/10.c", "examples/plagiarisms/10/B/main.c")
# compute_ab_and_ba_sim("Example 11:", "examples/plagiarisms/11/11.c", "examples/plagiarisms/11/11b.c")



'''
# print(anl.find_structers(parse_unit_a))
# parse_unit_a.dump_cursors_kind()
#dump
print('Dump')
parse_unit.dump()

#find global variables
print('\n\n')
print('find global variables')
print(anl.find_global_variables(parse_unit))

#find array operator usage
print('\n\n')
print('find array operator usage')
print(anl.find_array_operators(parse_unit) )

#get addtional includes
print('\n\n')
print('get addtional includes')
includes = parse_unit.get_all_additional_includes()
for i in includes:
    print('--' * i[0], i[1])
'''

# get comments
# print('\n\n')
# print('get comments')
# print(anl.get_comments(parse_unit))
