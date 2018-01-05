#include "GrahamScan.h"
#include <algorithm>
#include <vector>

namespace ams562 {

void GrahamScan::apply(std::vector<Point2D> &pc, std::vector<Point2D> &ch) const {

    //
    // First find the lowest point by using std::max_element
    // if there are ties, pick the most left one

    std::vector<Point2D>::iterator result = std::min_element(std::begin(pc), std::end(pc), 
        [] (const Point2D &p1, const Point2D &p2){ return p1.cogety() < p2.cogety();});
    
    for (int i = 0; i < pc.size(); i++){
        if ((*result).cogety() == pc[i].cogety()){
            if ((*result).cogetx() < pc[i].cogetx()){
                *result = pc[i];            //judge whether result is the left most point
            }
        }
    }

    //
    // Then, swap that point with the first element in pc

    pc[0].swap(*result);

    //
    // Next step is to sort the 2nd point to the last point in pc
    // by polar angle with the first point in pc
    // Note that the first point in pc is the lowest point in the
    // point cloud. std::sort

    std::sort(pc.begin() + 1, pc.end(), [pc] (const Point2D &p1, const Point2D &p2){
                
        double x1 = p1.cogetx() - (*pc.begin()).cogetx();
        double y1 = p1.cogety() - (*pc.begin()).cogety();
        double x2 = p2.cogetx() - (*pc.begin()).cogetx();
        double y2 = p2.cogety() - (*pc.begin()).cogety();

        if (x1 < 0 && x2 > 0){
            return false;
        }
        else if (x1 > 0 && x2 <0){
            return true;
        }
        else if (x1 == 0 && x2 < 0){
            return true ;
        }
        else if (x1 == 0 && x2 > 0){
            return false;
        }
        else if (x1 < 0 && x2 == 0){
            return false;
        }
        else if (x1 > 0 && x2 == 0){
            return true;
        }
        else {
            return (y1 / x1) < (y2 / x2);
        }
        
    });

    //
    // Push back the first and second points to the back
    // of ch, push_back of ch should be used

    ch.push_back(pc[0]);
    ch.push_back(pc[1]);


    //
    // Bonus, I do the cur for you

    auto cur = pc.begin()+2;
    while (cur != pc.end()) {
        //
        // Get the last 2 points in ch by using iterators
        // note that you can start with ch.end(), be aware
        // of the position of ch.end()
        auto iter1 = ch.end() - 2;
        auto iter2 = ch.end() - 1;

        //
        // Compute the orientation information of ch's last1
        // last2 and cur
        
        int ori = (*cur).orientation(*iter1, *iter2); 

        //
        // if cur is to left of last1_last2
        // then push cur to ch

        if (ori > 0){
            ch.push_back(*cur);
            cur++; 
        }

        //
        // else if cur is collinear and cur lies futher
        // replace the last point of ch by cur

        else if (ori == 0){
            if (dist_sq(*cur, *iter1) >= dist_sq(*iter2, *iter1)){
                ch.pop_back();
                ch.push_back(*cur);
            }
            //*ch.end() = *cur; 
            cur++;
        }

        //
        // else, pop the last point back from ch
        // and keep ch unchanged

        else{
            ch.pop_back();
        }
    }
}

}
