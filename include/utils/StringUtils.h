#ifndef UTILS_STRINGUTILS_H
#define UTILS_STRINGUTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>

namespace utils
{

    class StringUtils
    {
    public:
        // Split string by a single character delimiter
        static std::vector<std::string> split(const std::string &str, char delimiter)
        {
            std::vector<std::string> tokens;
            std::stringstream ss(str);
            std::string item;
            while (std::getline(ss, item, delimiter))
            {
                tokens.push_back(item);
            }
            return tokens;
        }

        // Trim from start (in place)
        static void ltrim(std::string &s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                            [](unsigned char ch)
                                            { return !std::isspace(ch); }));
        }

        // Trim from end (in place)
        static void rtrim(std::string &s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(),
                                 [](unsigned char ch)
                                 { return !std::isspace(ch); })
                        .base(),
                    s.end());
        }

        // Trim from both ends (in place)
        static void trim(std::string &s)
        {
            ltrim(s);
            rtrim(s);
        }

        // Return a trimmed copy
        static std::string trimmed(const std::string &s)
        {
            std::string copy = s;
            trim(copy);
            return copy;
        }

        // Convert string to lower case (returns copy)
        static std::string toLower(const std::string &s)
        {
            std::string result = s;
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });
            return result;
        }

        // Convert string to upper case (returns copy)
        static std::string toUpper(const std::string &s)
        {
            std::string result = s;
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char c)
                           { return std::toupper(c); });
            return result;
        }

        // Replace all occurrences of 'from' with 'to' in string (returns copy)
        static std::string replaceAll(const std::string &str, const std::string &from, const std::string &to)
        {
            if (from.empty())
                return str;
            std::string result = str;
            size_t start_pos = 0;
            while ((start_pos = result.find(from, start_pos)) != std::string::npos)
            {
                result.replace(start_pos, from.length(), to);
                start_pos += to.length();
            }
            return result;
        }

        // Check if string starts with prefix
        static bool startsWith(const std::string &str, const std::string &prefix)
        {
            return str.size() >= prefix.size() &&
                   std::equal(prefix.begin(), prefix.end(), str.begin());
        }

        // Check if string ends with suffix
        static bool endsWith(const std::string &str, const std::string &suffix)
        {
            return str.size() >= suffix.size() &&
                   std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
        }

        // Join vector of strings with a delimiter
        static std::string join(const std::vector<std::string> &tokens, const std::string &delimiter)
        {
            if (tokens.empty())
                return "";
            std::ostringstream os;
            auto it = tokens.begin();
            os << *it++;
            for (; it != tokens.end(); ++it)
            {
                os << delimiter << *it;
            }
            return os.str();
        }
    };

} // namespace utils

#endif // UTILS_STRINGUTILS_H
