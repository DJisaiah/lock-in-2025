char char_of_code (unsigned charcode) {
    return (char)charcode;
    // couldve also done return ('%c', charcode)
    // or used the toascii function from ctype.h
    // can also just return charcode as C implicitly truncates
}
