#include <random>
#include "TranslucenceCube.h"

TranslucencePlane::TranslucencePlane(unsigned int cc) : cc(cc)
{ init(); }

void TranslucencePlane::init()
{
	// plane 默认长度为2,缩为1
	plane.modelMatrix = glm::scale(plane.modelMatrix, glm::vec3(0.5, 0.5, 1));

	std::array<glm::vec3, div> ms{
			{{0.5, 0.7, 0.2}, {0.4, 0.8, 0.2},{0.24, 0.52, 0.09}, {0.16, 0.34, 0.06}}
	};

	for(auto &color : ms){
		Material m;
		m.specular = m.diffuse = m.ambient = color;
		materials.emplace_back(m);
	}

	std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u1(0, 30);
	std::uniform_int_distribution<int> u2(0, div);
	map.resize(cc);
	for (int i = 0; i < cc; i++)
	{
		map[i].resize(cc);
		for (int j = 0; j < cc; j++)
		{
			map[i][j] = u1(e) == 0 ? div : u2(e);
		}
	}

}

void TranslucencePlane::render(const Shader &shader, const Camera &camera)
{
	for (int i = 0; i < cc; i++)
	{
		for (int j = 0; j < cc; j++)
		{
			if (map[i][j] == div) continue;

			plane.material = materials[map[i][j]];
			plane.modelMatrix = glm::scale(this->modelMatrix, glm::vec3(1.0 / cc, 1.0 / cc, 1.0 / cc));
			plane.modelMatrix = glm::translate(plane.modelMatrix, glm::vec3(i - cc / 2 + 0.5, j - cc / 2 + 0.5, 0));
			plane.render(shader, camera);

		}
	}

}

void TranslucenceCube::render(const Shader &shader, const Camera &camera)
{
	std::array<glm::vec3, 6> r = {{{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
	std::array<glm::vec3, 2> t = {{{0, 0, -0.5}, {0, 0, 0}}};

	planes[0].modelMatrix = glm::rotate(this->modelMatrix, glm::radians(90.f), r[0]);
	planes[0].modelMatrix = glm::translate(planes[0].modelMatrix, glm::vec3(-0.5, 0, 0.5));
	planes[0].render(shader, camera);
	planes[1].modelMatrix = glm::rotate(this->modelMatrix, glm::radians(90.f), r[0]);
	planes[1].modelMatrix = glm::translate(planes[1].modelMatrix, glm::vec3(-0.5, 0, 0));
	planes[1].render(shader, camera);

	for (int i = 2; i < 6; i++)
	{
		planes[i].modelMatrix = glm::rotate(this->modelMatrix, glm::radians(90.0f), r[i / 2]);
		planes[i].modelMatrix = glm::translate(planes[i].modelMatrix, t[i % 2]);
		planes[i].render(shader, camera);
	}

}
