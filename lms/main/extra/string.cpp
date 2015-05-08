#include <lms/extra/string.h>
#include <string>
#include <vector>
#include <iostream>

namespace lms {
namespace extra {

std::string trim(const std::string& str, const std::string& delims) {
    std::string result(str);
    result.erase(0, result.find_first_not_of(delims));
    result.erase(result.find_last_not_of(delims) + 1);
    return result;
}
std::vector<std::string> split(char *string, int strLength, const char splitter){
    std::vector<std::string> result;
    std::cout <<"CALLED"<<std::endl;
    char *resultBuff = string;
    int oldFound = 0;
    for(int i = 0; i < strLength; i++){
        std::cout<<"char: "<< resultBuff[i] <<std::endl;
        if(resultBuff[i] == splitter){
            //found new part
            std::string name(&resultBuff[oldFound],i-oldFound);
            oldFound = i+1;
            result.push_back(name);
            std::cout <<"part found: " << name << std::endl;
        }
    }
    //add last element if the string doesn't end with the splitter
    if(oldFound < strLength){
        std::string name(&resultBuff[oldFound],strLength-oldFound);
        result.push_back(name);
        std::cout << "found last: " << name <<std::endl;

    }
    return result;
}

std::string dirname(std::string path) {
    // delete trailing slashes
    size_t lastNotSlash = path.find_last_not_of('/');

    if(lastNotSlash != std::string::npos) {
        path.erase(lastNotSlash + 1);
    } else {
        // path was a sequence of only slashs
        return "/";
    }

    // delete file name
    size_t slash = path.find_last_of('/');

    if(slash == std::string::npos) {
        // there was only a basename and no dirname
        return ".";
    } else {
        path.erase(slash);

        if(path.empty()) {
            return "/";
        } else {
            return path;
        }
    }
}

bool isAbsolute(const std::string &path) {
    return !path.empty() && path[0] == '/';
}

} // namespace extra
} // namespace lms
