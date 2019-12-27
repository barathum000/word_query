#ifndef BINARY_QUERY_H
#define BINARY_QUERY_H

#include "query_base.h"


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
    private:
        AndQuery(Query lhs, Query rhs): BinaryQuery(lhs, rhs, "AND"){}
        virtual std::set<line_no> eval(const TextQuery&) const;
};


class OrQuery: public BinaryQuery{
    friend class Query;
    private:
        OrQuery(Query lhs, Query rhs): BinaryQuery(lhs, rhs, "OR"){}
        virtual std::set<line_no> eval(const TextQuery&) const;        
};

#endif