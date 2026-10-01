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

test:
	python3 -m venv venv
	venv/bin/pip3 install online-judge-verify-helper setuptools==80
	venv/bin/oj-verify run

.PHONY: build clean
