#ifndef DEF_USER_INTERFACE
#define DEF_USER_INTERFACE

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glmAnimation3D.h"

class UserInterface 
{
public:
	UserInterface(GLFWwindow* window);
	virtual ~UserInterface();
	bool inputColorR() const;
	bool inputColorG() const;
	bool inputColorB() const;
	bool inputColorA() const;
	bool inputDemandingScaleCube() const;
	bool inputDemandingScaleCubeX() const;
	bool inputDemandingScaleCubeY() const;
	bool inputDemandingScaleCubeZ() const;
	bool inputDemandingAnimation() const;
	bool inputDemandingRotate() const;
	bool inputDemandingChangeColorObject() const;
	bool inputDemandingTexture1() const;
	bool inputDemandingRotateAroundX() const;
	bool inputDemandingRotateAroundY() const;
	bool inputDemandingRotateAroundZ() const;
	bool inputDemandingRotateRight() const;
	bool inputDemandingRotateLeft() const;
	bool inputDemandingChangeFOV() const; 
	bool confirmFilePath() const;
	void inputFileTexture(int successLoaderTexture);
	float setRotateAroundXValue();
	float setRotateAroundYValue();
	float setRotateAroundZValue();
	float setScaleCube();
	float setScaleCubeX();
	float setScaleCubeY();
	float setScaleCubeZ();
	void setColorR();
	void setColorG();
	void setColorB();
	void setColorA();
	void setColorObjectR();
	void setColorObjectG();
	void setColorObjectB();
	void setColorObjectA();
	void setChangeFOV();
	// getting value rotate
	int getIndicatorTextureFilePath();
	float& getValueRotateX();
	float& getValueRotateY();
	float& getValueRotateZ();
	float getFOV_Value() const;
	// 
	// getting value color
	float getColorR() const;
	float getColorG() const;
	float getColorB() const;
	float getColorA() const;
	float getColorObjectR() const;
	float getColorObjectG() const;
	float getColorObjectB() const;
	float getColorObjectA() const;


	void setSettingFrame();
	bool inputDemandingChangeColorFrame();
	bool ButtonForSetAnimation();
	bool changeColorFrame();
	void setLastedmatrix();
	void endFrame();
	float LastedFloatFrame;
	float LastedFloatFrameX;
	float LastedFloatFrameY;
	float LastedFloatFrameZ;
	static char* filePathPointer[150];
	protected:
		int lastedFilePath;
		static char filePath[150];
		float* size1 = nullptr;
		float FOV;
		float LastedFrameColorR;
		float LastedFrameColorG;
		float LastedFrameColorB;
		float LastedFrameColorA;
		float LastedRotateXValue;
		float LastedRotateYValue;
		float LastedRotateZValue;
		float LastedColorObjectR;
		float LastedColorObjectG;
		float LastedColorObjectB;
		float LastedColorObjectA;
};

#endif // !1

