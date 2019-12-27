#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <set>
#include <vector>
#include <map>
#include <string>
#include <fstream>


class TextQuery{
    public:
        typedef std::vector<std::string>::size_type line_no; // use line_no as alias
        void read_file(std::ifstream& is){ store_file(is); build_map(); }
        std::string text_line(line_no) const;
        std::set<line_no> run_query(std::string&) const;

    private:
        std::vector<std::string> m_text; // save the whole text
        std::map<std::string, std::set<line_no> > m_word_map; // map words to the lines
        void store_file(std::ifstream&);       
        void build_map();
};

#endif