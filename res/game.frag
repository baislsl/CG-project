#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 fragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 lightPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    bool use;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;
uniform bool usingTexture;
uniform vec3 viewPos;
uniform bool selflight;

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    if (usingTexture)
    {
        if (selflight) ambient = vec4(1, 1, 1, 1) * (texture(texture_diffuse1, TexCoords));
        else ambient  = vec4(light.ambient, 1)  * (texture(texture_diffuse1, TexCoords));
        diffuse  = vec4(light.diffuse, 1) * diff * (texture(texture_diffuse1, TexCoords));
        specular = vec4(light.specular, 1) * spec * (texture(texture_specular1, TexCoords));
    }
    else
    {
        ambient = vec4(light.ambient * material.ambient, 1);
        diffuse = vec4(light.diffuse * diff * material.diffuse, 1);
        specular = vec4(light.specular * spec * material.specular, 1);
    }
    ambient = max(ambient, vec4(0, 0, 0, 0));
    diffuse = max(diffuse, vec4(0, 0, 0, 0));
    specular = max(specular, vec4(0, 0, 0, 0));
    if (selflight) return ambient;
    return (ambient + diffuse + specular);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                 light.quadratic * (distance * distance));
    // 合并结果
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    if (usingTexture)
    {
        if (selflight) ambient = vec4(1, 1, 1, 1.0) * (texture(texture_diffuse1, TexCoords));
        ambient  = vec4(light.ambient, 1.0) * (texture(texture_diffuse1, TexCoords));
        diffuse  = vec4(light.diffuse, 1.0) * diff * (texture(texture_diffuse1, TexCoords));
        specular = vec4(light.specular, 1.0) * spec * (texture(texture_specular1, TexCoords));
    }
    else
    {
        ambient = vec4(light.ambient * material.ambient, 1);
        diffuse = vec4(light.diffuse * diff * material.diffuse, 1);
        specular = vec4(light.specular * spec * material.specular, 1);
    }
    ambient = max(ambient, vec4(0, 0, 0, 0));
    diffuse = max(diffuse, vec4(0, 0, 0, 0));
    specular = max(specular, vec4(0, 0, 0, 0));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    if (selflight) return ambient;
    return (ambient + diffuse + specular);
}


void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
//    定向光
//    vec3 result = CalcDirLight(dirLight, norm, viewDir);
//    FragColor = vec4(result, 1);
    vec4 result = CalcDirLight(dirLight, norm, viewDir);
//    点光源
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        if (pointLights[i].use == true) result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);
    }
    FragColor = result;
//    FragColor = texture(texture_diffuse1, TexCoords);
}


