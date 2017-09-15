#include <string>
#include <string>
#include <fstream>
#pragma once
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"
#include <glm\gtx\matrix_decompose.hpp>

#include "Model.h"
#include "Shader.h"
#include "rotate.h"

class Bone {

public:
	string nodeName;
	Bone *parent;
	vector<Bone> children;

	//initial orietantion and translation
	glm::vec3 init_translate;
	glm::mat4 init_R;

	//variation
	glm::mat4 R;
	glm::vec3 translate;
	glm::vec3 angle;

	//transformation
	glm::mat4 transform;

	//visualise tree structure
	void Print(string indent, bool last);

	//update position with respect to parent
	void UpdatePosition(glm::mat4 parent, bool last);

};

void Bone::Print(string indent, bool last)
{
	cout << indent;
	if (last)
	{
		cout << "\\-";
		indent += "  ";
	}
	else {
		cout << "|\t-";
		indent += "| \t";
	}
	cout << this->nodeName << endl;
	for (int i = 0; i<this->children.size(); i++)
	{
		children[i].Print(indent, i == children.size());
	}
}



void Bone::UpdatePosition(glm::mat4 parent, bool last)
{
	this->angle = glm::vec3(0);
	this->transform = glm::mat4(parent);

	//Rotation
	this->transform *= this->init_R;
	this->transform *= this->R;
	//Translation
	this->transform = glm::translate(this->transform, this->init_translate);
	this->transform = glm::translate(this->transform, this->translate);

	//pass on rotation
	for (int i = 0; i<this->children.size(); i++)
	{
		children[i].UpdatePosition(this->transform, i == children.size());
	}
}