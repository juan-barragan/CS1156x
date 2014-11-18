#include"PNGScreen.h"
#include<gd.h>
#include<cmath>
#include<iostream>

const double epsilon = 0.00000001;

namespace ML 
{
  struct gdImage
  {
    gdImagePtr image;
  };
};

ML::PNGScreen::PNGScreen(int px, int py, 
			 double ax, double bx,
			 double ay, double by,
			 const std::string& fileName)
  : xPixels(px), yPixels(py), a_x(ax), b_x(bx), a_y(ay), b_y(by), 
    m_x(px/(bx-ax)), m_y(py/(by-ay)), file(fileName)
{
  pimpl_img = new gdImage();
  pimpl_img->image = gdImageCreate(xPixels, yPixels);

  colors[WHITE] = gdImageColorAllocate(pimpl_img->image, 255, 255, 255);
  colors[BLACK] = gdImageColorAllocate(pimpl_img->image, 0, 0, 0);
  colors[RED] = gdImageColorAllocate(pimpl_img->image, 255, 0, 0);
  colors[BLUE] = gdImageColorAllocate(pimpl_img->image, 0, 0, 255);
  colors[GREEN] = gdImageColorAllocate(pimpl_img->image, 0, 255, 0);
  colors[CYAN] = gdImageColorAllocate(pimpl_img->image, 0, 255, 255);
}

ML::PNGScreen::~PNGScreen()
{
  gdImageDestroy(pimpl_img->image);
  delete pimpl_img;
}

int ML::PNGScreen::toPixel_x(double x) const
{
  return m_x*(x - a_x);
}
int ML::PNGScreen::toPixel_y(double y) const
{
  return yPixels - m_y*(y - a_y);
}

void ML::PNGScreen::plot_line(const Line& l, COLOR c)
{
  if (std::abs(l.B()) < epsilon)
    return ;
  double m = l.m();
  double b = l.i();
  double y_ax = m*a_x + b;
  double y_bx = m*b_x + b;
  gdImageLine(pimpl_img->image, toPixel_x(a_x), toPixel_y(y_ax), toPixel_x(b_x), toPixel_y(y_bx), colors[c]);   
}

void ML::PNGScreen::plot_point(const Point& p, COLOR c)
{
  //plot_point(p.x, p.y, c);
  gdImageSetPixel(pimpl_img->image, toPixel_x(p.x), toPixel_y(p.y), colors[c]);
}
  
void ML::PNGScreen::plot_point(double x, double y, COLOR c)
{
  //  gdImageSetPixel
  gdImageFilledEllipse(pimpl_img->image, toPixel_x(x), toPixel_y(y), 5, 5, colors[c]);
}

double ML::PNGScreen::toPlane_x(int pixel) const
{
  return pixel/m_x + a_x;
}

double ML::PNGScreen::toPlane_y(int pixel) const
{
  return (yPixels - pixel)/m_y + a_y;
}

void ML::PNGScreen::plot_circle(const Point& p, COLOR)
{
}

#include <stdio.h>
void ML::PNGScreen::flush() const
{
  FILE * f = fopen(file.c_str(), "w");
  gdImagePng(pimpl_img->image, f);
  fclose(f);
}
