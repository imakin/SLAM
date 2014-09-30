//MAKIN 20 Juni 2014
//more 29 Juni 2014

#ifndef MAKIN_LANDMARK_HPP
#define MAKIN_LANDMARK_HPP
	
#define MAX_LANDMARK 15
#define LANDMARK_ASOSIASI_DATA_SELISIH_MAX 10 //untuk pixel (rgb callback)
#define DEFAULT -1 ///minta nilai data asli
#define MAX_SAME_LANDMARK_RANGE 0.8	//untuk jarak 
#define SPIKE_EDGE 40
class landmark
{
	public :
		int landmark_count; ///start from 1 to MAX_LANDMARK
		int unique_count; /// itungan landmark nambah terus;
		int prelandmark_count; ///mulai dr 1 bukan 0
		struct prelandmarks_struct{
			int x0;
			int x1;
			int y0;
			int y1;
			int dr;
		};
		
		struct prelandmarks_struct prelandmarks[MAX_LANDMARK];
		
		struct landmarks_struct{
			float x;///di peta x,y coordinat cartesian
			float y;
			int r;
			int bearing;
			int id;
			int spike;
			//~ int observed;//berapa kali diobservasi ~ likely not used
		};
		struct landmarks_struct landmarks[MAX_LANDMARK];
		
		landmark(void)
		{
			landmark_count = 0;
			prelandmark_count = 0;
			unique_count = 0;
		}
		
		void addPreLandmark(int _x0, int _x1, int _y0, int _y1, int _depth_rerata)
		{
			prelandmark_count ++;
			prelandmarks[prelandmark_count].x0 = _x0;
			prelandmarks[prelandmark_count].x1 = _x1;
			prelandmarks[prelandmark_count].y0 = _y0;
			prelandmarks[prelandmark_count].y1 = _y1;
			prelandmarks[prelandmark_count].dr = _depth_rerata;
		}
	
		void deletePreLandmark( int _index)
		{
			
			for (int i=_index;i<=(prelandmark_count-1);i++)
			{
				prelandmarks[i].x0 = prelandmarks[i+1].x0;
				prelandmarks[i].x1 = prelandmarks[i+1].x1;
				prelandmarks[i].y0 = prelandmarks[i+1].y0;
				prelandmarks[i].y1 = prelandmarks[i+1].y1;
				prelandmarks[i].dr = prelandmarks[i+1].dr;	
			}
			if (prelandmark_count!=0)
				prelandmark_count=prelandmark_count-1;
		}
	
		void resetPreLandmark (int _index, int _x0, int _x1, int _y0, int _y1, int depth_rerata)
		{
			if (_x0!=DEFAULT)
				prelandmarks[_index].x0 = _x0;
			if (_x1!=DEFAULT)
				prelandmarks[_index].x1 = _x1;
			if (_y0!=DEFAULT)
				prelandmarks[_index].y0 = _y0;
			if (_y1!=DEFAULT)
				prelandmarks[_index].y1 = _y1;
			if (depth_rerata!=DEFAULT)
				prelandmarks[_index].dr = depth_rerata;
			
		}
	
		void addLandmark(int range_from_robot, int bearing_from_robot, float _x, float _y) ///Data matang x,y di peta coordinat cartesian
		{
			landmark_count++;
			unique_count++;
			landmarks[landmark_count].x = _x;
			landmarks[landmark_count].y = _y;
			landmarks[landmark_count].r = range_from_robot;
			landmarks[landmark_count].bearing = bearing_from_robot;
			landmarks[landmark_count].id = unique_count;
		}
		void deleteLandmark(int _index)
		{
			for (int i=_index;i<=(landmark_count-1);i++)
			{
				landmarks[i].x = landmarks[i+1].x;
				landmarks[i].y = landmarks[i+1].y;
				landmarks[i].r = landmarks[i+1].r;
				landmarks[i].bearing = landmarks[i+1].bearing;
				landmarks[i].id = landmarks[i+1].id;
				//~ landmarks[i] = landmarks[i+1];
			}
			if (landmark_count!=0)
				landmark_count=landmark_count-1;
		}
		void resetLandmark( int _index, int range_from_robot, int bearing_from_robot, float _x, float _y)
		{
			if (range_from_robot!=DEFAULT)
				landmarks[_index].r = range_from_robot;
			if (bearing_from_robot!=DEFAULT)
				landmarks[_index].bearing = bearing_from_robot;
			if (_x!=DEFAULT)
				landmarks[_index].x = _x;
			if (_y!=DEFAULT)
				landmarks[_index].y = _y;
			
			//~ landmarks[landmark_count].id = landmarks[landmark_count].id;
				
		}
		
		void removeDuplicateLandmark(void)
		{
			///the latest data has bigger index, liek dis if yu cri evrytiem
			int i,j;
			for (i=landmark_count;i>=2;i--)
			{
				for (j=i-1;j>=1;j--)
				{
					if (	(abs(landmarks[i].x - landmarks[j].x)<MAX_SAME_LANDMARK_RANGE) && (abs(landmarks[i].y - landmarks[j].y)<MAX_SAME_LANDMARK_RANGE))
					{
						landmarks[i].id = landmarks[j].id; ///id memakai ID lama
						deleteLandmark(j);
					}
				}
			}
			//~ for (i=landmark_count;i>=1;i--)
			//~ {
				//~ if (landmarks[i].spike<SPIKE_EDGE)
					//~ deleteLandmark(i);
			//~ }
		}
		~landmark(void)
		{
			landmark_count = 0;
		}
};

class singleLandmark
{
	public :
		int x;
		int y;
		int depth_rerata;
		int bearing;
	//~ void check(void)
};

#endif

