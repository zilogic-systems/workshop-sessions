files = $(wildcard chapter-*.txt)

book.tar.gz: $(files)
	rm -fr book
	mkdir book
	cp $^ book
	cd book; git init
	cd book; git add $^
	cd book; git commit -a -m "Initial book project."
	tar --gzip -c -f book.tar.gz book

clean:
	rm -f book.tar.gz
	rm -fr book
