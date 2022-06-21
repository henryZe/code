import sys, os
import getopt
import openpyxl
import pandas
import git
import json

# read total commits from xlsx
#
# check whether there is "Fixes" in linux main stream:
#     if not:
#         continue
#     else:
#         if already in hulk-7.5:
#             write commit-id in linux_patch & hulk-7.5
#         else:
#             write commit-id in linux
#
# update data into xlsx

def gain_xlsx_target_commit(xlsx_path):

    assert os.path.exists(xlsx_path)
    xlsx = pandas.read_excel(xlsx_path, sheet_name='total', usecols='A,B')

    cols = []
    for value in xlsx.values:
        cols.append({"target": value[0], "msg": value[1]})

    return cols

def check_fix_in_source_repo_per(id, repo, branch, date):

    assert os.access(repo, os.F_OK)
    g = git.Git(repo)
    g.checkout(branch)

    grep_cond = "--grep=Fixes: {}".format(id["target"])
    date_cond = "--after={}".format(date)

    loginfo = g.log('--pretty={"commit":"%h"}',
                    date_cond, grep_cond)

    if not loginfo:
        id["src_fix"] = None
        return

    commits = loginfo.split("\n")

    # multi fixes refers to a bug
    for commit in commits:
        info_json = json.loads(commit)
        if "src_fix" not in id:
            id["src_fix"] = [info_json["commit"]]
        else:
            id["src_fix"].append(info_json["commit"])

    return

def check_fix_in_target_repo_per(id, repo, branch, date):

    assert os.access(repo, os.F_OK)
    g = git.Git(repo)
    g.checkout(branch)

    if not id['src_fix']:
        id["dest_repo"] = None
        return

    grep_cond = "--grep=Fixes: {}".format(id["target"])
    date_cond = "--after={}".format(date)

    loginfo = g.log('--pretty={"commit":"%h"}',
                    date_cond, grep_cond)

    if not loginfo:
        id["dest_repo"] = None
        return

    commits = loginfo.split("\n")

    # multi fixes refers to a bug
    for commit in commits:
        info_json = json.loads(commit)
        if "dest_repo" not in id:
            id["dest_repo"] = [info_json["commit"]]
        else:
            id["dest_repo"].append(info_json["commit"])

    return

def list2str(l):
    if not l:
        return None

    new_l = l[:]
    str_l = ',\n'.join(new_l)
    return str_l

def update_xlsx_commit_per(id, row, new_xlsx_path,
                    source_repo_path, source_branch,
                    target_repo_path, target_branch):

    l = [[id["target"], id["msg"], list2str(id["src_fix"]), list2str(id["dest_repo"])]]

    df = pandas.DataFrame(l, columns=["commit id", "content",
                                    source_repo_path + ' ' + source_branch,
                                    target_repo_path + ' ' + target_branch])

    if row > 0:
        df.to_csv(new_xlsx_path, mode='a', index=False, header=False)
    else:
        df.to_csv(new_xlsx_path, mode='w', index=False)

    return

def main(script_name, argv):
    rule = 'python3 {} [-i input_file] [-o output_file] [--source_repo ./linux_repo_path] [--source_branch master] [--target_repo_path ./linux-rh-3-10] [--target_branch redhat-7.5.x-next] [--date yyyy-mm-dd]'.format(script_name)

    try:
        opts, args = getopt.getopt(argv, "hi:o:",
                                    ["help=",
                                    "input=", "output=",
                                    "source_repo=", "source_branch=",
                                    "target_repo=", "target_branch=",
                                    "date="])
    except getopt.GetoptError:
        print(rule)
        sys.exit(2)

    inputfile = "./hulk-7.5-patch-merged.xlsx"
    outputfile = "./hulk-7.5-patch-merged-newgen.csv"

    source_repo_path = "../linux"
    source_branch = "master"

    target_repo_path = "../linux-rh-3-10"
    target_branch = "redhat-7.5.x-next"

    date = "2022-01-01"

    for opt, arg in opts:
        if opt in ('-h', "--help"):
            print(rule)
            sys.exit()

        elif opt in ("-i", "--input"):
            inputfile = arg
        elif opt in ("-o", "--output"):
            outputfile = arg

        elif opt in ("--source_repo"):
            source_repo_path = arg
        elif opt in ("--source_branch"):
            source_branch = arg

        elif opt in ("--target_repo"):
            target_repo_path = arg
        elif opt in ("--target_branch"):
            target_branch = arg

        elif opt in ("--date"):
            date = arg

    commit_ids = gain_xlsx_target_commit(inputfile)

    for i in range(len(commit_ids)):
        check_fix_in_source_repo_per(commit_ids[i], source_repo_path, source_branch, date)
        check_fix_in_target_repo_per(commit_ids[i], target_repo_path, target_branch, date)
        update_xlsx_commit_per(commit_ids[i], i, outputfile,
                            os.path.basename(source_repo_path), source_branch,
                            os.path.basename(target_repo_path), target_branch)

    return

if __name__ == "__main__":
    main(sys.argv[0], sys.argv[1:])
