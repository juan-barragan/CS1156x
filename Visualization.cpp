#include "Visualization.h"
#include "PNGScreen.h"
#include<sstream>

void ML::Visual::write_points_to_file(const std::vector<Point>& points, const std::string& fileName)
{
  std::ofstream file_stream;
  file_stream.open(fileName);
  for(auto p:points)
    file_stream<<p.x<<" "<<p.y<<"\n";
  file_stream.close();
}

std::string ML::Visual::to_string(const ML::Line& l)
{
  std::ostringstream s_stream;
  s_stream<<l.m()<<"*x +"<<l.i();
  return s_stream.str();

}
void ML::Visual::dump(const std::vector<ML::Point>& points1, const std::string& name1,
		      const std::vector<ML::Point>& points2, const std::string& name2,
		      const ML::Line& l1,
		      const ML::Line& l2, const std::string& fileName )
{
  write_points_to_file(points1, name1);
  write_points_to_file(points2, name2);
  std::ofstream file_stream;
  file_stream.open(fileName);
  file_stream<<"set xrange[-1.5:1.5]; set yrange[-1.5:1.5]; ";
  file_stream<<"plot "<<ML::Visual::to_string(l1)<<", ";
  file_stream<<Visual::to_string(l2)<<", ";
  file_stream<<"\""<<name1<<"\""<<" using 1:2, ";
  file_stream<<"\""<<name2<<"\""<<" using 1:2 \n";
  file_stream<<"pause -1\n";
  file_stream.close();
}

void ML::Visual::dump(int item, const std::vector<ML::Point>& goods,
		      const std::vector<ML::Point>& bads,
		      const ML::Point& selected,
		      const ML::Line& g,
		      const ML::Line& f, bool drawSelected)
{
  std::ostringstream name;
  name<<item<<".png";
  PNGScreen s(512, 512, -1, 1, -1, 1, name.str());
  s.plot_line(g, BLUE);
  s.plot_line(f, BLACK);
  
  for(auto p:goods)
    s.plot_point(p, GREEN);
  for(auto p:bads)
    s.plot_point(p, RED);
  if(drawSelected)
    s.plot_point(selected, CYAN);
  s.flush();
}

