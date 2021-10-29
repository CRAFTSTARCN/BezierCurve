#pragma once

#include <list>

#include "EdgeAndPoint.h"
#include "../core/Component.h"
#include "../core/Mesh.h"

class BezierCurveAlgo : public Component {
    
    float t_step_;
    std::list<Point> points_;
    Mesh* owner_mesh_;
    bool work_stat;
    float change_stat;
    std::vector<Point> point_arr[2];
    
public:
    BezierCurveAlgo(int segment_count);
    ~BezierCurveAlgo() override;

    void bezierAlgoPoint(float cur_t);
    void bezierAlgo();
    
    void update() override;
    void onActivate() override;
    std::string componentType() const override;

    std::list<Point>* getPointLoop();
};
