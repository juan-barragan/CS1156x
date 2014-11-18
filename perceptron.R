drawLine<-function(w)
{
	par(new=T)	
	x = seq(-1.0,1.0, 0.01)		
	y = -w[1]/w[2]*x - w[3]/w[2]
	plot(x, y, t="n", xlim=c(-1.5,1.5), ylim=c(-1.5,1.5));
	lines(x,y)
}

sign<-function(w, p)
{
	s=1;
	if(w[1]*p[1] + w[2]*p[2] + w[3]*p[3]<0)
	  s=-1;
	s
}

plotData<-function()
{
	par(new=T)
	testdata <- read.table("points.dat")
	plot(testdata, xlim=c(-1.5,1.5), ylim=c(-1.5,1.5));
}

p1 = c(testdata[1,1], testdata[1,2], 1)
p2 = c(testdata[1,1], testdata[1,2], 1)
p1 = c(testdata[1,1], testdata[1,2], 1)
p1 = c(testdata[1,1], testdata[1,2], 1)
p1 = c(testdata[1,1], testdata[1,2], 1)
p1 = c(testdata[1,1], testdata[1,2], 1)
p1 = c(testdata[1,1], testdata[1,2], 1)
p1 = c(testdata[1,1], testdata[1,2], 1)
