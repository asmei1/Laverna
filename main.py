from laverna.analyser import CodeAnalyser, CodeSimilarityTool
from laverna.code_unit import CodeUnit


# testing usage
anl = CodeSimilarityTool()

def compute_ab_and_ba_sim(title, code_unit_a, code_unit_b):
    ratio = anl.simple_similarity_ratio(code_unit_a, code_unit_b)
    print(title, ratio)

def compute_ab_and_ba_sim_fun(title, code_unit_a, code_unit_b):
    ratio = anl.complex_similarity_ratio(code_unit_a, code_unit_b)
    print(title, ratio)

def test_all():
    cu_1_a = CodeUnit(["examples/plagiarisms/1/1.c"])
    cu_1_b = CodeUnit(["examples/plagiarisms/1/1p.c"])

    cu_2_a = CodeUnit(["examples/plagiarisms/2/2.c"])
    cu_2_b = CodeUnit(["examples/plagiarisms/2/2b.c"])

    cu_3_a = CodeUnit(["examples/plagiarisms/3/3.c"])
    cu_3_b = CodeUnit(["examples/plagiarisms/3/3b.c"])

    cu_4_a = CodeUnit(["examples/plagiarisms/4/4.c"])
    cu_4_b = CodeUnit(["examples/plagiarisms/4/4b.c"])

    cu_5_a = CodeUnit(["examples/plagiarisms/5/5.c"])
    cu_5_b = CodeUnit(["examples/plagiarisms/5/B/main.c", "examples/plagiarisms/5/B/utils.h",
                       "examples/plagiarisms/5/B/utils.c"])

    cu_6_a = CodeUnit(["examples/plagiarisms/6/6.c"])
    cu_6_b = CodeUnit(["examples/plagiarisms/6/6b.c"])

    # cu_7_a = CodeUnit(["examples/plagiarisms/7/7.c"])
    # cu_7_b = CodeUnit(["examples/plagiarisms/7/B/main.c", "examples/plagiarisms/7/B/comparators.h",
    #                    "examples/plagiarisms/7/B/comparators.c"])

    cu_8_a = CodeUnit(["examples/plagiarisms/8/8.c"])
    cu_8_b = CodeUnit(["examples/plagiarisms/8/8b.c"])

    cu_9_a = CodeUnit(["examples/plagiarisms/9/A/6.29.c", "examples/plagiarisms/9/A/format_type.h"])
    cu_9_b = CodeUnit(["examples/plagiarisms/9/B/6.29.c", "examples/plagiarisms/9/B/format_type.h"])

    cu_10_a = CodeUnit(["examples/plagiarisms/10/10.c"])
    cu_10_b = CodeUnit(["examples/plagiarisms/10/B/main.c", "examples/plagiarisms/10/B/utils.h",
                        "examples/plagiarisms/10/B/utils.c"])

    cu_11_a = CodeUnit(["examples/plagiarisms/11/11.c"])
    cu_11_b = CodeUnit(["examples/plagiarisms/11/11b.c"])

    cu_12_a = CodeUnit(["examples/plagiarisms/12/A/11.10.c", "examples/plagiarisms/12/A/doubly_linked_list.h",
                        "examples/plagiarisms/12/A/doubly_linked_list.c"])
    cu_12_b = CodeUnit(["examples/plagiarisms/12/B/main.c", "examples/plagiarisms/12/B/doubly_linked_list.h",
                        "examples/plagiarisms/12/B/doubly_linked_list.c"])

    cu_13_a = CodeUnit(["examples/plagiarisms/13/A/main.c", "examples/plagiarisms/13/A/linked_list.h",
                        "examples/plagiarisms/13/A/linked_list.c"])
    cu_13_b = CodeUnit(["examples/plagiarisms/13/B/11.8.c", "examples/plagiarisms/13/B/linked_list.h",
                        "examples/plagiarisms/13/B/linked_list.c"])



    compute_ab_and_ba_sim("Example 1:", cu_1_a, cu_1_b)
    compute_ab_and_ba_sim("Example 2:", cu_2_a, cu_2_b)
    compute_ab_and_ba_sim("Example 3:", cu_3_a, cu_3_b)
    compute_ab_and_ba_sim("Example 4:", cu_4_a, cu_4_b)
    compute_ab_and_ba_sim("Example 5:", cu_5_a, cu_5_b)
    compute_ab_and_ba_sim("Example 6:", cu_6_a, cu_6_b)
    # compute_ab_and_ba_sim("Example 7:", cu_7_a, cu_7_b)
    compute_ab_and_ba_sim("Example 8:", cu_8_a, cu_8_b)
    compute_ab_and_ba_sim("Example 9:", cu_9_a, cu_9_b)
    compute_ab_and_ba_sim("Example 10:", cu_10_a, cu_10_b)
    compute_ab_and_ba_sim("Example 11:", cu_11_a, cu_11_b)
    compute_ab_and_ba_sim("Example 12:", cu_12_a, cu_12_b)
    compute_ab_and_ba_sim("Example 13:", cu_13_a, cu_13_b)

    print("Functions")
    compute_ab_and_ba_sim_fun("Example 1:", cu_1_a, cu_1_b)
    compute_ab_and_ba_sim_fun("Example 2:", cu_2_a, cu_2_b)
    compute_ab_and_ba_sim_fun("Example 3:", cu_3_a, cu_3_b)
    compute_ab_and_ba_sim_fun("Example 4:", cu_4_a, cu_4_b)
    compute_ab_and_ba_sim_fun("Example 5:", cu_5_a, cu_5_b)
    compute_ab_and_ba_sim_fun("Example 6:", cu_6_a, cu_6_b)
    # compute_ab_and_ba_sim_fun("Example 7:", cu_7_a, cu_7_b)
    compute_ab_and_ba_sim_fun("Example 8:", cu_8_a, cu_8_b)
    compute_ab_and_ba_sim_fun("Example 9:", cu_9_a, cu_9_b)
    compute_ab_and_ba_sim_fun("Example 10:", cu_10_a, cu_10_b)
    compute_ab_and_ba_sim_fun("Example 11:", cu_11_a, cu_11_b)
    compute_ab_and_ba_sim_fun("Example 12:", cu_12_a, cu_12_b)
    compute_ab_and_ba_sim_fun("Example 13:", cu_13_a, cu_13_b)
    compute_ab_and_ba_sim_fun("Wrong sample:", cu_13_a, cu_12_b)
    compute_ab_and_ba_sim_fun("Wrong sample:", cu_13_a, cu_11_b)

test_all()




# code_unit_a = CodeUnit(["examples/main.c"])
# anl.simple_similarity_ratio(code_unit_a, code_unit_a)
# #
# cu_6_a = CodeUnit(["examples/plagiarisms/6/6.c"])
# cu_6_b = CodeUnit(["examples/plagiarisms/6/6b.c"])
# anl.functions_similarity_ratio(cu_6_a, cu_6_b)
# compute_ab_and_ba_sim("Example 6:", cu_6_a, cu_6_b)
#
# cu_13_a = CodeUnit(["examples/plagiarisms/13/A/main.c", "examples/plagiarisms/13/A/linked_list.h",
#                     "examples/plagiarisms/13/A/linked_list.c"])
# cu_13_b = CodeUnit(["examples/plagiarisms/13/B/11.8.c", "examples/plagiarisms/13/B/linked_list.h",
#                     "examples/plagiarisms/13/B/linked_list.c"])
# compute_ab_and_ba_sim_fun("Example 13:", cu_13_a, cu_13_b)
