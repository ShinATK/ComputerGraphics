//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

// 寻找光线与场景中哪个包围盒相交
Intersection Scene::intersect(const Ray& ray) const {
    return this->bvh->Intersect(ray);
}

// 对光源随机采样
void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0.0f;//发光区域面积
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

    // 对primary ray计算与场景中的交点
    Intersection view_to_obj = Scene::intersect(ray);

    // 如果没有交点
    if (!view_to_obj.happened) {
        return { 0.0, 0.0, 0.0 };
    }

    // 有交点，则判断是光源还是物体
  
    // 如果打到的是光源
    // 对应于渲染方程的自发光项
    //（目前应该是认为自发光=光源，即不考虑其反射的光线了）
    Vector3f emit = { 0.0,0.0,0.0 };// 自发光项
    if (view_to_obj.m->hasEmission()) {
        emit = view_to_obj.m->getEmission();
        return emit;
    }

    // 如果打到的是物体
    // 对应于渲染方程中直接和间接的反射部分

    // 对场景中的光源采样，获取采样光源的位置和pdf
    Intersection light_pos;
    float pdf_light = 0.0f;
    sampleLight(light_pos, pdf_light);

    // 物体交点位置，法线，像素到物体交点的方向
    Vector3f p = view_to_obj.coords;//交点的位置
    Vector3f N = view_to_obj.normal.normalized();//交点处法线
    Vector3f wo = ray.direction; // 对应于光线的反射方向，即从从相机到像素打出的光线，注意方向
    // 光源位置，光源法线，光源到物体交点的方向
    Vector3f xx = light_pos.coords;//光源位置
    Vector3f NN = light_pos.normal.normalized();//光源法线
    Vector3f wi_dir = (p - xx).normalized(); // 对应于光线的入射方向
   
    // 直接反射部分
/*
    交点是一定存在的，因为需要打到目标物体上
    问题在于，这个交点，和目标物体的交点是否为同一个
    所以还需要判断一下交点的深度是否相同，但浮点数很难保证一定相同
    所以这里设置二者相差在某个很小的误差范围内即可认为是同一个位置
*/
    Vector3f dir = { 0.0, 0.0, 0.0 };//直接光源，直接从光源发出没有经过其他物体反射
    Vector3f f_r_dir = { 0.0, 0.0, 0.0 };
    Ray light_to_obj(xx, wi_dir); // 光源打向物体的光线
    Intersection light_blocked = Scene::intersect(light_to_obj);
    float dis_target = (p - xx).norm();// 光源到目标物体的距离
    float dis2 = dotProduct((p - xx), (p - xx));
    float dis_blocked = light_blocked.distance;//光源到遮挡物的距离
    // 能挡住的一定是比target obj更靠近光源的obj
    if (light_blocked.happened && (dis_target - dis_blocked < EPSILON)) {
        emit = light_blocked.m->getEmission();
        f_r_dir = light_blocked.m->eval(wi_dir, wo, N);
        dir = emit * f_r_dir * dotProduct(wi_dir, N) * dotProduct(wi_dir, NN) / dis2 / pdf_light;
    }

    // 间接反射部分
    Vector3f indir = { 0.0, 0.0, 0.0 }; // 间接光源，经由其他物体反射的入射光线
    Vector3f f_r_indir = { 0.0,0.0,0.0 };
    float pdf_obj = 0.0f;
    float p_rr = get_random_float();
    // 大于一定概率时，物体才会反射光线
    if (p_rr < RussianRoulette) {
        Vector3f wi_indir = view_to_obj.m->sample(wo, N);
        Ray ray_indir(p, wi_indir);
        Intersection indir_obj = Scene::intersect(ray_indir);

        if (!indir_obj.m->hasEmission()) {
            f_r_indir = view_to_obj.m->eval(wi_indir, wo, N);
            pdf_obj = view_to_obj.m->pdf(wi_indir, wo, N);
            indir = castRay(ray_indir, indir_obj.distance) * f_r_indir * dotProduct(wi_indir, N) / pdf_obj / RussianRoulette;
        }
    }
    
    return dir + indir;

}

