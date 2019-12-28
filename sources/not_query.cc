#include "query_handler.h"


std::set<NotQuery::line_no> NotQuery::eval(const TextQuery& t) const{
    std::set<line_no> org_lines = m_query.eval(t);
    std::set<line_no> ret_lines; // exclude lines in org_lines
    line_no size = t.size();

    for(line_no line = 0; line < size; ++line){
        if (org_lines.find(line) == org_lines.end())
            ret_lines.insert(line);
    }
    return ret_lines;
}


std::ostream& NotQuery::display(std::ostream& os) const {
    return  os << "NOT" << m_query;
}