#!/bin/bash
cat Makefile | grep CFLAGS
cat Makefile | grep CXXFLAGS
sed -e "s/-O2//p" -i Makefile  | grep CFLAGS
cat Makefile | grep CXXFLAGS
cat Makefile  | grep -- -O

