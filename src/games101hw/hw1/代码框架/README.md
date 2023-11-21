model matrix

```cpp
Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.

    Eigen::Matrix4f rotation;
    rotation << cos(rotation_angle), -sin(rotation_angle), 0, 0, 
                sin(rotation_angle), cos(rotation_angle), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1;
    model = rotation * model;

    return model;
}
```


projection matrix

```cpp
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.

    float n = zNear, f = zFar;

    Eigen::Matrix4f orth;
    orth << n, 0, 0, 0,
            0, n, 0, 0,
            0, 0, n+f, -n*f,
            0, 0, 1, 0;
    
    projection = orth * projection;

    return projection;
}
```


rotation matrix

```cpp
// rotation any axis
Eigen::Matrix4f get_rotation(Vector3f axis, float angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f rotation;

    if (axis == Vector3f(1,0,0)){
        rotation << 1,0,0,0,
                    0, cos(angle), -sin(angle), 0,
                    0, sin(angle), cos(angle), 0,
                    0, 0, 0, 1;
    }
    else if (axis == Vector3f(0,1,0)){
        rotation << cos(angle), 0, -sin(angle), 0,
                    0, 1, 0, 0,
                    -sin(angle), 0, cos(angle), 0,
                    0, 0, 0, 1;
    }
    else if (axis == Vector3f(0,0,1)){
        rotation << cos(angle), -sin(angle), 0, 0, 
                    sin(angle), cos(angle), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;
    }
    else {
        std::cout << "Plz input right axis vector!" << std::endl;
    }
```