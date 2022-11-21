#!bin/bash
declare -a proc_time
for i in {1..50}
do
	start=$(date +%s%4N);
	./semaphore #| top -b -n 3 | grep mutex |tail -n 1 | awk '{print $1 " "$6}' 
	#ram=$(./mutex ; pmap $(ps au | grep -m1 mutex) | tail -n 1 | awk '{print $2}')
	end=$(date +%s%4N)
	#ram=$(sudo pmap "$PID" | tail -n 1 | awk '{print $2}')
	#echo "$ram"
	time="$(($end-$start))";
	proc_time+=("$time")

done
echo "${proc_time[@]}" >> data.txt
