#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <set>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

class TextQuery{
    public:
        typedef std::vector<std::string>::size_type line_no; // use line_no as alias
        void read_file(std::ifstream& is){ store_file(is); build_map(); }
        std::string text_line(line_no) const;
        std::set<line_no> run_query(const std::string&) const;
        line_no size() const { return m_text.size(); }
        void show_lines(const std::set<line_no>& lines, std::ostream& os = std::cout) const;

    private:
        std::vector<std::string> m_text; // save the whole text
        std::map<std::string, std::set<line_no> > m_word_map; // map words to the lines
        void store_file(std::ifstream&);       
        void build_map();
};

#endif
