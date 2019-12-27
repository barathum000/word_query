#include "query_base.h"
#include "word_query.h"


Query::Query(const std::string& word):
    m_query(new WordQuery(word)),
    m_ref_count(new size_t(1))
    {}