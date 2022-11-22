#!bin/bash
declare -a proc_time
for i in {1..50}
do
	start=$(date +%s%4N);
	./mutex
	end=$(date +%s%4N)
	time="$(($end-$start))";
	proc_time+=("$time")

done
echo "${proc_time[@]}" >> data.txt
