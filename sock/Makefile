all:
	@${MAKE} ${MAKEFLAGS} -C daemon
	@${MAKE} ${MAKEFLAGS} -C shell

clean:
	@${MAKE} ${MAKEFLAGS} -C daemon clean
	@${MAKE} ${MAKEFLAGS} -C shell clean

cleandir:
	@${MAKE} ${MAKEFLAGS} -C daemon cleandir
	@${MAKE} ${MAKEFLAGS} -C shell cleandir

prog: prog.cpp message.h
	c++ -std=c++11 -o prog prog.cpp

cleanprog:
	rm -rf prog
