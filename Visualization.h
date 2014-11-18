#ifndef ML_VISUALIZATION_H
#define ML_VISUALIZATION_H

#include"Line.h"
#include"Point.h"

#include<vector>
#include<string>
#include<fstream>

namespace ML
{
  class Visual
  {
  public:
    static void write_points_to_file(const std::vector<Point>& points, const std::string& fileName);
    static std::string to_string(const Line& l);
    static void dump(const std::vector<Point>& points1, const std::string& name1,
		     const std::vector<Point>& points2, const std::string& name2,
		     const ML::Line& l1,
		     const ML::Line& l2, const std::string& fileName );

    static void dump(int item, const std::vector<Point>& goods,
		     const std::vector<Point>& bads,
		     const Point& selected,
		     const Line& g,
		     const Line& h, bool drawSelected = false);
  };
};

#endif // ML_VISUALIZATION_H
