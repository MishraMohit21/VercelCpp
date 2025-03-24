npm i

mkdir -p build
cd build
cmake ..
make

cd ..

./build/VercelDeployService