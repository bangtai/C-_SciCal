#ifndef __GRAHAMSCAN_H
#define __GRAHAMSCAN_H

#include "_CvHullBase.h"

namespace ams562 {
//
// Finish define class GrahamScan as a child of CvHulllBase
// and override apply
class GrahamScan : public CvHullBase{
public:
    void apply(std::vector<Point2D> &pc, std::vector<Point2D> &ch) const;
    
};
}

#endif
