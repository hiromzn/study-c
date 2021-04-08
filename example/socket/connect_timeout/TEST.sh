echo "##### TEST : BAD ip address"
echo "----- TEST blocking with timeout"
./main 10.21.40.199 22 1
echo "----- TEST NON blocking with timeout"
./main 10.21.40.199 22 0
echo ""
echo "##### TEST : OK ip address"
echo "----- TEST blocking with timeout"
./main 10.21.41.69 22 1
echo "----- TEST NON blocking with timeout"
./main 10.21.41.69 22 0
