sh -c "echo -n \"FLTKFLAGS = \" && fltk-config --cflags && echo && echo -n \"FLTKOPTIM = \" && fltk-config --optim && echo && echo -n \"FLTKOPTIM = \" && fltk-config --use-images --ldflags && echo && cat MakefileTemplate" > Makefile  
make
