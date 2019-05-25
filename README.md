# Performance difference between data accesss with/without boolean flag embeded

This test is to collect and compare time consumption of operation on an array of<br>
employee data set: if employee ever serviced in army (indicated by some flag),<br>
increase his/her salary. The result is based on [ctimeit](https://github.com/stephen-wang/ctimeit) and, the result shows<br>
that moving boolean flag out of data stucuture can improve performance under<br>
some conditions:<br>
    1) the number of flags equal to true is sparse compring to toal number, I<br>
       make it as 1/1000 in test;<br>
    2) the total number should be not too small (CPU cache can hold both flag<br>
       array and data array) or too big (flag array fills up CPU cache)

<Strong>Results</Strong><br>
wangwenzhi@wangwenzhi-devbox-1:/local/perf_diff_of_flag_store$ nums="3000 30000 300000 600000 900000 1200000 2000000 ";for num in $nums; do ./test_flag_storing $num 0;./test_flag_storing $num 1; done<br>
<br>
increase_salary_with_flag(EmployeeF*, 3000):<br>
avg: 24µs745ns (24745 ns)<br>
<br>
increase_salary_with_separate_flag(EmployeeNF*, 3000):<br>
avg: 26µs323ns (26323 ns)<br>
<br>
increase_salary_with_flag(EmployeeF*, 30000):<br>
avg: 370µs553ns (370553 ns)<br>
<br>
increase_salary_with_separate_flag(EmployeeNF*, 30000): <br>
avg: 381µs871ns (381871 ns) <br>
<br>
increase_salary_with_flag(EmployeeF*, 300000): <br>
avg: 4ms537µs732ns (4537732 ns) <br>
<br>
increase_salary_with_separate_flag(EmployeeNF*, 300000):
avg: 1ms102µs844ns (1102844 ns) <br>
<br>
increase_salary_with_flag(EmployeeF*, 600000):
avg: 4ms647µs922ns (4647922 ns) <br>
<br>
increase_salary_with_separate_flag(EmployeeNF*, 600000):
avg: 2ms171µs333ns (2171333 ns) <br>
<br>
increase_salary_with_flag(EmployeeF*, 900000): <br>
avg: 8ms791µs222ns (8791222 ns) <br>
<br>
increase_salary_with_separate_flag(EmployeeNF*, 900000):<br>
avg: 3ms676µs788ns (3676788 ns) <br>
<br>
increase_salary_with_flag(EmployeeF*, 1200000): <br>
avg: 8ms853µs262ns (8853262 ns) <br>
<br>
increase_salary_with_separate_flag(EmployeeNF*, 1200000):<br>
avg: 6ms482µs713ns (6482713 ns)<br>
<br>
increase_salary_with_flag(EmployeeF*, 2000000): <br>
avg: 21ms592µs709ns (21592709 ns) <br> 
<br>
increase_salary_with_separate_flag(EmployeeNF*, 2000000):<br>
avg: 7ms791µs388ns (7791388 ns)<br>
<br>
