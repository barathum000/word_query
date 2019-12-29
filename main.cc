#include "query_handler.h"
#include "text_query.h"
#include <sstream>


std::vector<std::string> handle_query_string(std::string query_string){
    std::vector<std::string> ret_vector;
    std::istringstream query_stream(query_string);
    std::string element;
    while(query_stream >> element){
        if (element != "(" || element != ")")
            ret_vector.push_back(element);
    }
    return ret_vector;
}


Query get_binary_query(const Query& lhs, const Query& rhs, std::string op){
    if (op == "|")
        return lhs | rhs;
    else if (op == "&")
        return lhs & rhs;
    else
        throw std::runtime_error("!!!unrecongized operation"); 
}


Query get_query_obj(const std::vector<std::string>& query_vector){
    Query q;
    std::size_t beg_idx;

    if (query_vector[0] != "~"){
        q = Query(query_vector[0]);
        beg_idx = 1;
    }
    else{
        q = ~Query(query_vector[1]);
        beg_idx = 2;
    }

    for (std::size_t idx = beg_idx; idx < query_vector.size(); ++idx){
        std::string op = query_vector[idx];
        if(op == "|" || op == "&"){
            if (query_vector[idx+1] != "~"){
                q = get_binary_query(q, Query(query_vector[idx+1]), op);
                idx += 2;
            }
            else{
                q = get_binary_query(q, ~Query(query_vector[idx+1]), op);
                idx += 3;
            }
        }
        else
            continue; 
    }
    return q;
}


int main(int argc, char **argv){
    if (argc < 2){
        std::cout << "Usage: ./${bin} ${file_path}\n";
        exit(1);
    }
    // handle input file
    TextQuery text_query;
    std::string input_file = argv[1];
    std::ifstream fp(input_file);
    text_query.read_file(fp);
    // read query string from user
    std::cout << "Input query condition(bracket is not allowed currently): ";
    std::string query_string;
    getline(std::cin, query_string);
    // split query string and generate query object
    std::vector<std::string> query_vec = handle_query_string(query_string);
    Query q = get_query_obj(query_vec);
    // execute query
    std::set<TextQuery::line_no> lines = q.eval(text_query);
    text_query.show_lines(lines);
    return 0;
}