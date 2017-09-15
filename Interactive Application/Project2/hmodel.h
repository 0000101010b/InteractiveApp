#pragma once
#include "Bones.h"


class Hand
{
public:
	Model model = NULL;
	Bone root;
	Hand(Model model);

	void BonePos();
	void RenderObject(Shader shader,Bone *pNode);
	void Draw(Shader shader);


	void DisplayHierarchy();

	void Grasp(glm::vec3 rot);
	void Wave(glm::vec3 rot);


private:

};

Hand::Hand(Model model)
	: model(model)
{
	BonePos();

	DisplayHierarchy();

	root.UpdatePosition(root.transform,true);
}

void Hand::BonePos() {
	//base bone wrist
	root = Bone();
	root.nodeName = "base";
	root.init_translate = glm::vec3(-20.0f, 0.0f, 0.0f);
	root.transform = glm::scale(glm::vec3(0.2f, 0.2f, 0.2f));
	root.R = qRotate(glm::vec3(0,270.0f,0));

	#pragma region Finger1
	//finger 1
	Bone f1_part1 = Bone();
	f1_part1.nodeName = "finger_1_1";
	f1_part1.init_translate = glm::vec3(-5.0f, 10.0f, 0.0f);

	glm::mat4 cTransform = glm::mat4(root.transform);
	f1_part1.transform = glm::translate(cTransform, glm::vec3(-5.0f, 10.0f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));


	Bone f1_part2 = Bone();
	f1_part2.nodeName = "finger_1_2";

	f1_part2.init_translate = glm::vec3(0.0f, 2.5f, 0.0f);

	glm::mat4 c2Transform = glm::mat4(f1_part1.transform);
	f1_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 2.5f, 0.0f));
	//f1_part2.transform *= qRotate(glm::vec3(45.0f));


	Bone f1_part3 = Bone();
	f1_part3.nodeName = "finger_1_3";
	f1_part3.init_translate = glm::vec3(0.0f, 2.5f, 0.0f);

	glm::mat4 c3Transform = glm::mat4(f1_part2.transform);
	f1_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 2.5f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));


	f1_part2.children.push_back(f1_part3);
	f1_part1.children.push_back(f1_part2);
	//f1_part1.children.push_back(f1_part3);

	root.children.push_back(f1_part1);
	//root.children.push_back(f1_part2);
	//root.children.push_back(f1_part3);
#pragma endregion

	#pragma region Finger2
	//finger 2
	Bone f2_part1 = Bone();
	f2_part1.nodeName = "finger_2_1";

	cTransform = glm::mat4(root.transform);
	f2_part1.transform = glm::translate(cTransform, glm::vec3(-2.0f, 11.5f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));

	f2_part1.init_translate = glm::vec3(-2.0f, 11.5f, 0.0f);



	Bone f2_part2 = Bone();
	f2_part2.nodeName = "finger_2_2";
	f2_part2.init_translate = glm::vec3(0.0f, 3.0f, 0.0f);

	c2Transform = glm::mat4(f2_part1.transform);
	f2_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 3.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));


	Bone f2_part3 = Bone();
	f2_part3.nodeName = "finger_2_3";
	f2_part3.init_translate = glm::vec3(0.0f, 3.0f, 0.0f);

	c3Transform = glm::mat4(f2_part2.transform);
	f2_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 3.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	f2_part2.children.push_back(f2_part3);
	f2_part1.children.push_back(f2_part2);
	//f2_part1.children.push_back(f2_part3);

	//root.children.push_back(f2_part3);
	//root.children.push_back(f2_part2);
	root.children.push_back(f2_part1);

#pragma endregion

	#pragma region Finger3
	//finger 3
	Bone f3_part1 = Bone();
	f3_part1.nodeName = "finger_3_1";
	f3_part1.init_translate = glm::vec3(1.0f, 11.5f, 0.0f);

	cTransform = glm::mat4(root.transform);
	f3_part1.transform = glm::translate(cTransform, glm::vec3(1.0f, 11.5f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));


	Bone f3_part2 = Bone();
	f3_part2.nodeName = "finger_3_2";
	f3_part2.init_translate = glm::vec3(0.0f, 4.0f, 0.0f);

	c2Transform = glm::mat4(f3_part1.transform);
	f3_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 4.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	Bone f3_part3 = Bone();
	f3_part3.nodeName = "finger_3_3";
	f3_part3.init_translate = glm::vec3(0.0f, 4.0f, 0.0f);

	c3Transform = glm::mat4(f3_part2.transform);
	f3_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 4.0f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	f3_part2.children.push_back(f3_part3);
	f3_part1.children.push_back(f3_part2);
	//f3_part1.children.push_back(f3_part3);

	//root.children.push_back(f3_part3);
	//root.children.push_back(f3_part2);
	root.children.push_back(f3_part1);

#pragma endregion

	#pragma region Finger4
	//finger 1
	Bone f4_part1 = Bone();
	f4_part1.nodeName = "finger_4_1";
	f4_part1.init_translate = glm::vec3(4.0f, 11.5f, 0.0f);

	cTransform = glm::mat4(root.transform);
	f4_part1.transform = glm::translate(cTransform, glm::vec3(4.0f, 11.5f, 0.0f));




	//c1.transform *= qRotate(glm::vec3(45.0f));


	Bone f4_part2 = Bone();
	f4_part2.nodeName = "finger_4_2";
	f4_part2.init_translate = glm::vec3(0.0f, 3.25f, 0.0f);
	c2Transform = glm::mat4(f4_part1.transform);
	f4_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	Bone f4_part3 = Bone();
	f4_part3.nodeName = "finger_4_3";
	f4_part3.init_translate = glm::vec3(0.0f, 3.25f, 0.0f);

	c3Transform = glm::mat4(f4_part2.transform);
	f4_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));



	//f4_part1.children.push_back(f4_part3);
	f4_part2.children.push_back(f4_part3);
	f4_part1.children.push_back(f4_part2);

	//root.children.push_back(f4_part3);
	//root.children.push_back(f4_part2);
	root.children.push_back(f4_part1);

#pragma endregion

	#pragma region Thumb
	//thumb
	Bone t_part1 = Bone();
	t_part1.nodeName = "thumb_1";
	t_part1.init_translate = glm::vec3(7.5f, 5.25f, 0.0f);

	cTransform = glm::mat4(root.transform);
	t_part1.transform = glm::translate(cTransform, glm::vec3(7.0f, 5.5f, 0.0f));
	//c1.transform *= qRotate(glm::vec3(45.0f));

	Bone t_part2 = Bone();
	t_part2.nodeName = "thumb_2";
	t_part2.init_translate = glm::vec3(0.0f, 3.25f, 0.0f);

	c2Transform = glm::mat4(t_part1.transform);
	t_part2.transform = glm::translate(c2Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	Bone t_part3 = Bone();
	t_part3.nodeName = "thumb_3";
	t_part3.init_translate = glm::vec3(0.0f, 3.25f, 0.0f);

	c3Transform = glm::mat4(t_part2.transform);
	t_part3.transform = glm::translate(c3Transform, glm::vec3(0.0f, 3.25f, 0.0f));
	//c2.transform *= qRotate(glm::vec3(45.0f));

	//t_part1.children.push_back(t_part3);
	t_part2.children.push_back(t_part3);
	t_part1.children.push_back(t_part2);

	//root.children.push_back(t_part3);
	//root.children.push_back(t_part2);
	root.children.push_back(t_part1);

#pragma endregion
}

void Hand::DisplayHierarchy() {

	root.Print("", true);
}


void Hand::Grasp(glm::vec3 rot) {

	for (int i = 0; i < root.children.size(); i++)
	{
		Bone* knuckle = &root.children[i];
		for (int j = 0; j < knuckle->children.size(); j++) {

			knuckle->children[j].R *= qRotate(rot);
		}
	}
}
void Hand::Wave(glm::vec3 rot) {

	root.R *= qRotate(rot);

}


void Hand::RenderObject(Shader shader,Bone *pNode)
{
	glm::mat4 transformation;
	transformation = pNode->transform;
		
	GLint modelLoc = glGetUniformLocation(shader.Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation));
	
	model.Draw(shader);

	for each (Bone var in pNode->children)
	{
		RenderObject(shader, &var);
	}
}

void Hand::Draw(Shader shader) {
	this->RenderObject(shader,&root);
}

