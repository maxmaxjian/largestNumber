#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

class solution {
  public:
    std::string largestNumber(const std::vector<int> & nums) {
        std::vector<std::vector<int>> paths = getPaths(nums, std::vector<int>());
        std::vector<std::string> numStrs;
        std::transform(paths.begin(), paths.end(), std::inserter(numStrs, numStrs.begin()), [](const std::vector<int> & vec){
            return std::accumulate(vec.begin(), vec.end(), std::string(),
                                   [](const std::string & s, int i){
                                       return s+std::to_string(i);
                                   });
        });
        
        std::cout << "All candidates are:\n";
        std::copy(numStrs.begin(), numStrs.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
        
        return *std::max_element(numStrs.begin(), numStrs.end());
    }

  private:
    std::vector<std::vector<int>> getPaths(const std::vector<int> & nums, const std::vector<int> & curr) {
        std::vector<std::vector<int>> result;
        if (curr.size() == nums.size())
            result.push_back(curr);
        else {
            std::vector<int> next = getNext(nums, curr);
            for (auto & nx : next) {
                auto cpy = curr;
                cpy.push_back(nx);
                auto temp = getPaths(nums, cpy);
                std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
            }
        }
        return result;
    }

    std::vector<int> getNext(const std::vector<int> & nums, const std::vector<int> & curr) {
        std::vector<int> next, cands;
        std::copy_if(nums.begin(), nums.end(), std::inserter(cands, cands.begin()), [&](int i){
            return find(curr.begin(), curr.end(), i) == curr.end();
        });

        auto it = std::max_element(cands.begin(), cands.end(),
                                   [](int i, int j){
                                       while (i/10 != 0)
                                           i /= 10;
                                       while (j/10 != 0)
                                           j /= 10;
                                       return i < j;
                                   });
        std::copy_if(cands.begin(), cands.end(), std::inserter(next, next.begin()), [&](int i){
            while (i/10 != 0)
                i /= 10;
            int found = *it;
            while (found/10 != 0)
                found /= 10;
            return i == found;
        });
        return next;
    }
};

int main() {
    std::vector<int> nums{3, 30, 34, 5, 9};

    solution soln;
    std::string largest = soln.largestNumber(nums);
    std::cout << "The largest number is:\n"
              << largest << std::endl;
}
