DOCUMENT := Thesis
LATEXMK := latexmk -pdf -bibtex

.PHONY: document sort-acronyms clean

default: document

sort-acronyms:
	sort Acronyms.tex -o Acronyms.tex

document:
	@echo "Build document"
	$(LATEXMK) $(DOCUMENT)

clean:
	@ echo "Clean up"
	$(LATEXMK) -C
	rm -f pdfa.xmpi
	rm -f $(DOCUMENT)-blx.bib
	rm -f gfxcompiled/*
