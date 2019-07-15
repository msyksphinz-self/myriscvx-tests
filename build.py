#!/usr/bin/python3

import json
import itertools
import sys
import os
import subprocess
import numpy as np
from threading import Thread

def compile_arch(arch):
    print("Archicture : {}".format(arch[0]))
    for test in tests.items():
        cfg_list = []
        for cfg in arch[1].items():
            cfg_list += [cfg[1]]

        input_source = test[1]["source"]
        print("  Source is {} ".format(input_source))
        for config in itertools.product(*cfg_list):

            dirname = 'results/' + test[0] + "_".join(config).replace(' ', '_')
            print("    Building {} in {} ...".format(test[0], dirname))
            if not os.path.exists(dirname):
                os.mkdir(dirname)

            bitfile = dirname + "/" + test[0] + ".bc"
            llfile  = dirname + "/" + test[0] + ".ll"
            objfile = dirname + "/" + test[0] + ".o"
            dmpfile = dirname + "/" + test[0] + ".dmp"
            subprocess.call(["./bin/clang", "-c", config[0],
                             "../myriscvx-tests/" + input_source,
                             "-emit-llvm",
                             test[1]["clang_additional_opt"],
                             "-o", bitfile])
            subprocess.call(["./bin/llvm-dis", bitfile, "-o", llfile])

            for filetype in ["asm", "obj"] :
                llc_command = ["./bin/llc", "-stats", "-debug", "-filetype=" + filetype, bitfile] + list(config[1:])

                llc_log = ""
                try:
                    llc_log = subprocess.check_output(llc_command, stderr=subprocess.STDOUT)
                except subprocess.CalledProcessError as e:
                    print("Failed to build {} {}".format(test[1], config))
                    llc_log = e.output

                logfile = dirname + "/" + test[0] + "." + filetype + ".log"
                with open(logfile, 'w') as log_fp:
                    log_fp.write(str(llc_log))
                log_fp.close()

            # objdump
            objdump_command = ["./bin/llvm-objdump", "-debug", "-d", objfile]
            obj_log = subprocess.call(objdump_command, stderr=subprocess.STDOUT)
            with open(logfile, 'w') as log_fp:
                log_fp.write(str(obj_log))
            log_fp.close()


if __name__ == '__main__':
    config_file = sys.argv[1]

    with open(config_file) as file:
        json_dict = json.load(file)

    arch_configs = json_dict[0]
    tests = json_dict[1]
    # print(tests)

    if not os.path.exists("results"):
        os.mkdir("results")

    for arch in arch_configs.items():
        th = Thread(target=compile_arch, args=[arch])
        th.start()
