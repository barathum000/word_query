#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H

#include "query_base.h"
#include "word_query.h"


class Query{
    friend Query operator&(const Query&, const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator~(const Query&);

    public:
        Query(const std::string& word);
        Query(const Query& q): m_query(q.m_query), m_ref_count(q.m_ref_count){ ++*m_ref_count; }
        ~Query(){ decr_ref_count(); }
        std::set<QueryBase::line_no> eval(const TextQuery& text) const { return m_query->eval(text); }
        std::ostream& display(std::ostream& os = std::cout) const { return m_query->display(os); }

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
    return q.display(os);
}


inline Query::Query(const std::string& word):
    m_query(new WordQuery(word)),
    m_ref_count(new size_t(1))
    {}


class BinaryQuery: public QueryBase{
    friend class Query;

    private:
        virtual std::ostream& display(std::ostream& os = std::cout) const{
            return os << m_lhs << " " << m_operation << " " << m_rhs; 
        }

    protected:
        BinaryQuery(Query lhs, Query rhs, const std::string operation): 
        m_lhs(lhs), 
        m_rhs(rhs),
        m_operation(operation){}
        const Query m_lhs, m_rhs;
        std::string m_operation;
};


class AndQuery: public BinaryQuery{
    friend class Query;
    friend Query operator& (const Query&, const Query&);
    private:
        AndQuery(Query lhs, Query rhs): BinaryQuery(lhs, rhs, "AND"){}
        virtual std::set<line_no> eval(const TextQuery&) const;
};


class OrQuery: public BinaryQuery{
    friend class Query;
    friend Query operator| (const Query&, const Query&);
    private:
        OrQuery(Query lhs, Query rhs): BinaryQuery(lhs, rhs, "OR"){}
        virtual std::set<line_no> eval(const TextQuery&) const;        
};


class NotQuery: public QueryBase{
    friend class Query;
    friend Query operator~(const Query&);
    private:
        NotQuery(const Query& q):m_query(q){}

        virtual std::set<line_no> eval(const TextQuery&) const;
        virtual std::ostream& display(std::ostream& os = std::cout) const;

        const Query m_query;
};


inline Query operator&(const Query& lhs, const Query& rhs){
    return new AndQuery(lhs, rhs); // Query q = AndQuery(lhs, rhs)
}


inline Query operator|(const Query& lhs, const Query& rhs){
    return new OrQuery(lhs, rhs);
}

inline Query operator~(const Query& q){
    return new NotQuery(q);
}
#endif