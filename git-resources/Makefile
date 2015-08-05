book.tar.gz:
	mkdir book
	cp chapter-*.txt book
	cd book; git init
	cd book; git add chapter-*.txt
	cd book; git commit -a -m "Initial book project."
	tar --gzip -c -f book.tar.gz book

clean:
	rm -f book.tar.gz
	rm -fr book
