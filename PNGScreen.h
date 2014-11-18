#ifndef ML_PNGSCREEN_H
#define ML_PNGSCREEN_H

#include"Line.h"
#include"Point.h"

namespace ML
{
  class gdImage;
  enum COLOR { WHITE=0, BLACK, RED, BLUE, GREEN, CYAN };
  
  class PNGScreen
  {
  public:
    PNGScreen(int, int, 
	      double, double,
	      double, double,
	      const std::string&);
    void flush() const;
    ~PNGScreen();

    void plot_line(const Line& l, COLOR);
    void plot_point(const Point& p, COLOR);
    void plot_circle(const Point& p, COLOR);
    void plot_point(double x, double y, COLOR);
    double toPlane_x(int pixel) const;
    double toPlane_y(int pixel) const;
    inline int width() const { return yPixels; }
    inline int height() const { return xPixels; }
  private:
    int toPixel_x(double x) const;
    int toPixel_y(double y) const;
    int xPixels;
    int yPixels;
    double a_x;
    double b_x;
    double a_y;
    double b_y;
    double m_x;
    double m_y;
    gdImage* pimpl_img; 
    std::string file;
    int colors[CYAN+1];
  };
};

#endif // ML_PNGSCREEN_H
