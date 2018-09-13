CXXFLAGS = -O3 -Wall -std=c++11

all: Johansson_Anders_FYS3150_Oblig2.pdf enpartikkel.x

%.pdf: %.tex plot1.tex plot2.tex eigentest.txt kilder.bib
	latexmk -f -pdf $<

enpartikkel.x: enpartikkel.o funksjoner.o schrodinger.o jacobi.o Potensial.o
	$(CXX) $(CXXFLAGS) -o $@ $^
topartikler.x: topartikler.o PotensialMedInteraksjon.o PotensialUtenInteraksjon.o Potensial.o schrodinger.o jacobi.o funksjoner.o
	$(CXX) $(CXXFLAGS) -o $@ $^
test.x: test.o funksjoner.o jacobi.o
	$(CXX) $(CXXFLAGS) -o $@ $^

eigentest.txt: test.x
	./$< > eigentest.txt
omegamed5.00.dat: topartikler.x
	./$<
nlik250.dat: enpartikkel.x
	./$<

plot1.tex: plot.gpi nlik250.dat
	gnuplot $<
plot2.tex: plotto.gpi omegamed5.00.dat
	gnuplot $<
clean:
	latexmk -c
	rm -rf *.bbl *.o *.x
	rm -rf _minted-${NAVN}
	rm -rf *.dat *.eps *-converted-to.pdf plot*.tex *.txt *.run.xml
