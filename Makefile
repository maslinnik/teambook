LATEXCMD = pdflatex -shell-escape -output-directory build/
export TEXINPUTS=.:content/tex/:
export max_print_line = 1048576

build:
	mkdir -p build
	$(LATEXCMD) content/teambook.tex </dev/null
	cp build/teambook.pdf teambook.pdf
	rm -f header.tmp

clean:
	rm -rf build header.tmp

.PHONY: build clean
