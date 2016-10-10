/*
 * Copyright (c) 2016 Charles University in Prague, Faculty of Arts,
 *                    Institute of the Czech National Corpus
 * Copyright (c) 2016 Tomas Machalek <tomas.machalek@gmail.com>
 */

#include <string>

/*

How to install:

1) compile the module:

g++ -Wall -fPIC -DPIC -shared -o ucnkdynfn.so ucnkdynfn.cc

2) update your registry file:

ATTRIBUTE my_attr {
    LABEL "My Attribute"
    MULTIVALUE yes
    MULTISEP "|"
    DYNAMIC geteachncharbysep
    DYNLIB  "/a/path/to/ucnkdynfn.so"
    FUNTYPE i
    ARG1 "0"
    FROMATTR ep_tag
    DYNTYPE index
    TRANSQUERY no
}

3) install new attribute for Manatee:

mkdynattr /a/path/to/the/registry/file my_attr

*/


extern "C" {

    /**
     * Separate a string by "|" and return all the pos-th elements
     * from respective items.
     * Example: geteachncharbysep("foo|bar|baz", 2) returns "o|r|z"
     */
    const char * geteachncharbysep(char * s, int pos) {
        std::string ss(s);
        int state = 0;
        std::string out;
        std::string tmp;
        for (std::string::size_type i = 0; i < ss.size(); ++i) {
            if (state == 0) {
                if (ss[i] != '|') {
                    if (i > 0) {
                        out.append(1, '|');
                    }
                    tmp.append(1, ss[i]);
                    state = 1;
                }
            } else if (state == 1) {
                if (ss[i] == '|') {
                    out.append(1, tmp[pos]);
                    tmp.clear();
                    state = 0;

                } else {
                    tmp.append(1, ss[i]);
                }
            }
        }
        if (tmp.length() > 0) {
            out.append(1, tmp[pos]);
        }        
        return out.c_str();
    }

}

