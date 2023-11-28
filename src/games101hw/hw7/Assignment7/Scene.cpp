//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

// 寻找光线与场景中哪个包围盒相交
Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

// 对光源随机采样
void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;//发光区域面积
    for (uint32_t k = 0; k < objects.size(); ++k) {//迭代所有物体
        if (objects[k]->hasEmit()){//计算直接光源总面积
            emit_area_sum += objects[k]->getArea();
        }
    }
    // 对场景中的所有光源
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    //开始对全部光源进行采样
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){// 随机选取一个光源面
                // 利用 Sample 在光源面中按照pdf的概率随机找到一个点pos
                // 得到这个点pos的信息
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here

    Vector3f dir = { 0.0, 0.0, 0.0 };
    Vector3f indir = { 0.0, 0.0, 0.0 };

    Intersection inter = Scene::intersect(ray);

    // 没有交点
    if (!inter.happened) return dir;

    Vector3f emit = { 0.0,0.0,0.0 };
    Vector3f f_r = { 0.0,0.0,0.0 };
    // 打到光源
    if (inter.m->hasEmission()) {
        emit = inter.m->getEmission();
        f_r = inter.m->eval();
        dir = emit * 
    }
    
}

