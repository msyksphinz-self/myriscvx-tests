#!/usr/bin/python3

import json
import itertools
import sys
import os
import subprocess
import numpy as np
from threading import Thread
from threading import Lock
import asyncio

def compile_arch(arch, result_fp, lock):
    print("Archicture : {}".format(arch[0]))

    test_result_array = []

    for test in tests.items():
        if test[1]["enable"] != 1:
            continue

        cfg_list = []
        for cfg in arch[1].items():
            cfg_list += [cfg[1]]

        if not "source" in test[1].keys():
            print("test {} \"source\" key not found.".format(test[0]))
            exit()

        input_source = test[1]["source"]
        print("  Source is {} ".format(input_source))
        for config in itertools.product(*cfg_list):

            dirname = 'results/' + test[0] + "_".join(config).replace(' ', '_')
            if not os.path.exists(dirname):
                os.mkdir(dirname)

            bitfile = dirname + "/" + test[0] + ".bc"
            llfile  = dirname + "/" + test[0] + ".ll"
            objfile = dirname + "/" + test[0] + ".o"
            dmpfile = dirname + "/" + test[0] + ".dmp"
            subprocess.run(["./bin/clang", "-march=native", "-c", config[0],
                             "../myriscvx-tests/" + input_source,
                             "-emit-llvm",
                             test[1]["clang_additional_opt"],
                             "-o", bitfile])
            subprocess.run(["./bin/llvm-dis", bitfile, "-o", llfile])

            result = []

            for filetype in ["asm", "obj"] :
                llc_command = ["./bin/llc", "-stats", "-debug", "-filetype=" + filetype, bitfile] + list(config[1:])

                # print("  Executing Command : {}".format(' '.join(llc_command)))

                ret = subprocess.run(llc_command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                logfile = dirname + "/" + test[0] + "." + filetype + ".log"
                with open(logfile, 'w') as log_fp:
                    log_fp.write('{}'.format(ret.stdout.decode('utf-8')))
                log_fp.close()
                result.append(ret.returncode)

            # objdump
            objdump_command = ["./bin/llvm-objdump", "-debug", "-d", objfile]
            ret = subprocess.run(objdump_command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            logfile = dirname + "/" + test[0] + ".objdump.log"
            with open(logfile, 'w') as log_fp:
                log_fp.write('{}'.format(ret.stdout.decode('utf-8')))
            log_fp.close()
            result.append(ret.returncode)

            print("    [{2},{3},{4}] Building {0} in {1} ...".format(test[0], dirname, result[0], result[1], result[2]))

            test_result_array.append([dirname, result[0], result[1], result[2]])
    result_fp_lock.acquire()
    result_fp.write("==== {} RESULT ====\n".format(arch[0]))
    for result in test_result_array:
        result_fp.write(" {0} {1} {2} : {3}\n".format(result[1], result[2], result[3], result[0]))
    result_fp_lock.release()


if __name__ == '__main__':
    config_file = sys.argv[1]

    with open(config_file) as file:
        json_dict = json.load(file)

    arch_configs = json_dict[0]
    tests = json_dict[1]
    # print(tests)

    if not os.path.exists("results"):
        os.mkdir("results")

    result_fp = open("result.txt", 'w')
    result_fp_lock = Lock()

    for arch in arch_configs.items():
        th = Thread(target=compile_arch, args=[arch, result_fp, result_fp_lock])
        th.start()

    for arch in arch_configs.items():
        th.join()

    # result_fp.close()
