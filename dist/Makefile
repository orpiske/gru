VERSION=0.2.0

check:
	rpmlint -i dist/gru.spec

rpm-prep:
	mkdir -p ${HOME}/rpmbuild/SOURCES/
	tar --transform="s/\./gru-${VERSION}/" -cf ${HOME}/rpmbuild/SOURCES/gru-${VERSION}.tar.gz --exclude=./build --exclude=.git --exclude=*.bz ./ --gzip

rpm: rpm-prep
	rpmbuild -ba dist/gru.spec
