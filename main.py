from laverna import parser, analyzer

#testing usage
anl = analyzer.Analyzer()

parse_unit = parser.ParseUnit("examples/main.c")
parse_unit.parse()
'''
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

#get comments
print('\n\n')
print('get comments')
print(anl.get_comments(parse_unit))
