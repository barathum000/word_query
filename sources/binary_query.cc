#include "binary_query.h"
#include <algorithm>

std::set<AndQuery::line_no> AndQuery::eval(const TextQuery& t) const{
    std::set<line_no> ret_lines;
    std::set<line_no> l_ret = m_lhs.eval(t);
    std::set<line_no> r_ret = m_rhs.eval(t);   
    
    std::set_intersection(l_ret.begin(), l_ret.end(), r_ret.begin(), r_ret.end(), ret_lines.begin(), std::inserter(ret_lines, ret_lines.begin()));
    return ret_lines;
}


std::set<OrQuery::line_no> OrQuery::eval(const TextQuery& t) const{
    std::set<line_no> l_ret = m_lhs.eval(t);
    std::set<line_no> r_ret = m_lhs.eval(t);

    l_ret.insert(r_ret.begin(), r_ret.end());
    return l_ret;
}