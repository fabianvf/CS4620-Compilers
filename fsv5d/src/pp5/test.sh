#!/usr/bin/env bash 
#
# diff.sh
# by: Fabian
#
# this script recursively finds all files in the specified folder, and 
# compares the output of the reference compiler to your own compiler.
# If there are differences, it writes them to a file under the name of
# [input_filename].diff

if [ -z $1 ];
then
echo "Needs an argument, dumbass"
    exit 2
fi

# Sets up file structure
if [ ! -d diff_results ]; then
	mkdir diff_results
else
	rm -rf diff_results/*
fi
if [ ! -d diff_results/asm ]; then
	mkdir diff_results/asm
else
	rm -rf diff_results/asm/*
fi
if [ ! -d diff_results/out ]; then
	mkdir diff_results/out
else
	rm -rf diff_results/asm/*
fi
if [ ! -d decaf_samples ]; then
	mkdir decaf_samples
	cp samples/*.decaf decaf_samples/
fi
pass_counter=0
fail_counter=0
for entry in "decaf_samples"/*
do
	filename=${entry%%.*}
	filename=${filename##*/}
	echo "$entry"

	# Generates assembly 
	asm1=`./dcc < $entry 2> /dev/null`
	asm2=`pp5_solution/dcc < $entry 2> /dev/null`
	printf '%s\n' "$asm1" > "diff_results/asm/$filename.asm"
	printf '%s\n' "$asm2" > "diff_results/asm/${filename}_reference.asm"

	(cat "defs.asm" >>"diff_results/asm/$filename.asm")
	(cat "defs.asm" >>"diff_results/asm/${filename}_reference.asm")


	diff "diff_results/asm/$filename.asm" "diff_results/asm/${filename}_reference.asm" > "diff_results/asm/${filename}_asm.diff"
	# Generates actual output 
	out2=`spim -file "diff_results/asm/${filename}_reference.asm" 2> /dev/null`
#	out2=$(cat samples/$filename.out)
	out1=`spim -file "diff_results/asm/$filename.asm" 2> /dev/null`
#	printf '%s\n' "$out1" > "diff_results/out/$filename.out"
#	printf '%s\n' "$out2" > "diff_results/out/${filename}_reference.out"

	# Checks output of executed assembly against reference assembly
	output=`diff -u  <(echo "$out1") <(echo "$out2")`
	if [ -n "$output" ]; then
		printf '%s\n' "$output" > "diff_results/$filename.diff"
		echo "$filename did not pass"
		fail_counter=`expr $fail_counter + 1`
	else
		echo "$filename passed!"
		pass_counter=`expr $pass_counter + 1`
	fi
done

# Useful information spit out at the end
echo -e "$pass_counter tests passed, $fail_counter tests failed"
test_counter=`expr $pass_counter + $fail_counter`
percent=$(echo "$pass_counter/$test_counter *100" | bc -l)
echo ${percent:0:3}"% pass rate"
