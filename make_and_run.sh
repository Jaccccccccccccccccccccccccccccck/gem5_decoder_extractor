mkdir -p build
cd build
cmake ..
clear
make -j
echo "start run."
# ./main 17fffe0a  go error
./main 885f7c40