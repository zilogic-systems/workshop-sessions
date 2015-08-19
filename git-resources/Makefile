files = $(wildcard chapter-*.txt)

all: book.tar.gz tangled-working-copy.tar.gz

book.tar.gz: $(files)
	rm -fr book
	mkdir book
	cp $^ book
	cd book; git init
	cd book; git add $^
	cd book; git commit -a -m "Initial book project."
	tar --gzip -c -f book.tar.gz book

tangled-working-copy.tar.gz: book.tar.gz
	cd book; sed -i -e "s/fredom/freedom/" *.txt
	cd book; head -n 2 chapter-2.txt > new-chapter-2.txt
	cd book; cat ../insert-text.txt >> new-chapter-2.txt
	cd book; tail -n +2 chapter-2.txt >> new-chapter-2.txt
	cd book; mv new-chapter-2.txt chapter-2.txt
	tar --gzip -c -f tangled-working-copy.tar.gz book

clean:
	rm -f book.tar.gz
	rm -fr book
	rm -f tangled-working-copy.tar.gz