#include "word_query.h"


std::set<WordQuery::line_no> WordQuery::eval(const TextQuery& t) const{
    return t.run_query(m_word);
}


std::ostream& WordQuery::display(std::ostream& os) const{
    return os << m_word;
}