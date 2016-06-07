path_prefix=/usr/local/lib
dynlib=ucnkdynfn.so

build: ucnkdynfn.cc
	g++ -Wall -fPIC -DPIC -shared -o $(dynlib) ucnkdynfn.cc

.PHONY: install
install: $(dynlib)
	mkdir -p $(path_prefix)/manatee/dynattr
	install -m 0755 $(dynlib) $(path_prefix)/manatee/dynattr

.PHONY: uninstall
uninstall:
	rm -f $(path_prefix)/manatee/dynattr/$(dynlib)
