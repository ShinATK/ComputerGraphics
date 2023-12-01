//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    // 光源面积
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            // 计算 scene 中全部 light_source 的面积之和
            emit_area_sum += objects[k]->getArea();
        }
    }
    // 设置采样概率
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            // 判断光源采样的总面积是否达到采样要求
            if (p <= emit_area_sum){
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

    // 计算 ray 与 scene 的交点
    Intersection view_to_obj = Scene::intersect(ray);
    // 没有交点返回 none
    if (!view_to_obj.happened) {
        return { 0.0,0.0,0.0 };
    }

    // 有交点，判断是否为光源
    if (view_to_obj.m->hasEmission()) {
        return view_to_obj.m->getEmission();
    }

    // 交点不是光源，开始考虑直接光照和间接光照

    // 直接光照，设置光源的参数
    Intersection light_pos;
    float pdf_light = 0.0f;
    // 对光源采样
    sampleLight(light_pos, pdf_light);

    // 交点位置、法线、及出射方向
    Vector3f p = view_to_obj.coords;
    Vector3f N = view_to_obj.normal.normalized();
    Vector3f wo = ray.direction;

    // 光源位置、法线、交点入射方向（光源指向交点）
    Vector3f xx = light_pos.coords;
    Vector3f NN = light_pos.normal.normalized();
    Vector3f ws = (p - xx).normalized();

    Vector3f dir = { 0.0,0.0,0.0 };
    Ray light_to_obj(xx, ws);
    // 判断从光源到 point 的 ray 有没有被 blocked
    Intersection light_blocked = Scene::intersect(light_to_obj);
    Vector3f tmp = p - xx;
    float dis_target = tmp.norm();
    float dis2 = dotProduct((p - xx), (p - xx));
    float dis_blocked = light_blocked.distance;
    // blocked 位置是否和目标交点位置是同一个
    // 在误差范围内即可
    if (light_blocked.happened && (dis_target - dis_blocked < EPSILON)) {
        Vector3f L_i = light_pos.emit;
        // 注意这里计算要以交点为出发点计算
        // 所以 ws 要注意改变方向
        Vector3f f_r_dir = light_blocked.m->eval(wo, -ws, N);
        // 这里是计算 ws 和 N 的余弦值，要以交点为出发点
        float cos_theta = dotProduct(-ws, N);
        float cost_theta_l = dotProduct(ws, NN);
        dir = L_i * f_r_dir * cos_theta * cost_theta_l / dis2 / pdf_light;
    }

    // 计算间接光照
    Vector3f indir = { 0.0, 0.0, 0.0 };
    // 获取本次 shoot 的概率
    float p_rr = get_random_float();
    if (p_rr < RussianRoulette) {
        // 发生 shoot 开始计算
        // 对入射方向进行随机均匀采样  
        Vector3f wi_indir = view_to_obj.m->sample(wo, N);
        Ray ray_indir(p, wi_indir);
        // 找到入射方向上的交点
        Intersection indir_obj = Scene::intersect(ray_indir);
        // 判断该 object 是否为光源
        // 是光源则不进行计算，因为此时是直接光照
        // 不是光源则开始进行递归调用
        if (indir_obj.happened && !indir_obj.m->hasEmission()) {
            Vector3f f_r_indir = view_to_obj.m->eval(wo, wi_indir, N);
            float pdf_obj = view_to_obj.m->pdf(wo, wi_indir, N);
            float cost_theta = dotProduct(wi_indir, N);
            // 递归调用，并除以 shoot ray 的概率值
            indir = castRay(ray_indir, indir_obj.distance) * f_r_indir * cost_theta / pdf_obj / RussianRoulette;
        }
    }

    return dir + indir;

}