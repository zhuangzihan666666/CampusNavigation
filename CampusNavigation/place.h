#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include <unordered_map>

struct Place {
    int id;
    std::string name;
};

class PlaceManager {

private:
    std::vector<Place> places;
    std::unordered_map<int, int> idIndex;

public:

    std::string filename;
    
    // 
    PlaceManager(const std::string& filename = "");

    // 从文件加载地点数据
    bool loadFromFile();

    // 保存到文件
    bool saveToFile() const;

    // 添加地点
    bool addPlace(int id, const std::string& name);

    // 删除地点
    bool deletePlace(int id);

    // 修改地点
    bool updatePlace(int id,const std::string& newName);
    
    // 按 id 查找（返回指针，便于修改）
    Place* findById(int id);

    // 按名称查找（支持模糊）
    std::vector<Place*> findByName(const std::string& keyword);

    // 打印所有地点
    void printAll() const;
    
    // 地点数量
    int size() const;
    
    // 直接访问线性表（给后续模块用）
    const std::vector<Place>& getAll() const;

    // 确定选择地点
    int decidePlace(const std::string &keyword);
};

#endif