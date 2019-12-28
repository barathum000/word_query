#include <algorithm>
#include "query_handler.h"

std::set<AndQuery::line_no> AndQuery::eval(const TextQuery& t) const{
    std::set<line_no> ret_lines;
    std::set<line_no> l_ret = m_lhs.eval(t);
    std::set<line_no> r_ret = m_rhs.eval(t);

    for (std::set<line_no>::const_iterator iter = l_ret.begin(); iter != l_ret.end(); ++iter){
        if (r_ret.find(*iter) != r_ret.end())
            ret_lines.insert(*iter);
    }  
    
    return ret_lines;
}


std::set<OrQuery::line_no> OrQuery::eval(const TextQuery& t) const{
    std::set<line_no> l_ret = m_lhs.eval(t);
    std::set<line_no> r_ret = m_lhs.eval(t);

    l_ret.insert(r_ret.begin(), r_ret.end());
    return l_ret;
}