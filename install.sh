# install cargo
# curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source ~/.bashrc
# build zenohc
echo "build zenohc"
mkdir build_zenohc
cd build_zenohc
cmake ../libs/zenoh-c
cmake --build .
sudo cmake --build . --target install

# build zenohcpp
echo "build zenohcpp"
cd ..
mkdir build_zenohcpp
cd build_zenohcpp
cmake ../libs/zenoh-cpp
sudo cmake --install .
