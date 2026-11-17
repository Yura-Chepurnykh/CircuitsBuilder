#ifndef MODEL_TO_VIEWS_HPP
#define MODEL_TO_VIEWS_HPP

#include <unordered_map>

struct Mapper
{
public:
    size_t model_id = 0;
    size_t view_id = 0;
    std::unordered_map<int, int> modelToView;
    std::unordered_map<int, int> viewToModel;
};

#endif // MODEL_TO_VIEWS_HPP
