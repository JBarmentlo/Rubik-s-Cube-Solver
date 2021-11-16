export WORKDIR=$PWD
gnome-terminal --working-directory=$WORKDIR -- python3 src/visu_server.py
docker build -t rubiks_dock .
docker run -it --rm --network=host -v $WORKDIR:/roobik rubiks_dock 
