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
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
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

    Intersection view_to_obj = Scene::intersect(ray);
    if (!view_to_obj.happened) {
        return { 0.0,0.0,0.0 };
    }

    if (view_to_obj.m->hasEmission()) {
        return view_to_obj.m->getEmission();
    }

    Intersection light_pos;
    float pdf_light = 0.0f;
    sampleLight(light_pos, pdf_light);

    Vector3f p = view_to_obj.coords;
    Vector3f N = view_to_obj.normal.normalized();
    Vector3f wo = ray.direction;

    Vector3f xx = light_pos.coords;
    Vector3f NN = light_pos.normal.normalized();
    Vector3f ws = (p - xx).normalized();

    Vector3f dir = { 0.0,0.0,0.0 };
    Ray light_to_obj(xx, ws);

    Intersection light_blocked = Scene::intersect(light_to_obj);
    Vector3f tmp = p - xx;
    float dis_target = tmp.norm();
    float dis2 = dotProduct((p - xx), (p - xx));
    float dis_blocked = light_blocked.distance;

    if (light_blocked.happened && (dis_target - dis_blocked < EPSILON)) {
        Vector3f L_i = light_pos.emit;
        Vector3f f_r_dir = light_blocked.m->eval(wo, -ws, N);
        float cos_theta = dotProduct(-ws, N);
        float cost_theta_l = dotProduct(ws, NN);
        dir = L_i * f_r_dir * cos_theta * cost_theta_l / dis2 / pdf_light;
    }

    Vector3f indir = { 0.0, 0.0, 0.0 };
    float p_rr = get_random_float();
    if (p_rr < RussianRoulette) {
        Vector3f wi_indir = view_to_obj.m->sample(wo, N);
        Ray ray_indir(p, wi_indir);

        Intersection indir_obj = Scene::intersect(ray_indir);

        if (indir_obj.happened && !indir_obj.m->hasEmission()) {
            Vector3f f_r_indir = view_to_obj.m->eval(wo, wi_indir, N);
            float pdf_obj = view_to_obj.m->pdf(wo, wi_indir, N);
            float cost_theta = dotProduct(wi_indir, N);
            indir = castRay(ray_indir, indir_obj.distance) * f_r_indir * cost_theta / pdf_obj / RussianRoulette;
        }
    }

    return dir + indir;

}