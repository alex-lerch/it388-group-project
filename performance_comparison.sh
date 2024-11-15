# recompile first
make

# run OMP merge sort sequentially on ints and output performance to 'performance_outfile.txt' file
echo "OMP sequential with problem size 10" > performance_outfile.txt
./merge_sort OMP int d10.rand 1 >> performance_outfile.txt
echo "" >> performance_outfile.txt


echo "OMP sequential with problem size 1000" >> performance_outfile.txt
./merge_sort OMP int d1000.rand 1 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP sequential with problem size 10,000" >> performance_outfile.txt
./merge_sort OMP int d10000.rand 1 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP sequential with problem size 100,000" >> performance_outfile.txt
./merge_sort OMP int d100000.rand 1 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP sequential with problem size 2,000,000" >> performance_outfile.txt
./merge_sort OMP int d2000000.rand 1 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP sequential with problem size 4,000,000" >> performance_outfile.txt
./merge_sort OMP int d4000000.rand 1 >> performance_outfile.txt
echo "" >> performance_outfile.txt
echo "" >> performance_outfile.txt
echo "===================================================================================" >> performance_outfile.txt
echo "" >> performance_outfile.txt
echo "" >> performance_outfile.txt


# run OMP merge sort with 3 threads on ints and output performance to 'performance_outfile.txt' file
echo "OMP nThreads = 3 with problem size 10" >> performance_outfile.txt
./merge_sort OMP int d10.rand 3 >> performance_outfile.txt
echo "" >> performance_outfile.txt


echo "OMP nthreads = 3 with problem size 1000" >> performance_outfile.txt
./merge_sort OMP int d1000.rand 3 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 3 with problem size 10,000" >> performance_outfile.txt
./merge_sort OMP int d10000.rand 3 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 3 with problem size 100,000" >> performance_outfile.txt
./merge_sort OMP int d100000.rand 3 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 3 with problem size 2,000,000" >> performance_outfile.txt
./merge_sort OMP int d2000000.rand 3 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 3 with problem size 4,000,000" >> performance_outfile.txt
./merge_sort OMP int d4000000.rand 3 >> performance_outfile.txt
echo "" >> performance_outfile.txt
echo "" >> performance_outfile.txt
echo "======================================================================================" >> performance_outfile.txt
echo "" >> performance_outfile.txt
echo "" >> performance_outfile.txt


# run OMP merge sort with 10 threads on ints and output performance to 'performance_outfile.txt' file
echo "OMP nThreads = 10 with problem size 10" >> performance_outfile.txt
./merge_sort OMP int d10.rand 10 >> performance_outfile.txt.txt
echo "" >> performance_outfile.txt


echo "OMP nthreads = 10 with problem size 1000" >> performance_outfile.txt
./merge_sort OMP int d1000.rand 10 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 10 with problem size 10,000" >> performance_outfile.txt
./merge_sort OMP int d10000.rand 10 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 10 with problem size 100,000" >> performance_outfile.txt
./merge_sort OMP int d100000.rand 10 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 10 with problem size 2,000,000" >> performance_outfile.txt
./merge_sort OMP int d2000000.rand 10 >> performance_outfile.txt
echo "" >> performance_outfile.txt

echo "OMP nthreads = 10 with problem size 4,000,000" >> performance_outfile.txt
./merge_sort OMP int d4000000.rand 10 >> performance_outfile.txt
echo "" >> performance_outfile.txt