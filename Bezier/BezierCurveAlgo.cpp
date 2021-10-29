#include "BezierCurveAlgo.h"

#include "../core/RenderableObject.h"
#include "../util/InputHandler.h"

BezierCurveAlgo::BezierCurveAlgo(int segment_count) :
    Component(), points_(), owner_mesh_(nullptr), work_stat(false), change_stat(false)
{
    t_step_ = 1.0f / static_cast<float>(segment_count);
    points_ = {
        Point(450, 800), 
        Point(200, 100), 
        Point(850, 100)
    };
}

BezierCurveAlgo::~BezierCurveAlgo() = default;


void BezierCurveAlgo::bezierAlgoPoint(float cur_t) {
    float minus_t = 1.0-cur_t;
    point_arr[0].clear(); point_arr[1].clear();
    auto end_it =  (--points_.end());
    for(auto beg = points_.begin(); beg != end_it; ++beg) {
        auto nxt = std::next(beg);
        point_arr[0].push_back(Point((minus_t*beg->x + cur_t*nxt->x) ,
                                         (minus_t*beg->y + cur_t*nxt->y)));
    }
    int cur_point_arr_ind = 0;
    while(point_arr[cur_point_arr_ind].size() > 1) {
        int nxt_point_arr_ind = (cur_point_arr_ind + 1) % 2;
        point_arr[nxt_point_arr_ind].clear();
        for(int i=0; i<point_arr[cur_point_arr_ind].size()-1; ++i) {
            point_arr[nxt_point_arr_ind].emplace_back(
                (minus_t*point_arr[cur_point_arr_ind][i].x + cur_t*point_arr[cur_point_arr_ind][i+1].x),
                (minus_t*point_arr[cur_point_arr_ind][i].y + cur_t*point_arr[cur_point_arr_ind][i+1].y) 
            );
        }
        cur_point_arr_ind = nxt_point_arr_ind;
    }
    Point n_point = point_arr[cur_point_arr_ind][0];
    owner_mesh_->addVertex(n_point.x,n_point.y, -1.0);
}

void BezierCurveAlgo::bezierAlgo() {
    owner_mesh_->clearVertex();
    if(points_.size() < 3) return;
    for(float t = 0.0; t < 1.0f; t += t_step_) {
        bezierAlgoPoint(t);
    }
}

void BezierCurveAlgo::update() {
    if(InputHandler::getKeyDown(GLFW_KEY_C)) {
        work_stat = !work_stat;
        change_stat = true;
    } else if(InputHandler::getMouseR()) {
        work_stat = false;
        owner_mesh_->clearVertex();
    }

    if(InputHandler::getMouseL() ||
       InputHandler::getMouseDownL() ||
       InputHandler::getKeyDown(GLFW_KEY_D)) {
        change_stat = true;
    }

    if(work_stat) {
        bezierAlgo();
        change_stat = false;
    }
}

void BezierCurveAlgo::onActivate() {
    owner_mesh_ = attachedObject->getMesh();
}

std::string BezierCurveAlgo::componentType() const {
    return "BezierCurveAlgo";
}

std::list<Point>* BezierCurveAlgo::getPointLoop() {
    return  &points_;
}
