#ifndef WORD_QUERY_H
#define WORD_QUERY_H

#include "query_base.h"


class WordQuery: public QueryBase{
    friend class Query;
    private:
        WordQuery(const std::string& word): m_word(word){}

        virtual std::set<line_no> eval(const TextQuery&) const;
        virtual std::ostream& display(std::ostream& os = std::cout) const;

        std::string m_word;

};

#endif