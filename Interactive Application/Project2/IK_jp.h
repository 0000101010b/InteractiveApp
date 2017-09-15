#pragma once


#include "Bones.h"
//#include <armadillo>
#include <Eigen/Dense>

using namespace Eigen;

class Arm {
public:
	Model model = NULL;
	vector<Bone> bones;

	Arm(Model model);

	bool IK(glm::vec3 g,glm::vec3 axis,float dt,float scale);
	void RenderObject(Shader shader, Bone *pNode);
	void Draw(Shader shader);
	void BonePos();

	
	
	

	

};

Arm::Arm(Model model)
	: model(model)
{
	BonePos();

}


bool Arm::IK(glm::vec3 g,glm::vec3 axis,float dt,float s){

		glm::vec3 e;
	
		for (int i = 0; i < bones.size(); i++)
			e += bones[i].init_translate;
		
		if (glm::distance(g, e) < 0.1f)
			return false;

		glm::vec3 j1 = glm::cross(axis, glm::normalize(e));
		glm::vec3 j2 = glm::cross(axis, glm::normalize(e - bones[1].init_translate));

		MatrixXf J(2,2);
		J(0, 0)=j1.x;
		J(1, 0)=j1.y;
		J(0, 1)=j2.x;
		J(1, 1)=j2.y;

		
		MatrixXf JPinv = J.completeOrthogonalDecomposition().pseudoInverse();

		glm::vec3 de = g - e;
		de = glm::normalize(de);

		MatrixXf V(1, 2);
		V(0, 0) = de.x;
		V(0, 1) = de.y;
		//V(0, 2) = de.z;
	
		//MatrixXf tempV=V.transpose();
		
		MatrixXf add(1,2);
		add=V* JPinv *dt * s;
		
		
		for (int i = 1; i < bones.size(); i++) {
			bones[i].angle.z += add(0 ,i - 1);
			
			float angle=bones[i].angle.z;
			bones[i].angle =  glm::vec3(0,0,fmod(angle,360.0f));
			
			glm::vec4 q=quatfromDegreeAxis(bones[i].angle);
			bones[i].init_translate =rotate_vector_by_quaternion(bones[i].init_translate, q);
		}
		for (int i = bones.size() - 1; i > 0; i--) {
			bones[i - 1].children.clear();
			bones[i - 1].children.push_back(bones[i]);
			cout << bones[i].angle.z << endl;
		}

		return true;

	//}
	//while (glm::distance(g, e) > 0.1f);
}
void Arm::RenderObject(Shader shader, Bone *pNode) {

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
void Arm::Draw(Shader shader) {
	this->RenderObject(shader, &bones[0]);
}

void Arm::BonePos() {

	int armcount = 3;
	bones.reserve(armcount);

	Bone root;
	root = Bone();
	root.nodeName = "base";
	root.transform = glm::scale(glm::vec3(0.2f, 0.2f, 0.2f));
	root.init_translate = glm::vec3(-20.0f,0,0);
	root.transform = glm::translate(root.transform, root.init_translate);
	root.R = qRotate(glm::vec3(0));

	bones.push_back(root);

	for (int i = 1; i < armcount; i++)
		bones.push_back(Bone());//create bone
	
	for (int i = 1; i < armcount; i++) {
		bones[i].nodeName = "   e" + std::to_string(i);//assign name
		bones[i].init_translate = glm::vec3(0.0f, 5.0f, 0.0f);//assign translation
		glm::mat4 cTransform = glm::mat4(bones[i - 1].transform);
		bones[i].transform = glm::translate(cTransform, bones[i].init_translate);
	}

	for (int i = armcount - 1; i > 0; i--)
		bones[i-1].children.push_back(bones[i]);
	
	bones[0].Print("", true);

	//m = arma::pinv(m);

	//m=arma::pinv(m);
	root.UpdatePosition(root.transform, true);
}

