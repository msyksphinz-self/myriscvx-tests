#!/bin/sh

source=$1
bench=`basename $source | cut -f1 -d.`

option=("-O0" "-O1")
arch=("-march=mips" "-march=myriscvx32 -mcpu=simple32"  "-march=riscv32")
reloc=("static" "pic")
abis=("lp64" "stack32")
tailcall=("-enable-MYRISCVX-tail-calls=true" "-enable-MYRISCVX-tail-calls=false")

## -O0
for opt in "${option[@]}"
do
    for a in "${arch[@]}"
    do
        for rel in "${reloc[@]}"
        do
            for abi in "${abis[@]}"
            do
                for t in "${tailcall[@]}"
                do

                    mkdir -p result

                    work_dir=`echo ${bench}_${opt}_${a}_${rel}_${abi}_${t} | sed 's/\ /_/g'`
                    echo ${work_dir}
                    mkdir -p result/${work_dir}

                    if [ "${a}" != "-march=myriscvx32 -mcpu=simple32" ]; then
                        abi=""
                    fi

                    if [ "${a}" != "-march=myriscvx32 -mcpu=simple32" ]; then
                        t=""
                    fi

                    ./bin/clang ${opt} ${source} -c -emit-llvm -o result/${work_dir}/${bench}.bc
                    ./bin/llvm-dis result/${work_dir}/${bench}.bc -o result/${work_dir}/${bench}.ll
                    ./bin/llc -stats -debug -target-abi=${abi} ${a} ${t} -relocation-model=${rel} -filetype=asm result/${work_dir}/${bench}.bc -o - &> result/${work_dir}/llc.log
                done
            done
        done
    done
done
