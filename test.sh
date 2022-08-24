#!/bin/bash

python3 test/case/miniob_test.py \
        --test-case-dir=test/case/test  \
        --test-case-scores=test/case/case-scores.json \
        --test-result-dir=test/case/result \
        --test-result-tmp-dir=test/case/result_tmp \
        --use-unix-socket \
        --git-repo=https://github.com/maochongxin/miniob.git \
        --git-branch=mcx-dev \
        --code-type=git \
        --target-dir=./miniob \
        --log=stdout \
        --compile-make-args=-j4