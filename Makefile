OBJS=utils.o game.o hero.o list.o main.o comm/a.o comm/_ae.o comm/bar.o comm/bb.o comm/bmar.o comm/b.o comm/bsale.o comm/_clsc.o comm/cstat.o comm/d.o comm/e.o comm/girl.o comm/help.o comm/h.o comm/hp.o comm/inv.o comm/i.o comm/jmp.o comm/kl.o comm/k.o comm/kos.o comm/loa.o comm/mar.o comm/meet.o comm/met.o comm/mh.o comm/ob.o comm/p.o comm/pon.o comm/pr.o comm/raid.o comm/rep.o comm/r.o comm/rsl.o comm/sav.o comm/sl.o comm/s.o comm/so.o comm/ssl.o comm/sstay.o comm/stat.o comm/stdi.o comm/str.o comm/_sv.o comm/sv.o comm/svo.o comm/t.o comm/tok.o comm/trn.o comm/tus.o comm/up.o comm/_vis.o comm/v.o comm/vpl.o comm/wes.o comm/_w.o comm/w.o comm/x.o pltl/pltl0.o pltl/pltl1.o pltl/pltl2.o
CXXFLAGS=-Wall -ggdb

all: comm pltl $(OBJS)
	g++ -o gop $(OBJS) -lncursesw

comm:
	make -C comm

pltl:
	make -C pltl

clean:
	rm -f *.o gop &>/dev/null &
	make -C comm clean
	make -C pltl clean

lclean:
	rm -f *.o gop &>/dev/null &

.PHONY: all clean comm pltl lclean