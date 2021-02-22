#pragma once

#include <vector>
#include <string>
#include <algorithm>

class InputParser{
   private:
      std::vector<std::string> tokens;

      InputParser(){}

   public:
      InputParser (const InputParser&) = delete;
      InputParser (InputParser&&) = delete;
      InputParser& operator=(const InputParser&) = delete;
      InputParser& operator=(InputParser&&) = delete;


      void add_values(int &argc, char **argv) {
         for(int i = 1; i < argc; ++i) {
            this->tokens.push_back(std::string(argv[i]));
         }
      }

      static InputParser& getInstance() {
         static InputParser instance;
         return instance;
      }

      const std::string& getCmdOption(const std::string &option) const{
         std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
      }

      bool cmdOptionExists(const std::string &option) const{
         return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
      }
};
