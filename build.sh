source .envrc
python3.8 download_tables.py
rm -rf build/*
cd build
cmake ..
cmake --build . 
