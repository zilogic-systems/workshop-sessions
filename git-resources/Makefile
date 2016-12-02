TOPDIR = ../
files = $(wildcard chapter-*.txt)
resources = book.tar.gz book.git.tar.gz tangled-working-copy.tar.gz

all: $(resources)

install:
	mkdir -p $(TOPDIR)/build/git-resources
	cp $(resources) $(TOPDIR)/build/git-resources

install-extra:

book-git: $(files)
	rm -fr book
	mkdir book
	cp $^ book
	cd book; git init
	cd book; git config user.name "User"
	cd book; git config user.email user@example.com
	cd book; git config alias.vb "log --all --decorate --graph --oneline"
	cd book; git add $^
	cd book; git commit -a -m "Initial book project."

book.git.tar.gz: book-git
	rm -fr book.git
	git clone --bare book
	tar --gzip -c -f book.git.tar.gz book.git

book.tar.gz: book-git
	tar --gzip -c -f book.tar.gz book

tangled-working-copy.tar.gz: book-git
	cd book; sed -i -e "s/fredom/freedom/" *.txt
	cd book; head -n 2 chapter-2.txt > new-chapter-2.txt
	cd book; cat ../insert-text.txt >> new-chapter-2.txt
	cd book; tail -n +2 chapter-2.txt >> new-chapter-2.txt
	cd book; mv new-chapter-2.txt chapter-2.txt
	tar --gzip -c -f tangled-working-copy.tar.gz book

clean:
	rm -f book.tar.gz
	rm -f book.git.tar.gz
	rm -f tangled-working-copy.tar.gz
	rm -fr book
	rm -fr book.git
