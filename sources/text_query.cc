#include "text_query.h"
#include <sstream>


// private API
void TextQuery::store_file(std::ifstream& is){
    std::string line;
    while(getline(is, line)){
        m_text.push_back(line);
    }
}


void TextQuery::build_map(){
    // extract every line
    for (line_no idx = 0; idx < m_text.size(); ++idx){
        std::istringstream line(m_text[idx]);
        std::string word;
        while(line >> word){
            m_word_map[word].insert(idx);
        }
    }
}


// public API
std::string TextQuery::text_line(line_no line) const{
    if (line < m_text.size())
        return m_text[line];
    else
    {
        throw std::out_of_range("line number out of range");
    }
    

}


std::set<TextQuery::line_no> TextQuery::run_query(const std::string& word) const{
    std::map<std::string, std::set<line_no> >::const_iterator iter = m_word_map.find(word);
    if (iter != m_word_map.end())
        return iter->second;
    
    return std::set<line_no>(); // empty set
}