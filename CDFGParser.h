#ifndef CDFG_PARSER_H
#define CDFG_PARSER_H

static const char* TokenArray[] = {
    "[VAR]"
  , "[OP]"
  , "[CONST]"
  , "[BRANCH]"
  , "[MERGE]"
};

static const int szTokenArray = sizeof(&TokenArray)/sizeof(&TokenArray[0]);


class CDFGParser {
public:
    CDFGParser(std::string FilenameOfCDFG);

private:
    Node* parse(ifstream & in);
    Node* parseVar(ifstream & in);
    Node* parserOp(ifstream & in);
};


#endif // CDFG_PARSER_H
