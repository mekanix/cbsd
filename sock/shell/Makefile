CXXFLAGS += -I. -I.. -I/usr/local/include -std=c++11
SRCS != ls -1 *.cpp
LDADD = -pthread -L/usr/local/lib -lreplxx
PROG_CXX = cbsdsh
MK_MAN = no

.include <bsd.prog.mk>
