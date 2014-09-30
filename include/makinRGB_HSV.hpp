//MAKIN 20 Juni 2014

#ifndef RGB_HSV_H
#define RGB_HSV_H

#include <math.h>/* fmod */


void rgbToHsv(int r, int g, int b, int *h, int *s, int *v)
{
			if (r<=1 && g<=1 && b<=1)
			{
				*h = 0;
				*s = 0;
				*v = 0;
				return;
			}
			
			float rs,gs,bs,cmax=0,cmin=1;
			rs = r/255.0;
			gs = g/255.0;
			bs = b/255.0;
			
			if (cmin>rs)	cmin = rs;
			if (cmin>gs)	cmin = gs;
			if (cmin>bs)	cmin = bs;
			
			*h=0;
			/** HUE **/
			if ((rs>=gs) && (rs>bs))
			{
				cmax = rs;
				//~ h = 60*	(int((gs-bs)/(cmax-cmin))%6);
				*h = int(60*	(
							fmod(	((gs-bs)/(cmax-cmin))	,	6.0)
						));
			}
			else if ((gs>=rs) && (gs>=bs))
			{
				cmax = gs;
				*h = int(60* (((bs-rs)/(cmax-cmin))+2.0));
			}
			else if ((bs>=rs) && (bs>=gs))
			{
				cmax = bs;
				*h = int(60* (((rs-gs)/(cmax-cmin))+4.0));
			}
			/** SATURATION **/
			if ((cmax-cmin)==0)
				*s = 0;
			else
			{
				*s = int(((cmax-cmin)/cmax)*100.0);
			}
			
			/** VALUE **/
			*v = int(cmax*100.0);
			return;
}
class newRGBtoHSV{
	public:
		newRGBtoHSV();
		int r,g,b,h,s,v;
		void setRGB(int Red, int Green, int Blue)
		{
			r= Red;
			g= Green;
			b= Blue;
		}
		void calculateHSV(void)
		{
			float rs,gs,bs,cmax=0,cmin=1;
			rs = r/255.0;
			gs = g/255.0;
			bs = b/255.0;
			
			if (cmin>rs)	cmin = rs;
			if (cmin>gs)	cmin = gs;
			if (cmin>bs)	cmin = bs;
			
			/** HUE **/
			if ((rs>=gs) && (rs>bs))
			{
				cmax = rs;
				//~ h = 60*	(int((gs-bs)/(cmax-cmin))%6);
				h = int(60*	(
							fmod(	((gs-bs)/(cmax-cmin))	,	6.0)
						));
			}
			else if ((gs>=rs) && (gs>=bs))
			{
				cmax = gs;
				h = int(60* (((bs-rs)/(cmax-cmin))+2.0));
			}
			else if ((bs>=rs) && (bs>=gs))
			{
				cmax = bs;
				h = int(60* (((rs-gs)/(cmax-cmin))+4.0));
			}
			/** SATURATION **/
			if ((cmax-cmin)==0)
				s = 0;
			else
			{
				s = int(((cmax-cmin)/cmax)*100.0);
			}
			
			/** VALUE **/
			v = int(cmax*100.0);
		}
};
newRGBtoHSV::newRGBtoHSV()
{
	r=0;g=0;b=0;h=0;s=0;v=0;
}

#endif

