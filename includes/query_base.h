#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include "text_query.h"
#include <set>
#include <iostream>

class Query;  // handler of QueryBase and its inherit classes

class QueryBase{
    friend class Query;
    protected:
        typedef TextQuery::line_no line_no;
        virtual ~QueryBase(){}
    private:
        virtual std::set<line_no> eval(const TextQuery&) const = 0;
        virtual std::ostream& display(std::ostream& os = std::cout) const = 0;
};

#endif