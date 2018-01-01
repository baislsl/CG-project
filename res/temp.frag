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

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    if (usingTexture)
    {
        ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));
        diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
        specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    }
    else
    {
        ambient = light.ambient * material.ambient;
        diffuse = light.diffuse * diff * material.diffuse;
        specular = light.specular * spec * material.specular;
    }
    ambient = max(ambient, vec3(0, 0, 0));
    diffuse = max(diffuse, vec3(0, 0, 0));
    specular = max(specular, vec3(0, 0, 0));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
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
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    if (usingTexture)
    {
        ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));
        diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
        specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    }
    else
    {
        ambient = light.ambient * material.ambient;
        diffuse = light.diffuse * diff * material.diffuse;
        specular = light.specular * spec * material.specular;
    }
    ambient = max(ambient, vec3(0, 0, 0));
    diffuse = max(diffuse, vec3(0, 0, 0));
    specular = max(specular, vec3(0, 0, 0));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}


void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
//    定向光
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    FragColor = vec4(result, 1.0);
//    点光源

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);
    FragColor = vec4(result, 1.0);
}

