#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include "text_query.h"
#include <set>
#include <iostream>

class Query;  // handler of QueryBase and its inherit classes

Query operator&(const Query&, const Query&);

Query operator|(const Query&, const Query&);

Query operator~(const Query&);


class QueryBase{
    friend class Query;
    protected:
        typedef TextQuery::line_no line_no;
        virtual ~QueryBase(){}
    private:
        virtual std::set<line_no> eval(const TextQuery&) const = 0;
        virtual std::ostream& display(std::ostream& os = std::cout) const = 0;
};


class Query{
    friend Query operator&(const Query&, const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator~(const Query&);

    public:
        Query(const std::string& word);
        Query(const Query& q): m_query(q.m_query), m_ref_count(q.m_ref_count){ ++*m_ref_count; }
        ~Query(){ decr_ref_count(); }
        std::set<QueryBase::line_no> eval(const TextQuery& text) const { return m_query->eval(text); }
        std::ostream& display(std::ostream& os = std::cout) const { return m_query->display(); }

        Query& operator=(const Query&);

    private:
        QueryBase* m_query;
        size_t* m_ref_count;
        Query(QueryBase* q): m_query(q), m_ref_count(new size_t(1)){}
        void decr_ref_count(){ 
            if (m_ref_count-- == 0) {
                delete m_query; 
                delete m_ref_count;
            } 
        }
};


inline std::ostream& operator<<(std::ostream& os, const Query &q){
    return q.display();
}

#endif